//
//  CaptureConfigurationSettingsViewController.h
//  ATSMacApp
//
//  Created by Rafael Lucena on 1/8/14.
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <CaptureKit/CaptureConfigurationAssistantViewController.h>

@interface CaptureConfigurationSettingsViewController : CaptureConfigurationAssistantViewController

/*!
 @method     initWithDataModel:
 @abstract   initializes a CaptureConfigurationBluetoothCaptureConfigurationViewController view controller.
 @param      dataModel
             The capture configuration data model configured by the presented view.
 @return     A CaptureConfigurationBluetoothCaptureConfigurationViewController configured to present a view that presents the saved bluetooth capture configurations.
 
 This is the designated initializer.
 */
- (id)initWithDataModel:(CaptureConfiguration *)dataModel;

/*!
 @method     viewControllerWithDataModel:
 @abstract   creates to initialize a CaptureConfigurationBluetoothCaptureConfigurationViewController view controller
 @param      dataModel
             The capture configuration data model configured by the presented view.
 @return     A CaptureConfigurationBluetoothCaptureConfigurationViewController configured to present a view that presents the saved bluetooth capture configurations.
 */
+ (id)viewControllerWithDataModel:(CaptureConfiguration *)dataModel;

@end
