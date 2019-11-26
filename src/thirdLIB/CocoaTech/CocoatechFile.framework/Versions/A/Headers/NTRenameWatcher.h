//
//  NTRenameWatcher.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 10/27/09.
//  Copyright 2009 Cocoatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NTFileDesc, NTFSWatcher, NTRenameWatcher;

@protocol NTRenameWatcherDelegateProtocol <NSObject>
- (void)renameWatcher:(NTRenameWatcher*)watcher renamed:(NTFileDesc*)theDesc;
@end

@interface NTRenameWatcher : NSObject 
{
	id<NTRenameWatcherDelegateProtocol> delegate;
	
	NTFileDesc* desc; 
	NTFSWatcher* fsWatcher;
	
	BOOL sendingDelayedNotification;
}

+ (NTRenameWatcher*)watcher:(id<NTRenameWatcherDelegateProtocol>)delegate 
					   desc:(NTFileDesc*)theDesc;
- (void)clearDelegate;

@end
