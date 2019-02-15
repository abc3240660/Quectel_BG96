#!/bin/sh
#
#  Installation Script.
#
#  Copyright (c) 2012-2015 tSoniq. All rights reserved.
#
#   $0  script name.
#   $1  the command (as passed to PrivilegedScriptRunner::startScript()).
#   $2  the path to the application requesting the script run.
#   $3  the path to the application's resources directory (containing any files to be installed).
#   $4  the user that originally invoked the script
#   $5  the home directory for the user that originally invoked the script
#
#   WARNING: this script is run as root and may damage the user's computer.
#   Test any changes THOROUGHLY by running the script manually before testing with the end application.
#   Errors in this script may render the end-users computer inoperative and/or cause file system damage.
#
#   This script currently supports two commands:
#
#       install     Install the kernel extension and start it.
#       remove      Stop and uninstall the kernel extension; move the application to the trash
#
#   Note that the commands are not symmetric: install only installs the kernel extension (on the assumption
#   that the app is already available), whereas remove both uninstalls the kernel extension and also moves
#   the application itself to the trash.
#
#   This script - like most Mac applications - currently makes no attempt to uninstall any meta-files
#   stored in the user's ~/Library directory. There are two reasons for this: (i) we do not know exactly
#   what is generated by the OS and (ii) we have no knowledge of which users to clear the application
#   from (in the case that the application has been run from multiple user's accounts).
#
#   When customising this script for a different driver, you should only need to change the definitions
#   of the KEXT_BID and KEXT_NAM variables. These are hard coded here rather than passed as parameters
#   to reduce potential security hazzards.
#

# Common definitions.
COMMAND=$1
APPLICATION=$2
RESOURCE_DIR=$3
ORIGINAL_USER=$4
ORIGINAL_HOME=$5

echo "Running script $0"
echo "  command:       '$COMMAND'"
echo "  application:   '$APPLICATION'"
echo "  resources:     '$RESOURCE_DIR'"
echo "  original_user: '$ORIGINAL_USER'"
echo "  original_home: '$ORIGINAL_HOME'"


# The paths to the kext(s).
# These must match the CFBundleID and product name used to build the kernel extension.
KEXT_BID="com.fte.driver.FTEFirmwareUpdateSupport"
KEXT_NAM="FTEFirmwareUpdateSupport.kext"


# Method called to terminate execution with success status.
doExitSuccess()
{
    echo "@@@exit/success/${COMMAND}"
    exit 0
}


# Method called to terminate execution with failure status.
doExitFailure()
{
    echo "@@@exit/fail/${COMMAND}/$1"
    exit 0
}


# Move the supplied argument(s) to the trash
doMoveToTrash()
{
    local SOURCE
    for SOURCE in "$@"; do

        local FILENAME=`basename "${SOURCE}"`
        FILENAME=${FILENAME%/}
        local TARGET=$FILENAME

        while [ -e "${ORIGINAL_HOME}/.Trash/${TARGET}" ]; do
          local EXTENSION=`expr "${FILENAME}" : ".*\(\.[^\.]*\)$"`
          local STEM=${FILENAME%$EXTENSION}
          TARGET="/$STEM`date +%H-%M-%S` ${RANDOM}${EXTENSION}"
        done
        TARGET="${ORIGINAL_HOME}/.Trash/${TARGET}"

        mv "${SOURCE}" "${TARGET}"
    done
}


# Method called to perform uninstallation of the driver.
doRemoveDriver()
{
    # sanity check (before sudo rm -rf destroys the user's computer)
    if [ -z "${KEXT_NAM}" ] ; then
        doExitFailure "Undefined kext name"
    else
        # unload the driver (using the bundle-id, as we do not know which copy is in use)
        kextunload -b "${KEXT_BID}"

        # remove the driver files
        if [ -d "/Library/Extensions/${KEXT_NAM}" ] ; then
            rm -rf "/Library/Extensions/${KEXT_NAM}"
            touch /Library/Extensions
        fi
        if [ -d "/System/Library/Extensions/${KEXT_NAM}" ] ; then
            rm -rf "/System/Library/Extensions/${KEXT_NAM}"
            touch /System/Library/Extensions
        fi
    fi
}


