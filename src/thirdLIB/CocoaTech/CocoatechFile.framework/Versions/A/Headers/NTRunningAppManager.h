//
//  NTRunningAppManager.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 9/13/09.
//  Copyright 2009 Cocoatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>


#define NTRM (NTRunningAppManager*)[NTRunningAppManager sharedInstance]

// sends out this notification when an app launches or terminates
#define kNTRunningAppManagerNotification @"NTRunningAppManagerNotification"

@interface NTRunningAppManager : NTSingletonObject {
	NTKVObserverProxy* observerProxy;
	NSMutableArray *relaunchArray;
	
	NSArray *applications;
	BOOL sentNotificationAfterDelay;
}

@property (readonly, retain) NSArray *applications;

- (NSArray*)regularApplications;
- (NSArray*)backgroundApplications;

- (void)showAll;
- (void)quitAll;

- (void)hideFront;
- (void)hideOthers;
- (void)hideAllExcept:(NSRunningApplication*)dontHideProcess;

- (NSRunningApplication*)applicationWithURL:(NSURL*)theURL;
- (NSRunningApplication*)applicationWithBundleIdentifier:(NSString*)theBundleIdentifier;

- (NSArray*)applicationsToDescs:(NSArray*)applications;

- (void)relaunch:(NSRunningApplication*)theRunningApplication;
@end
