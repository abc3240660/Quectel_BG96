//
//  APHTTPRequest.h
//  TrafficKit
//
//  Created by Mark Hamlin on 5/28/13.
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
@class APTCPFlow;

@interface APHTTPRequest : NSObject

/*!
 @property  errorDescription
 @abstract  Error description for the request
 */
@property (nonatomic, strong) NSString *errorDescription;

/*!
 @property  flow
 @abstract  The TCP flow this was parsed from
 */
@property (nonatomic, strong) APTCPFlow *flow;

/*!
 @property  senderIsZero
 @abstract  If the sender is endpoint 0 of the flow
 */
@property (nonatomic, assign) BOOL senderIsZero;

/*!
 @property  method
 @abstract  The request method (ex. @"GET", @"POST", etc)
 */
@property (nonatomic, strong) NSString *method;

/*!
 @property  resource
 @abstract  The resource URL (ex. @"/index.html")
 */
@property (nonatomic, strong) NSString *resource;

/*!
 @property  protocol
 @abstract  The protocol used (ex. @"HTTP", @"RTSP")
 */
@property (nonatomic, strong) NSString *protocol;

/*!
 @property  version
 @abstract  The version of the protocol used (@"1.1")
 */
@property (nonatomic, strong) NSString *version;

/*!
 @property  header
 @abstract  The header dictionary
 */
@property (nonatomic, strong) NSDictionary *header;

/*!
 @property  content
 @abstract  The content payload, if any
 */
@property (nonatomic, strong) NSData *content;

/*!
 @property  parsedContent
 @abstract  The parsed content payload, if any
 */
@property (nonatomic, strong) id parsedContent;

/*!
 @method    senderAddress
 @abstract  The sender's address
 */
- (NSString *)senderAddress;

/*!
 @method    senderPort
 @abstract  The sender's port
 */
- (unsigned short)senderPort;

/*!
 @method    recipientAddress
 @abstract  The recipient's address
 */
- (NSString *)recipientAddress;

/*!
 @method    recipientPort
 @abstract  The recipient's port
 */
- (unsigned short)recipientPort;

@end
