/* This file has been auto-generated. Do not edit. To make changes, edit rules.xml. */

#import <Foundation/Foundation.h>

#import "SpecReferenceConstants.h"

enum {
    RuleLevelError = 0,
    RuleLevelWarning = 1,
    RuleLevelInfo = 2,
};
typedef UInt8 RuleLevel;

enum {
    RuleAccCapsVolumeInfoButNoDisplayRemoteLingoIdentifyID = 0,
    RuleAccTxVoltageLogicHighTooHigh30PinID = 1,
    RuleAccessoryAuthenticationCertificateSerialUnparsableiAP2ID = 2,
    RuleAccessoryCapsTokeniPodPreferenceTokenLineOutMismatchID = 3,
    RuleAccessoryCapsTokeniPodPreferenceTokenVideoOutConnectionMismatchID = 4,
    RuleAccessoryCapsTokeniPodPreferenceTokenVideoOutMismatchID = 5,
    RuleAccessoryCapsTokeniPodPreferenceTokenVideoOutMonitorAspectRatioMismatchID = 6,
    RuleAccessoryCapsTokeniPodPreferenceTokenVideoOutSignalFormatMismatchID = 7,
    RuleAccessoryDataTransferAfterSessionClosedID = 8,
    RuleAccessoryDataTransferAfterSessionClosedAndACKedID = 9,
    RuleAccessoryDataTransferBeforeOpenDataSessionForProtocolACKedID = 10,
    RuleAccessoryHIDReportNotDevACKedID = 11,
    RuleAccessoryHIDReportPaddingBitSetToOneiAP2ID = 12,
    RuleAccessoryIdentificationRequiredMessagesNotSeenCAiAP2ID = 13,
    RuleAccessoryIdentifiediAP2HIDMessagesWithoutiAP2HIDComponentiAP2ID = 14,
    RuleAccessoryInfoContainsAppleTrademarkID = 15,
    RuleAccessoryInvalidConnectionLightningTo30PinAdapter8PinID = 16,
    RuleAccessoryInvalidConnectionOrientation8PinID = 17,
    RuleAccessorySentDeprecatedCommandID = 18,
    RuleAccessorySentInvalidLinkPacketCAiAP2ID = 19,
    RuleAccessoryStatusNotificationCommandWithoutAccessoryInfoTokenID = 20,
    RuleAccessoryStatusNotificationForSameStatusTypeSentTooFrequentlyID = 21,
    RuleAccessoryStatusNotificationMissingID = 22,
    RuleAccessoryStatusNotificationWithUnrecognizedStatusTypeID = 23,
    RuleAccessoryStatusNotificationWithoutRetAccessoryStatusNotificationID = 24,
    RuleAlarmDeprecatedID = 25,
    RuleAnalogAudioOutRequiredCommandsNotSeenCAID = 26,
    RuleAnalogUSBAudioRoutingAccCapWithAVSynchronizationSupportedID = 27,
    RuleAnalogUSBAudioRoutingAccCapWithoutAnalogUSBAudioRoutingSupportID = 28,
    RuleAnalogUSBAudioRoutingAccCapWithoutIdentifyForDigitalAudioLingoID = 29,
    RuleAnalogUSBAudioRoutingAccCapWithoutUSBHostDeviceID = 30,
    RuleAppLaunchRequiredMessagesNotSeenCAiAP2ID = 31,
    RuleAppleDeviceMessageContainsUnknownParametersiAP2ID = 32,
    RuleAssistiveTouchHIDComponentCountInvalidiAP2ID = 33,
    RuleAssistiveTouchRequiredCommandsNotSeenCAID = 34,
    RuleAssistiveTouchRequiredHIDUsagePageMissingNativeUSBiAP2ID = 35,
    RuleAssistiveTouchRequiredHIDUsagePageMissingiAP2ID = 36,
    RuleAssistiveTouchRequiredMessagesNotSeenCAiAP2ID = 37,
    RuleAssistiveTouchWithoutAccessoryCapsTokenID = 38,
    RuleAssistiveTouchWithoutLingoOptionsID = 39,
    RuleAsyncAccessoryDataLocationTypeNotSupportedByAccID = 40,
    RuleAsyncAccessoryDataSentWithoutWaitingForiPodACKID = 41,
    RuleAuthCertClassDoesNotMatchIdentifiedLingoesID = 42,
    RuleAuthV2GetSignatureTimeoutID = 43,
    RuleAuthenticationCertificateTimeoutiAP2ID = 44,
    RuleAuthenticationRequiredMessagesNotSeenCAiAP2ID = 45,
    RuleAuthenticationResponseTimeoutiAP2ID = 46,
    RuleAuthenticationV2BadIDLDeviceIDID = 47,
    RuleAuthenticationV2Timeout150sID = 48,
    RuleBadSignatureReturnedID = 49,
    RuleBaud55Not19200Or5760030PinID = 50,
    RuleBaudFFNot19200Or5760030PinID = 51,
    RuleBluetoothComponentInformationComponentIdentifierInvalidiAP2ID = 52,
    RuleBluetoothComponentInformationMissingComponentiAP2ID = 53,
    RuleBluetoothComponentInformationNoNewInformationiAP2ID = 54,
    RuleBluetoothRequiredMessagesNotSeenCAiAP2ID = 55,
    RuleCancelCommandBeforeAccessoryCapsTokenID = 56,
    RuleCancelCommandForUnsupportedCommandIDID = 57,
    RuleCapsTokenWithoutLingoIdentifiedID = 58,
    RuleCloseDataSessionNotDevACKed30PinID = 59,
    RuleClosedDescriptorInUnregisterDescriptorID = 60,
    RuleCommWithAppsAccessoryCapsTokenWithoutCommWithAppsClaimID = 61,
    RuleCommWithAppsClaimedWithoutValidAccessoryCapsTokenID = 62,
    RuleCommWithAppsCommandSentWithoutCommWithAppsAccessoryCapsTokenACKedID = 63,
    RuleCommandFromUnidentifiedLingoID = 64,
    RuleCommandRequiresAuthenticationV2ID = 65,
    RuleCommandSentAfterIdentificationFailedID = 66,
    RuleCommandSentBeforeIdentificationCompletedID = 67,
    RuleCommandsFromDeviceWithResistor360k30PinID = 68,
    RuleCommunicationWithiOSApplicationsRequiredCommandsNotSeenCAID = 69,
    RuleCurrentGPSTimeSentTooFrequentlyID = 70,
    RuleDeprecated191kResistor30PinID = 71,
    RuleDeprecated1MResistor30PinID = 72,
    RuleDeprecated360kResistor30PinID = 73,
    RuleDeprecatedBitsSetID = 74,
    RuleDeprecatedFireWirePowerPresent30PinID = 75,
    RuleDeprecatedRoleSwitchSeenID = 76,
    RuleDevACKCommandOKReturnedForOtherThanLastSectionID = 77,
    RuleDevACKSectionReceivedReturnedForLastSectionID = 78,
    RuleDevACKWithSectionReceivedOKStatusDuplicateSectionIndexID = 79,
    RuleDeviceIDNotZeroOrTwoHundredID = 80,
    RuleDeviceNotificationsOptionalMessagesNotSeenCAiAP2ID = 81,
    RuleDevicePowerVoltageTooLowExtended8PinID = 82,
    RuleDevicePowerVoltageTooLowLoadTest8PinID = 83,
    RuleDevicePoweredAccessoryFeatureNotSelectedCAiAP2ID = 84,
    RuleDevicePoweredAccessoryPowerMessagesNotSeenCAiAP2ID = 85,
    RuleDevicePoweredAccessoryUpdateMessagesNotDeclarediAP2ID = 86,
    RuleDidNotRegisterForBothNowPlayingApplicationNotificationsID = 87,
    RuleDidNotWaitAfterAuthenticationFailedID = 88,
    RuleDidNotWaitForSessionSpaceAvailableAfterSessionWriteFailureID = 89,
    RuleDigitalAudioLingoInUSBHostMode30PinID = 90,
    RuleDisplayRemoteRequiredCommandsNotSeenCAID = 91,
    RuleDuplicateHIDComponentIdentifieriAP2ID = 92,
    RuleDuplicateTransactionIDDetectedID = 93,
    RuleDuplicateTransportComponentIdentifieriAP2ID = 94,
    RuleEAProtocolParameterSeenDuringIdentificationWithoutEAMessagesDeclarediAP2ID = 95,
    RuleEAProtocolParameterSeenDuringIdentificationWithoutEASessionDuringLinkSynchronizationiAP2ID = 96,
    RuleEAProtocolTokenOrBundleSeedIDPrefTokenWhenCommunicationWithiOSUnusableID = 97,
    RuleEASessionDuringLinkSynchronizationWithoutiAP2EASessionProtocolParameterDuringIdentificationiAP2ID = 98,
    RuleEndIDPSRequestingAuthSentWithoutAnySetFIDTokenValuesID = 99,
    RuleEndIDPSSentWhileAckFIDTokenValuesPendingID = 100,
    RuleEnterExitExtendedInterfaceModeInsteadOfSetUIModeID = 101,
    RuleExceededMaxPacketPayloadSizeID = 102,
    RuleExtendedInterfaceModeWithoutRegistrationForDatabaseChangeNotificationID = 103,
    RuleExtendedInterfaceRequiredCommandsNotSeenCAID = 104,
    RuleExternalAccessoryProtocolIdentifierParametersNotUniqueiAP2ID = 105,
    RuleExternalAccessoryProtocolNameParametersNotUniqueiAP2ID = 106,
    RuleExternalAccessoryProtocolNativeTransportComponentIdentifierInvalidiAP2ID = 107,
    RuleExternalAccessorySessionMessagesNotSeenCAiAP2ID = 108,
    RuleFileTransferSessionDuringLinkSynchronizationWithoutiAP2FileTransferSessionMessagesDuringIdentificationiAP2ID = 109,
    RuleFileTransferWithoutFileTransferSessioniAP2ID = 110,
    RuleFileWriteBeforeOpenID = 111,
    RuleFirstCameraButtonStatusIsZeroID = 112,
    RuleFirstCommandNotStartIDPSID = 113,
    RuleFirstPacket20msDelayViolatedID = 114,
    RuleFirstTokenNotIdentifyTokenID = 115,
    RuleFlowControlNotificationIgnoredID = 116,
    RuleGameControllerAccessoryIdentificationExceededNumberOfNFFComponentsiAP2ID = 117,
    RuleGameControllerDPadOpposingCardinalDirectionsHIDSeeniAP2ID = 118,
    RuleGameControllerDPadOpposingCardinalDirectionsNativeHIDSeeniAP2ID = 119,
    RuleGameControllerDigitalSwitchHIDInvalidiAP2ID = 120,
    RuleGameControllerDigitalSwitchNativeHIDInvalidiAP2ID = 121,
    RuleGameControllerInvalidLEDArrayFieldiAP2ID = 122,
    RuleGameControllerInvalidNativeLEDArrayFieldiAP2ID = 123,
    RuleGameControllerJoystickAxesHIDFieldSizeNotEqualiAP2ID = 124,
    RuleGameControllerJoystickAxesNativeHIDFieldSizeNotEqualiAP2ID = 125,
    RuleGameControllerJoystickHIDInvalidiAP2ID = 126,
    RuleGameControllerJoystickNativeHIDInvalidiAP2ID = 127,
    RuleGameControllerLEDHIDInvalidiAP2ID = 128,
    RuleGameControllerLEDNativeHIDInvalidiAP2ID = 129,
    RuleGameControllerMultipleFormFittingControllerComponentImplementationiAP2ID = 130,
    RuleGameControllerPressureSensitiveSwitchHIDInvalidiAP2ID = 131,
    RuleGameControllerPressureSensitiveSwitchNativeHIDInvalidiAP2ID = 132,
    RuleGameControllerProhibitedUsagesSeeniAP2ID = 133,
    RuleGameControllerRequiredHIDUsagesNotDefinediAP2ID = 134,
    RuleGameControllerRequiredNativeHIDUsagesNotDefinediAP2ID = 135,
    RuleGameControllerSwitchesHIDNotSeenCAiAP2ID = 136,
    RuleGameControllerWithNonControllerComponentiAP2ID = 137,
    RuleGeneralLingoNotInIdentifyTokenID = 138,
    RuleGetLyricsRepeatFrequencyTooFastID = 139,
    RuleGetNumPlayingTracksNotSentBeforeGetPBTrackInfoID = 140,
    RuleGetOrSetiPodPreferencesVideoOutRequiresAuthID = 141,
    RuleGetPlayStatusBeforePlayControlACKID = 142,
    RuleGetWithoutAttemptedNotificationRegistrationID = 143,
    RuleGetiPodOptionsForLingoDigitalAudioBeforeAnalogUSBAudioRoutingAccCapID = 144,
    RuleGetiPodOptionsForLingoGeneralBeforeAnalogUSBAudioRoutingAccCapID = 145,
    RuleGetiPodOptionsWithoutTryingGetiPodOptionsForLingoID = 146,
    RuleHDRadioCommandWithoutHDCapableBitID = 147,
    RuleHIDFunctionClaimWithoutUSBHostHIDComponentCAiAP2ID = 148,
    RuleHIDFunctionClaimWithoutiAP2HIDComponentCAiAP2ID = 149,
    RuleHIDNativeUSBHIDReportPaddingBitSetToOneiAP2ID = 150,
    RuleHIDOveriAP2MessagesNotSeenCAiAP2ID = 151,
    RuleIAP2HIDComponentWithoutHIDFunctionClaimCAiAP2ID = 152,
    RuleIAPSentAfterUnsupportedAccessoryID = 153,
    RuleIAPSentDuringFlowControlWaitTimeID = 154,
    RuleIAPSentWith255kResistor30PinID = 155,
    RuleIDPSCommandSentBeforeStartIDPSACKedID = 156,
    RuleIDPSCommandSentWithoutStartIDPSID = 157,
    RuleIDPSStartedButNotCompletedWithin3SecondsID = 158,
    RuleIPodAttachWhenAccessoryAttached30PinID = 159,
    RuleIPodAuthBeforeDeviceAuthID = 160,
    RuleIPodHIDReportBeforeRegisterDescriptorACKedID = 161,
    RuleIPodOutButtonStatusSpacingGreaterThan100msID = 162,
    RuleIPodOutRequiredCommandsNotSeenCAID = 163,
    RuleIPodOutSimpleRemoteCommandWithoutiPodOutModeID = 164,
    RuleIPodOutWithoutClaimID = 165,
    RuleIdenticalContextButtonStatusSpacingLessThan30msID = 166,
    RuleIdenticalRotationInputStatusSpacingLessThan30msID = 167,
    RuleIdenticalVideoButtonStatusSpacingLessThan30msID = 168,
    RuleIdenticaliPodOutButtonStatusSpacingLessThan30msID = 169,
    RuleIdentificationID = 170,
    RuleIdentificationCommandSentTooSoonAfterFirstStartIDPSID = 171,
    RuleIdentificationInformationBeforeStartIdentificationiAP2ID = 172,
    RuleIdentificationInformationFirmwareVersionEmptyiAP2ID = 173,
    RuleIdentificationInformationHardwareVersionEmptyiAP2ID = 174,
    RuleIdentificationInformationIncorrectSourceForDeclaredReceivedMessageiAP2ID = 175,
    RuleIdentificationInformationIncorrectSourceForDeclaredSentMessageiAP2ID = 176,
    RuleIdentificationInformationManufacturerEmptyiAP2ID = 177,
    RuleIdentificationInformationModelIdentifierEmptyiAP2ID = 178,
    RuleIdentificationInformationNameEmptyiAP2ID = 179,
    RuleIdentificationInformationNonUniqueSupportedMessagesListiAP2ID = 180,
    RuleIdentificationInformationSerialNumberEmptyiAP2ID = 181,
    RuleIdentificationInformationUnknownSentOrReceivedMessageiAP2ID = 182,
    RuleIdentificationMessageSentAfterIdentificationAcceptediAP2ID = 183,
    RuleIdentifyingForAccessoryPowerLingoIsDeprecatedID = 184,
    RuleIdentifyingForMicrophoneLingoIsDeprecatedID = 185,
    RuleIncorrectBadParameterSentForiPodDataTransferID = 186,
    RuleIncorrectSelectDBRecordFieldLengthID = 187,
    RuleInsufficientRetryingOfIDLID = 188,
    RuleInvalidScaleDisplayFactorID = 189,
    RuleKeyboardRequiredHIDUsagePageMissingNativeUSBiAP2ID = 190,
    RuleKeyboardRequiredHIDUsagePageMissingiAP2ID = 191,
    RuleKeyboardWithConsumerPageInvalidHIDUsagesiAP2ID = 192,
    RuleLegacyIdentifyAfterIDPSID = 193,
    RuleLegacyIdentifyForDigitalAudioID = 194,
    RuleLightningModuleConfigurationDeprecated8PinID = 195,
    RuleLineOutCapsWithoutLineOutPreferencesID = 196,
    RuleLineOutDisabledAfterLineOutPreferencesSetID = 197,
    RuleLineOutPrefNotSetDuringIDPSForiPodOutID = 198,
    RuleLineOutPreferencesSeenWithoutLineOutAccessoryClaimID = 199,
    RuleLingo4DBSelectionID = 200,
    RuleLingo4OnlyInExtendedInterfaceModeID = 201,
    RuleLinkDetectSequenceSentTooEarlyiAP2ID = 202,
    RuleLinkDetectSequenceSentTooLateiAP2ID = 203,
    RuleLinkPacketACKAfterCumulativeAcknowledgmentTimeoutiAP2ID = 204,
    RuleLinkPacketACKNumberInvalidiAP2ID = 205,
    RuleLinkPacketEAKNumberInvalidiAP2ID = 206,
    RuleLinkPacketEAKSentWithoutPacketsOutOfOrderiAP2ID = 207,
    RuleLinkPacketLinkSynchronizationCumulativeACKTimeoutNotNegotiatediAP2ID = 208,
    RuleLinkPacketLinkSynchronizationLinkVersionNotNegotiatediAP2ID = 209,
    RuleLinkPacketLinkSynchronizationMaxCumulativeACKNotNegotiatediAP2ID = 210,
    RuleLinkPacketLinkSynchronizationMaxNumOfRetransmissionsNotNegotiatediAP2ID = 211,
    RuleLinkPacketLinkSynchronizationNegotiationNotConcludediAP2ID = 212,
    RuleLinkPacketLinkSynchronizationNumberOfRetriesExceedediAP2ID = 213,
    RuleLinkPacketLinkSynchronizationReactivationBefore80MsiAP2ID = 214,
    RuleLinkPacketLinkSynchronizationRetransmissionTimeoutNotNegotiatediAP2ID = 215,
    RuleLinkPacketLinkSynchronizationSessionNotNegotiatediAP2ID = 216,
    RuleLinkPacketLinkSynchronizationStartSYNPacketInConjunctionWithOtherControlBitiAP2ID = 217,
    RuleLinkPacketMaxNumberOfRetransmissionsExceedediAP2ID = 218,
    RuleLinkPacketMaxPacketLengthExceedediAP2ID = 219,
    RuleLinkPacketNoSYNWithinTimeoutAfterRSTiAP2ID = 220,
    RuleLinkPacketNumberOfOutstandingPacketsExceedediAP2ID = 221,
    RuleLinkPacketRetransmittedBeforeRetransmissionTimeoutiAP2ID = 222,
    RuleLinkPacketSentToUnsupportedDeviceiAP2ID = 223,
    RuleLinkPacketSequenceNumberDuplicatediAP2ID = 224,
    RuleLinkPacketiAP1CommunicationNotInitiatediAP2ID = 225,
    RuleLinkPacketiAP2DetectSequenceNotSentiAP2ID = 226,
    RuleLocationLingoIdentificationWithoutLocationClaimID = 227,
    RuleLocationLingoRequiredCommandsNotSeenCAID = 228,
    RuleLocationMessagesNotSeenCAiAP2ID = 229,
    RuleMaxConnectionsResponseIgnoredID = 230,
    RuleMeasured55Or5ABaudRateOutOfRange8PiniAP2ID = 231,
    RuleMeasuredFFBaudRateOutOfRange8PinID = 232,
    RuleMediaLibraryInformationMessagesNotSeenCAiAP2ID = 233,
    RuleMediaLibraryPlaybackOptionalMessagesNotSeenCAiAP2ID = 234,
    RuleMediaLibraryPlaybackUsedWithoutMediaLibraryUpdatesCAiAP2ID = 235,
    RuleMediaLibraryPlaybackWithoutMediaLibraryUpdatesInDeclarationiAP2ID = 236,
    RuleMediaLibraryUpdatesMessagesNotSeenCAiAP2ID = 237,
    RuleMediaLibraryUpdatesUsedWithoutMediaLibraryInformationCAiAP2ID = 238,
    RuleMediaLibraryUpdatesWithoutMediaLibraryInformationInDeclarationiAP2ID = 239,
    RuleMediaPlaybackRemoteInvalidHIDUsagesNativeUSBiAP2ID = 240,
    RuleMediaPlaybackRemoteInvalidHIDUsagesiAP2ID = 241,
    RuleMediaPlaybackRemoteRequiredHIDUsagePageMissingNativeUSBiAP2ID = 242,
    RuleMediaPlaybackRemoteRequiredHIDUsagePageMissingiAP2ID = 243,
    RuleMessageContainsUnknownParametersiAP2ID = 244,
    RuleMicrophoneCapsTokenDeprecatedID = 245,
    RuleMissingContextButtonStatusID = 246,
    RuleMissingRequestTransportMaxPayloadSizeDuringIDPSID = 247,
    RuleMissingVideoButtonStatusID = 248,
    RuleMultisectionAsyncAccessoryDataLocationDataTypeMismatchID = 249,
    RuleMultisectionAsyncAccessoryDataLocationTypeMismatchID = 250,
    RuleMultisectionAsyncAccessoryDataWithDataSectionIndexOutOfRangeID = 251,
    RuleMultisectionAsyncAccessoryDataWithEmptyPayloadID = 252,
    RuleMultisectionAsyncAccessoryDataWithMaximumDataSectionIndexMismatchID = 253,
    RuleMultisectionAsyncAccessoryDataWithNonSequentialDataSectionIndexID = 254,
    RuleMultisectionSetAccessoryDataValidButEmptyNotACKedID = 255,
    RuleMustSetSatEphRequiredBitID = 256,
    RuleNextAccessoryDataTransferTooSoonID = 257,
    RuleNoBluetoothComponentAfterIdentificationiAP2ID = 258,
    RuleNoBluetoothIdentificationCAiAP2ID = 259,
    RuleNoExplicitSetiPodPreferencesAudioID = 260,
    RuleNoExternalAccessoryProtocolParameterWhileIdentifyingCAiAP2ID = 261,
    RuleNoGetArtworkFormatsID = 262,
    RuleNoGetCurrentPlayingTrackChapterInfoID = 263,
    RuleNoGetiPodCapsForGymEquipmentID = 264,
    RuleNoHIDComponentDuringIdentificationCAiAP2ID = 265,
    RuleNoIAPAfterStartIDPSNACKID = 266,
    RuleNoIdentificationAfterPowerCycle30PinID = 267,
    RuleNoNewIdentificationBetweenIDLAndACKID = 268,
    RuleNoNotifyUSBModeDevACKWithin500msID = 269,
    RuleNoRequestLingoProtocolVersionForLingo4ID = 270,
    RuleNoRequestTransportMaxPayloadSizeBeforeAccessoryDataTransferID = 271,
    RuleNoResponseToGetAccessoryAuthenticationInfoID = 272,
    RuleNoResponseToGetAccessoryInfoID = 273,
    RuleNoResponseToGetCurrentEQIndexID = 274,
    RuleNoResponseToGetEQIndexNameID = 275,
    RuleNoResponseToGetEQSettingCountID = 276,
    RuleNoResponseToGetHDDataID = 277,
    RuleNoResponseToGetHDDataNotifyMaskID = 278,
    RuleNoResponseToGetHDDataReadyStatusID = 279,
    RuleNoResponseToGetHDProgramServiceID = 280,
    RuleNoResponseToGetHDProgramServiceCountID = 281,
    RuleNoRetAccessoryCapsForGetAccessoryCapsSystemCapsID = 282,
    RuleNoRetAccessoryCapsForGymEquipmentID = 283,
    RuleNoRetAccessoryCapsReturnedForSupportedLocationTypeID = 284,
    RuleNoRetAccessoryControlReturnedForSupportedControlTypeID = 285,
    RuleNoRetiPodCapsForGymEquipmentID = 286,
    RuleNoSetOrCheckiPodPreferencesVideoBeforeVideoOutEnabledID = 287,
    RuleNoTimelyIDLAfterStartIDPSNACKID = 288,
    RuleNoTimelyResponseToGetAccessoryCapsID = 289,
    RuleNoTimelyResponseToGetAccessoryControlID = 290,
    RuleNoTimelyResponseToGetAccessoryDataID = 291,
    RuleNoTimelyResponseToRetiPodAuthenticationInfoID = 292,
    RuleNoTimelyResponseToSetAccessoryControlID = 293,
    RuleNoTimelyResponseToSetAccessoryDataID = 294,
    RuleNoTimelyResponseToStartIdentificationOrIdentificationRejectedMessageiAP2ID = 295,
    RuleNoTimelyiAPButiAPResistorPresented30PinID = 296,
    RuleNoTransportSupportsiAP2ConnectionParameteriAP2ID = 297,
    RuleNonDevicePoweredAccessorySentAccessoryPowerModeiAP2ID = 298,
    RuleNowPlaying3rdPartyAppNotSeenCAiAP2ID = 299,
    RuleNowPlayingAppleAppsNotSeenCAiAP2ID = 300,
    RuleNowPlayingMessagesNotSeenCAiAP2ID = 301,
    RuleOpenDataSessionNotDevACKedID = 302,
    RulePendingACKID = 303,
    RulePlayControlCommandCodeDeprecatedID = 304,
    RulePlayControlCommandNotEndFFREWAfterStartFFID = 305,
    RulePlayControlCommandNotEndFFREWAfterStartREWID = 306,
    RulePlayControlResumeiPodWithoutThirdPartyApplicationCommunicationID = 307,
    RulePower100mAExceeded30PinID = 308,
    RulePowerSourceAccessoryInitialPowerSourceUpdateNotSeeniAP2ID = 309,
    RulePowerSourceAccessoryInitialStartPowerUpdatesNotSeeniAP2ID = 310,
    RulePowerSourceAccessoryRequiredMessagesNotDeclarediAP2ID = 311,
    RulePowerSourceUpdateInsufficientPowerSourceUsageSeenForClaimsCAiAP2ID = 312,
    RuleProhibitedCommandSentDuringIDPSID = 313,
    RuleRFTunerIdentificationWithoutClaimID = 314,
    RuleRFTunerRequestTimedOutID = 315,
    RuleRFTunerWithoutClaimID = 316,
    RuleRadioButtonStatusSpacingGreaterThan100msID = 317,
    RuleRadioButtonStatusSpacingLessThan30msID = 318,
    RuleRecordIndexOutOfBoundsID = 319,
    RuleRedundantGetAfterNotificationID = 320,
    RuleReferToRetiPodOptionsForLingoGeneralBit27NotUSBHostModeBit0ID = 321,
    RuleRegisterDescriptorHasAppleVIDID = 322,
    RuleRemoteUIEntryTooSoonAfterExitID = 323,
    RuleRemoteUIExitTooSoonAfterEntryID = 324,
    RuleRemoteUIIdentificationWithoutRemoteUIClaimID = 325,
    RuleRemoteUIModeCommandsRequireLingo4ID = 326,
    RuleRepeatRetAccessoryAuthenticationInfoSentBeforeACKID = 327,
    RuleRepeatedGetSentTooQuicklyID = 328,
    RuleRequestApplicationLaunchRetriedAfterNACKID = 329,
    RuleRequestApplicationLaunchUnsupportedID = 330,
    RuleRequestIdentifyNotAnsweredID = 331,
    RuleRequestLingoProtocolVersionWithoutTryingGetiPodOptionsForLingoID = 332,
    RuleRequestWiFiConnectionInfoRetriedID = 333,
    RuleRequiredAccessoryCapsTokenNotACKedID = 334,
    RuleRequiredAccessoryCapsTokenNotSentID = 335,
    RuleRequiredAccessoryInfoTokenWithFirmwareVersionNotACKedID = 336,
    RuleRequiredAccessoryInfoTokenWithFirmwareVersionNotSentID = 337,
    RuleRequiredAccessoryInfoTokenWithHardwareVersionNotACKedID = 338,
    RuleRequiredAccessoryInfoTokenWithHardwareVersionNotSentID = 339,
    RuleRequiredAccessoryInfoTokenWithManufacturerNotACKedID = 340,
    RuleRequiredAccessoryInfoTokenWithManufacturerNotSentID = 341,
    RuleRequiredAccessoryInfoTokenWithModelNumberNotACKedID = 342,
    RuleRequiredAccessoryInfoTokenWithModelNumberNotSentID = 343,
    RuleRequiredAccessoryInfoTokenWithNameNotACKedID = 344,
    RuleRequiredAccessoryInfoTokenWithNameNotSentID = 345,
    RuleRequiredBundleSeedIDPrefTokenNotACKedID = 346,
    RuleRequiredBundleSeedIDPrefTokenNotSentID = 347,
    RuleRequiredEAProtocolTokenNotACKedID = 348,
    RuleRequiredEAProtocolTokenNotSentID = 349,
    RuleRequiredIdentifyTokenNotACKedID = 350,
    RuleRequiredMicrophoneCapsTokenNotACKedID = 351,
    RuleRequiredMicrophoneCapsTokenNotSentID = 352,
    RuleResistorIDNotValid30PinID = 353,
    RuleResistorPresentButNot191k30PinID = 354,
    RuleResistorPresentButNot255kOrNone30PinID = 355,
    RuleResistorPresentButNot28k30PinID = 356,
    RuleResistorPresentButNot549k30PinID = 357,
    RuleResistorsIncorrectForClaimedCurrentCA8PinID = 358,
    RuleResponseToGetTunerFreqGreaterThan200msID = 359,
    RuleResponseToSetTunerFreqGreaterThan200msID = 360,
    RuleRestrictedCommandWhileIniPodOutModeID = 361,
    RuleRestrictedContextButtonStatusFromiOSDeviceID = 362,
    RuleRestrictedContextButtonStatusWhileIniPodOutModeID = 363,
    RuleRetAccessoryAuthInfoNotV2ID = 364,
    RuleRetAccessoryAuthenticationInfoCertClassUnparsableID = 365,
    RuleRetAccessoryAuthenticationInfoCertSerialUnparsableID = 366,
    RuleRetAccessoryAuthenticationInfoMaxSectionIndexMismatchID = 367,
    RuleRetAccessoryAuthenticationInfoOutOfRangeSectionIndexID = 368,
    RuleRetAccessoryAuthenticationInfoWithEmptyCertDataPayloadID = 369,
    RuleRetAccessoryCapsLocAsstDataBits1And2DoNotMatchID = 370,
    RuleRetAccessoryCapsLocationTypeMismatchID = 371,
    RuleRetAccessoryCapsSentWithInvalidLocCapsMaskID = 372,
    RuleRetAccessoryControlControlTypeMismatchID = 373,
    RuleRetAccessoryDataLocationDataTypeMismatchID = 374,
    RuleRetAccessoryDataLocationTypeMismatchID = 375,
    RuleRetAccessoryDataSentWithoutWaitingForiPodACKID = 376,
    RuleRetAccessoryInfoTypeTwoDeprecatedID = 377,
    RuleRetAccessoryStatusNotificationMissingAfterSetAccessoryStatusNotificationID = 378,
    RuleRetAccessoryStatusNotificationWithUnrecognizedBitsID = 379,
    RuleRetriedUnsupportedTokenID = 380,
    RuleRotationInputStatusSpacingGreaterThan100msID = 381,
    RuleSatelliteEphemerisRequestedTooFrequentlyID = 382,
    RuleScreenInfoTokenDeprecatedID = 383,
    RuleSecondByteNotSyncByteID = 384,
    RuleSecondOpeniPodFeatureFileWithoutCloseiPodFileID = 385,
    RuleSerialNoTimelyExitFromIntermittentHighPowerModeiAP2ID = 386,
    RuleSetAvailableCurrentNotSentAfterAuthID = 387,
    RuleSetAvailableCurrentValueIncorrectForSupportedAppleDevicesCAID = 388,
    RuleSetCurrentPlayingTrackChapterBeforeReturnCurrentPlayingTrackChapterInfoID = 389,
    RuleSetCurrentPlayingTrackChapterOutOfBoundsID = 390,
    RuleSetDisplayImageTooLateID = 391,
    RuleSetEventNotificationBeforeRetSupportedEventNotificationID = 392,
    RuleSetEventNotificationWithUnrecognizedBitsID = 393,
    RuleSetFIDTokenValuesSentWhileAckFIDTokenValuesPendingID = 394,
    RuleSetFIDTokenValuesWithoutGetiPodOptionsForLingoID = 395,
    RuleSetPlayStatusChangeNotificationOneByteFormSentWithoutVerifyingFourByteFormUnsupportedID = 396,
    RuleSetUIModeSentWheniPodOutUnusableID = 397,
    RuleSetVideoDelayWithoutRetiPodOptionsForLingoID = 398,
    RuleSimpleRemoteCommandSentWithoutSimpleRemoteClaimID = 399,
    RuleSimpleRemoteIdentifiedWithoutSimpleRemoteClaimID = 400,
    RuleSimpleRemoteRequiredCommandsNotSeenCAID = 401,
    RuleSportsLingoIdentificationWithoutGymEquipmentClaimID = 402,
    RuleSportsLingoRequiredCommandsNotSeenCAID = 403,
    RuleStartBluetoothConnectionUpdatesBluetoothTransportComponentIdentifierInvalidiAP2ID = 404,
    RuleStartEAMessageSeenWithoutEADatagramCAiAP2ID = 405,
    RuleStartFileTransferMessageSeenWithoutFileTransferDatagramCAiAP2ID = 406,
    RuleStartHIDHIDComponentIdentifierInvalidiAP2ID = 407,
    RuleStartIDPSRetriedTooQuicklyID = 408,
    RuleStartIDPSSentAfterBadParameterNACKID = 409,
    RuleStartIDPSSentAfterRejectionID = 410,
    RuleStartMediaLibraryUpdatesWithoutCorrectLastKnownRevisioniAP2ID = 411,
    RuleStartSecondMediaLibraryUpdatesWithoutLastKnownRevisioniAP2ID = 412,
    RuleStopHIDHIDComponentIdentifierInvalidiAP2ID = 413,
    RuleStorageLingoIdentificationWithoutStorageLingoAccessoryClaimID = 414,
    RuleStorageRequiredCommandsNotSeenCAID = 415,
    RuleSwitchControlHIDButtonCountInvalidiAP2ID = 416,
    RuleSwitchControlHIDButtonCountNotRecommendediAP2ID = 417,
    RuleSwitchControlHIDComponentCountInvalidiAP2ID = 418,
    RuleSwitchControlNativeHIDButtonCountInvalidiAP2ID = 419,
    RuleSwitchControlNativeHIDButtonCountNotRecommendediAP2ID = 420,
    RuleSyncByteSentOverUSBID = 421,
    RuleTestPatternProhibitedInProductionFirmwareID = 422,
    RuleTooManyRetriesOfAccessoryDataTransferID = 423,
    RuleTrafficSentBeforeAccessoryPowerTurnedOn30PinID = 424,
    RuleTrafficSentButPin20NotGrounded30PinID = 425,
    RuleTrafficSentWithin80msOfAccessoryPower30PinID = 426,
    RuleTrafficSentWithoutUsesiAPClaimID = 427,
    RuleUSBAudioAccCapWhenNotInUSBDeviceMode30PinID = 428,
    RuleUSBChargingPowerSourceType500mADeprecated30PinID = 429,
    RuleUSBDMinusDrivenWithoutUSBVbus30PinID = 430,
    RuleUSBDMinusResistorIncorrectFor1A30PinID = 431,
    RuleUSBDMinusResistorIncorrectFor2Point1A30PinID = 432,
    RuleUSBDMinusResistorIncorrectFor500mA30PinID = 433,
    RuleUSBDPlusDrivenWithoutUSBVbus30PinID = 434,
    RuleUSBDPlusResistorIncorrectFor1A30PinID = 435,
    RuleUSBDPlusResistorIncorrectFor2Point1A30PinID = 436,
    RuleUSBDPlusResistorIncorrectFor500mA30PinID = 437,
    RuleUSBDeviceModeAudioMessagesNotSeenCAiAP2ID = 438,
    RuleUSBHostHIDComponentDuplicateInterfaceNumberiAP2ID = 439,
    RuleUSBHostHIDComponentUSBHostTransportComponentIdentifierInvalidiAP2ID = 440,
    RuleUSBHostHIDComponentUndefinedInterfaceiAP2ID = 441,
    RuleUSBHostHIDComponentWithoutHIDFunctionClaimCAiAP2ID = 442,
    RuleUSBHostModeIdentificationWithoutClaimID = 443,
    RuleUSBHostModeInterruptInEndpointOptionalID = 444,
    RuleUSBHostModeWithoutClaimID = 445,
    RuleUSBInterfaceDescriptorsIncorrectForEANativeTransportiAP2ID = 446,
    RuleUSBVbusVoltageAtAcceptableLevelDuringLoadTest30PinID = 447,
    RuleUSBVbusVoltageReturnedToAcceptableLevel30PinID = 448,
    RuleUSBVbusVoltageTooHigh30PinID = 449,
    RuleUSBVbusVoltageTooLow30PinID = 450,
    RuleUSBVbusVoltageTooLowDuringLoadTest30PinID = 451,
    RuleUSBVbusVoltageTooLowExtended30PinID = 452,
    RuleUnexpectedAccResistor30PinID = 453,
    RuleUnexpectedAsyncAccessoryDataNMEASentenceID = 454,
    RuleUnexpectedAsyncAccessoryDataNMEASentenceAfterAccessoryAckID = 455,
    RuleUnknownDescriptorInUnregisterDescriptorID = 456,
    RuleUnknownDescriptorIniPodHIDReportID = 457,
    RuleUnknownSessionIDInAccessoryDataTransferID = 458,
    RuleUnrecognizedTransactionIDInResponseID = 459,
    RuleUnselectingTracksNotAllowedID = 460,
    RuleUnsupportedMessageSentiAP2ID = 461,
    RuleUnsupportedMessagesDeclaredCAiAP2ID = 462,
    RuleUnwarrantedLocationInformationSentiAP2ID = 463,
    RuleUsageNotSeenForSupportedHIDUsagesCAiAP2ID = 464,
    RuleUsageNotSeenForSupportedHIDUsagesNativeUSBCAiAP2ID = 465,
    RuleUserDataCommandSentButUserDataNotSupportedID = 466,
    RuleVbusDrivenWithoutUSBChargingPowerSourceClaim30PinID = 467,
    RuleVideoMonitorAspectRatioNotFullscreenWhenEnteringiPodOutModeID = 468,
    RuleVideoOutCapsWithoutVideoOutPreferencesID = 469,
    RuleVideoOutConnectionPrefNotSetDuringIDPSForiPodOutID = 470,
    RuleVideoOutDisabledAfterVideoOutPreferencesSetID = 471,
    RuleVideoOutNotTurnedOnDuringIDPSForiPodOutID = 472,
    RuleVideoOutPreferencesSeenWithoutVideoOutAccessoryClaimID = 473,
    RuleVideoOutRequiredCommandsNotSeenCAID = 474,
    RuleVideoOutTurnedOnWithoutVideoOutPreferencesID = 475,
    RuleVideoSignalFormatNotNTSCWhenEnteringiPodOutModeID = 476,
    RuleVideoSignalFormatPrefNotSetDuringIDPSForiPodOutID = 477,
    RuleVoiceOverCommandBeforeAccessoryCapsTokenID = 478,
    RuleVoiceOverCommandBeforeRetiPodOptionsForLingoID = 479,
    RuleVoiceOverEventLastSectionsDifferID = 480,
    RuleVoiceOverEventMultipleSectionsOutOfOrderID = 481,
    RuleVoiceOverEventWithMixedEventTypesID = 482,
    RuleVoiceOverMessagesNotSeenCAiAP2ID = 483,
    RuleVoiceOverOptionalMessagesNotSeenCAiAP2ID = 484,
    RuleVoiceOverRequiredCommandsNotSeenCAID = 485,
    RuleVoiceOverWithoutClaimID = 486,
    RuleVolumePollingOrInquiryWithoutAccessoryCapsTokenChecksVolumeID = 487,
    RuleWarnAboutRequestiPodModelNumID = 488,
    RuleWarnAboutRequestiPodSoftwareVersionID = 489,
    RuleWarnZeroCameraButtonStatusMissingID = 490,
    RuleWiFiMessagesNotSeenCAiAP2ID = 491,
    RuleWiFiNetworkLoginSharingRequiredCommandsNotSeenCAID = 492,
    RuleWorkoutFeatureDeprecatedID = 493,
    RuleWriteBeforeOpeniPodFeatureFileACKID = 494,
    RuleWriteToWrongFileHandleID = 495,
    RuleZeroCameraButtonStatusMissingID = 496,
// ----------------
    RuleCount
};
typedef UInt16 RuleID;

@interface RuleConstantsGenerated : NSObject

@property (class, nonatomic, readonly) NSArray<NSString *> *gRuleNames;
@property (class, nonatomic, readonly) NSArray<NSNumber *> *gRuleLevels;
@property (class, nonatomic, readonly) NSArray<NSNumber *> *gProductPlanRules;
@property (class, nonatomic, readonly) NSArray<NSNumber *> *gSpecPageNumbers;
@property (class, nonatomic, readonly) NSArray<NSString *> *gSpecSectionNames;
@property (class, nonatomic, readonly) NSArray<NSNumber *> *gErrorLevelBluetooth;
@property (class, nonatomic, readonly) NSArray<NSString *> *gSpecFilePredicates;
@property (class, nonatomic, readonly) NSArray<NSString *> *gSpecReferences;

@end
