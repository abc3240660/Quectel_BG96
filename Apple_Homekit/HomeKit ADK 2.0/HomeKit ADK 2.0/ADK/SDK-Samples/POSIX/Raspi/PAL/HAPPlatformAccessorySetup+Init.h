//
// Package: HomeKit-ADK
// Version: 2.0 (16A62)
//
// Disclaimer: IMPORTANT: This Apple software is supplied to you, by Apple Inc. ("Apple"), in your
// capacity as a current, and in good standing, Licensee in the MFi Licensing Program. Use of this
// Apple software is governed by and subject to the terms and conditions of your MFi License,
// including, but not limited to, the restrictions specified in the provision entitled "Public
// Software", and is further subject to your agreement to the following additional terms, and your
// agreement that the use, installation, modification or redistribution of this Apple software
// constitutes acceptance of these additional terms. If you do not agree with these additional terms,
// you may not use, install, modify or redistribute this Apple software.
//
// Subject to all of these terms and in consideration of your agreement to abide by them, Apple grants
// you, for as long as you are a current and in good-standing MFi Licensee, a personal, non-exclusive
// license, under Apple's copyrights in this Apple software (the "Apple Software"), to use,
// reproduce, and modify the Apple Software in source form, and to use, reproduce, modify, and
// redistribute the Apple Software, with or without modifications, in binary form, in each of the
// foregoing cases to the extent necessary to develop and/or manufacture "Proposed Products" and
// "Licensed Products" in accordance with the terms of your MFi License. While you may not
// redistribute the Apple Software in source form, should you redistribute the Apple Software in binary
// form, you must retain this notice and the following text and disclaimers in all such redistributions
// of the Apple Software. Neither the name, trademarks, service marks, or logos of Apple Inc. may be
// used to endorse or promote products derived from the Apple Software without specific prior written
// permission from Apple. Except as expressly stated in this notice, no other rights or licenses,
// express or implied, are granted by Apple herein, including but not limited to any patent rights that
// may be infringed by your derivative works or by other works in which the Apple Software may be
// incorporated. Apple may terminate this license to the Apple Software by removing it from the list
// of Licensed Technology in the MFi License, or otherwise in accordance with the terms of such MFi License.
//
// Unless you explicitly state otherwise, if you provide any ideas, suggestions, recommendations, bug
// fixes or enhancements to Apple in connection with this software ("Feedback"), you hereby grant to
// Apple a non-exclusive, fully paid-up, perpetual, irrevocable, worldwide license to make, use,
// reproduce, incorporate, modify, display, perform, sell, make or have made derivative works of,
// distribute (directly or indirectly) and sublicense, such Feedback in connection with Apple products
// and services. Providing this Feedback is voluntary, but if you do provide Feedback to Apple, you
// acknowledge and agree that Apple may exercise the license granted above without the payment of
// royalties or further consideration to Participant.
//
// The Apple Software is provided by Apple on an "AS IS" basis. APPLE MAKES NO WARRANTIES, EXPRESS OR
// IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR
// IN COMBINATION WITH YOUR PRODUCTS.
//
// IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION
// AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT
// (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (C) 2018 Apple Inc. All Rights Reserved.
//

#ifndef HAP_PLATFORM_ACCESSORY_SETUP_INIT_H
#define HAP_PLATFORM_ACCESSORY_SETUP_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAVE_NFC
    #define HAVE_NFC 0
#endif

#if HAVE_NFC
    #include <pthread.h>
    #include <nfc/nfc.h>
#endif

#include "HAPPlatform.h"

#if __has_feature(nullability)
#pragma clang assume_nonnull begin
#endif

/**@file
 * Accessory setup manager.
 *
 * The linked key-value store needs to be provisioned with accessory setup information
 * before this implementation may be used. Please refer to the Provision tool.
 *
 * - Programmable NFC functionality uses libnfc <http://libnfc.org>.
 *   This library supports many popular NFC chips and is configured using a connection string.
 *   If programmable NFC is accessed differently the implementation's function
 *   `HAPPlatformAccessorySetupUpdateSetupPayload` needs to be adjusted.
 *
 * - Display functionality uses the HAPLog APIs to display the Setup Payload and Setup Code.
 *   If a display is connected the implementation's function `HAPPlatformAccessorySetupUpdateSetupPayload`
 *   needs to be adjusted.
 *
 * **Example**

   @code{.c}

   // Get dependencies.
   HAPPlatformKeyValueStoreRef keyValueStore;

   // Allocate accessory setup manager.
   static HAPPlatformAccessorySetup accessorySetup;

   // Determine accessory capabilities.
   bool HAVE_DISPLAY;
   bool HAVE_NFC;
   const char *LIBNFC_CONNECTION_STRING; // Only applicable if programmable NFC is used.

   // Initialize accessory setup manager.
   HAPPlatformAccessorySetupCreate(&accessorySetup,
       &(const HAPPlatformAccessorySetupOptions) {
           .keyValueStore = keyValueStore,
           .useDisplay = HAVE_DISPLAY,
           .useProgrammableNFC = HAVE_NFC,
           .libnfcConnectionString = HAVE_NFC ? LIBNFC_CONNECTION_STRING : NULL
       });

   @endcode
 */

/**
 * Accessory setup manager initialization options.
 */
typedef struct {
    /**
     * Key-value store.
     */
    HAPPlatformKeyValueStoreRef keyValueStore;
    
    /**
     * Whether the accessory can display a dynamic 8-digit Setup Code.
     */
    bool useDisplay : 1;

    /**
     * Whether the accessory is connected to a programmable NFC tag that supports NDEF records.
     */
    bool useProgrammableNFC : 1;

    /**
     * The libnfc specific device connection string if specific NFC device is wanted, NULL otherwise.
     *
     * - Only used if the accessory is connected to a programmable NFC tag.
     */
    const char *_Nullable libnfcConnectionString;
} HAPPlatformAccessorySetupOptions;

/**
 * Accessory setup manager.
 */
struct HAPPlatformAccessorySetup {
    // Opaque type. Do not access the instance fields directly.
    /**@cond */
    HAPPlatformKeyValueStoreRef keyValueStore;
    bool useDisplay : 1;
    bool useProgrammableNFC : 1;
    const char *_Nullable libnfcConnectionString;
    
    #if HAVE_NFC
        struct {
            HAPSetupPayload setupPayload;
            pthread_t thread;
            bool isActive : 1;

            volatile int nfcLock;
            volatile int isAborted;
            volatile int isEmulating;

            nfc_context *nfcContext;
            nfc_device *nfcDevice;
        } nfc;
    #endif
    /**@endcond */
};

/**
 * Initializes the accessory setup manager.
 *
 * @param[out] accessorySetup       Pointer to an allocated but uninitialized HAPPlatformAccessorySetup structure.
 * @param      options              Initialization options.
 */
void HAPPlatformAccessorySetupCreate(
    HAPPlatformAccessorySetupRef accessorySetup,
    const HAPPlatformAccessorySetupOptions *options);

/**
 * Releases resources associated with an initialized accessory setup manager.
 *
 * @param      accessorySetup       Accessory setup manager.
 */
void HAPPlatformAccessorySetupRelease(
    HAPPlatformAccessorySetupRef accessorySetup);

#if __has_feature(nullability)
#pragma clang assume_nonnull end
#endif

#ifdef __cplusplus
}
#endif

#endif
