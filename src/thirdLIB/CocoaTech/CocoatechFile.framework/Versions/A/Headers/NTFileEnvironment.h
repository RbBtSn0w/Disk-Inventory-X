//
//  NTFileEnvironment.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 7/8/05.
//  Copyright 2005 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

// short cut
#define FENV(x) [[NTFileEnvironment sharedInstance] x]

#define kNTFSEventLogNotification @"kNTFSEventLogNotification"
#define kNTDirectoryLogNotification @"kNTDirectoryLogNotification"
#define kNTKqueueLogNotification @"kNTKqueueLogNotification"
#define kNTBonjourLogNotification @"kNTBonjourLogNotification"
#define kNTGeneralLogNotification @"kNTGeneralLogNotification"

@interface NTFileEnvironment : NTSingletonObject 
{
	NSInteger disableCacheFlag;
	
	BOOL logKQueueEvents;
	BOOL logBonjourEvents;
	BOOL logDirectoryLists;
	BOOL logFSEvents;
	BOOL logGeneralEvents;
}

- (BOOL)disableCache;

// -----------------------------------------------------------
@property (nonatomic, assign) BOOL logFSEvents;
- (void)notify_FSEvent:(NSString*)eventType eventInfo:(NSString*)eventInfo;

// -----------------------------------------------------------
@property (nonatomic, assign) BOOL logDirectoryLists;
- (void)notify_DirectoryList:(NSString*)thePath list:(NSArray*)theList state:(NSString*)theState;

// -----------------------------------------------------------
@property (nonatomic, assign) BOOL logKQueueEvents;
- (void)notify_KQueueEvent:(NSString*)eventInfo;

// -----------------------------------------------------------
@property (nonatomic, assign) BOOL logBonjourEvents;
- (void)notify_BonjourEvent:(NSString*)eventInfo;

// -----------------------------------------------------------
@property (nonatomic, assign) BOOL logGeneralEvents;
- (void)notify_GeneralEvent:(NSString*)eventInfo;

@end
