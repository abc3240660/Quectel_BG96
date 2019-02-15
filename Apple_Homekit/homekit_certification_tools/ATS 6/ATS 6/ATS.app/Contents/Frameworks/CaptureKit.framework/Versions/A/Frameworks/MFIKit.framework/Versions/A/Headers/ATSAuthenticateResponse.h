//
//  ATSAuthenticateResponse.h
//  ATSMacApp
//
//  Created by Carlos Frederico Azevedo on 8/8/14.
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ATSResponse.h"

@interface ATSAuthenticateResponse : ATSResponse

@property (nonatomic) BOOL isValid;

+ (ATSAuthenticateResponse *)authenticateResponseWithDictionary:(NSDictionary *)dictionary;

@end
