//
//  NTFSEventClient.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 4/23/10.
//  Copyright 2010 Cocoatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#define kNTComputerEventClient @"NTComputerEventClient"

@class NTFileSystemEventMessage, NTFileSystemEventCenterClient;

#define kFSEventClient_uniqueIDKey @"uniqueID"
#define kFSEventClient_messagesKey @"messages"

@interface NTFSEventClient : NSObject {
	NSNumber* uniqueID;
	NTFileSystemEventCenterClient* eventCenterClient;
}

@property (readonly, nonatomic, retain) NSNumber *uniqueID;

+ (NTFSEventClient*)client:(NTMessageProxy*)theDelegateProxy folder:(NTFileDesc*)theFolder;
+ (NTFSEventClient*)client:(NTMessageProxy*)theDelegateProxy folder:(NTFileDesc*)theFolder includeSubfolders:(BOOL)includeSubfolders;

+ (void)manuallyRefreshDirectory:(NTFileDesc*)directory;

- (NTFileDesc*)folder;

@end
