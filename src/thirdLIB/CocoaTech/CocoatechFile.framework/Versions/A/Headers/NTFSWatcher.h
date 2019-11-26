//
//  NTFSWatcher.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 7/6/05.
//  Copyright 2005 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NTFileDesc, NTFSWatcher;

@protocol NTFSWatcherDelegateProtocol <NSObject>
- (void)watcher:(NTFSWatcher*)watcher itemsChanged:(NSArray*)descs;
@end

@interface NTFSWatcher : NSObject 
{
	id<NTFSWatcherDelegateProtocol> delegate;

	NTMessageProxy* proxy;
	NSMutableArray* items; 
	
	// combine notifications
	NSMutableDictionary* descsToNotify;	
	BOOL sendingDelayedNotification;
}

+ (NTFSWatcher*)watcher:(id<NTFSWatcherDelegateProtocol>)delegate;
- (void)clearDelegate;

- (void)refreshDescs;  // update the descs so we can check for hasBeenModified etc

	// replaces (removeAll, add)
- (void)watchItems:(NSArray*)theDescs;
- (void)watchItem:(NTFileDesc*)theDesc;

	// files/directories I'm watching
- (NSArray*)watchedDescs;

@end