# Generic method used to install a specific instance of the driver.
#
#   $1  Specifies the KEXT name.
#   $2  Specifies the KEXT source dir.
#   $3  Specifies the KEXT target dir.
#
doInstallDriverFile()
{
    KEXT_TMP="`mktemp -d -t tsoniq`"
    KEXT_SRC="${2}/${1}.tgz"
    KEXT_DST="${3}/${1}"
    echo "doInstallDriverFile: ${KEXT_SRC}  -->  ${KEXT_TMP}  -->  ${KEXT_DST}"
    if [ ! -z "${1}" ] && [ -f "${KEXT_SRC}" ] && [ -d "${3}" ] ; then
        mkdir -p "${KEXT_TMP}"
        cd "${KEXT_TMP}" ; tar zxf "${KEXT_SRC}"
        chown -R root:wheel "${KEXT_TMP}/${1}"
        chmod -R 755 "${KEXT_TMP}/${1}"
        mv "${KEXT_TMP}/${1}" "${KEXT_DST}"
    fi
}


# Method called to perform installation.
doInstallDriver()
{
    # remove current install files
    doRemoveDriver

    # we always install to /Library/Extensions, but only /System/Library/Extensions if running a pre-10.9 OS.
    OS_PRODUCT_VERSION=`sw_vers -productVersion | cut -d . -f 2`

    # install the new driver and load it
    if [ -z "${KEXT_NAM}" ] ; then

        doExitFailure "Undefined kext name"

    elif [ ${OS_PRODUCT_VERSION} -lt 9 ] ; then

        # Running on 10.8 or older.
        # Install the unsigned driver extension in to /System/Library/Extensions (this is the driver that is used).
        echo "Installing for OS 10.8 or earlier"
        doInstallDriverFile "${KEXT_NAM}" "${RESOURCE_DIR}/kext0" "/System/Library/Extensions"
        kextload "/System/Library/Extensions/${KEXT_NAM}"
        touch "/System/Library/Extensions"

        # Also install the signed driver to /Library/Extensions to cover future upgrades to 10.9.
        if [ -d "/Library/Extensions" ] ; then
            doInstallDriverFile "${KEXT_NAM}" "${RESOURCE_DIR}/kext1" "/Library/Extensions"
            touch "/Library/Extensions"
        fi

    else

        # Running on 10.9 or newer. Install the signed driver in to /Library/Extensions.
        echo "Installing for OS 10.9 or later"
        doInstallDriverFile "${KEXT_NAM}" "${RESOURCE_DIR}/kext1" "/Library/Extensions"
        kextload "/Library/Extensions/${KEXT_NAM}"
        touch "/Library/Extensions"
    fi
}


# Run the script.
if [ ! -d "${RESOURCE_DIR}" ] ; then
    doExitFailure "Unable to access resource directory: ${RESOURCE_DIR}"
elif [ ! -f "${RESOURCE_DIR}/kext0/${KEXT_NAM}.tgz" ] ; then
    doExitFailure "Missing install file: kext0/${KEXT_NAM}"
elif [ ! -f "${RESOURCE_DIR}/kext1/${KEXT_NAM}.tgz" ] ; then
    doExitFailure "Missing install file: kext1/${KEXT_NAM}"
elif [ "${COMMAND}" = "install" ] ; then
    doInstallDriver
    doExitSuccess
elif [ "${COMMAND}" = "remove" ] ; then
    doRemoveDriver
    doMoveToTrash "${APPLICATION}"
    doExitSuccess
else
    doExitFailure "unknown command: ${COMMAND}"
fi
