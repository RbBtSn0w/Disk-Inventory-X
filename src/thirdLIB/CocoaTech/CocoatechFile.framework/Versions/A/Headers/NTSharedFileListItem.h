//
//  NTSharedFileListItem.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 4/1/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NTVolumeMgrState;

@interface NTSharedFileListItem : NSObject <NSCoding>
{
	LSSharedFileListItemRef itemRef;
	NSString* name;
	NSNumber* uniqueID;
	
	id cachedURL;
	id cachedResolvedURL;
	NTVolumeMgrState* volumeMgrState;
	UInt64 networkStateID;
	NSString* listID;
}

@property (nonatomic, assign) LSSharedFileListItemRef itemRef;
@property (nonatomic, retain) NSString* name;
@property (nonatomic, retain) NSNumber* uniqueID;

+ (NTSharedFileListItem*)item:(LSSharedFileListItemRef)theItem listID:(NSString*)listID;

// mounts shared volume if a server, returns URL
- (NSURL*)resolvedURL;
- (NSURL*)url;  // returns nil if not resolvable without UI

- (NSImage*)imageWithSize:(int)theSize;
- (NSImage*)image;
@end
