//
//  NTStringShare.h
//  CocoatechFile
//
//  Created by Steve Gehrman on Sat Dec 06 2003.
//  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NTStringShare : NTSingletonObject
{    
	NSLock *kindLock;
	NSLock *extensionLock;
	
    NSMutableSet* kindStrings;
    NSMutableSet* extensionStrings;
	
	NSString* packageKindString;
	NSString* volumeKindString;
	NSString* folderKindString;
	NSString* symbolicLinkKindString;
	NSString* documentKindString;	
}

- (NSString*)sharedKindString:(NSString*)kindString;
- (NSString*)sharedExtensionString:(NSString*)extensionString;

@property (readonly, nonatomic, retain) NSString *packageKindString;
@property (readonly, nonatomic, retain) NSString *volumeKindString;
@property (readonly, nonatomic, retain) NSString *folderKindString;
@property (readonly, nonatomic, retain) NSString *symbolicLinkKindString;
@property (readonly, nonatomic, retain) NSString *documentKindString;

@end
