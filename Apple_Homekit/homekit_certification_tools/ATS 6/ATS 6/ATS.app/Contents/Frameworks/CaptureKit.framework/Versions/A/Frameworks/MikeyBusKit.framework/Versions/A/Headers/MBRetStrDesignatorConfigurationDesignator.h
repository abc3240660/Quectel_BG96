//
//  MBRetStrDesignatorConfigurationDesignator.h
//  MikeyBusKit
//
//  Created by Vinod Madigeri on 11/5/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <MikeyBusKit/MBConfigurationDesignatorPacket.h>

/*
 String Keys to be able to access each value inside parsedPayloadFields
 */
extern NSString * const MBRetStringIndexKey;
extern NSString * const MBRetStringValueKey;


@interface MBRetStrDesignatorConfigurationDesignator : MBConfigurationDesignatorPacket

@end