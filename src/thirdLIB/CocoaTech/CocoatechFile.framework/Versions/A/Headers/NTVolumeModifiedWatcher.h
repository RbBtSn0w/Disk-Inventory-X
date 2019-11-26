//
//  NTVolumeModifiedWatcher.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 7/7/08.
//  Copyright 2008 Cocoatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NTFSEventClient;

// manually refreshes computer list if more than .5 K 
#define kNTVolumeFreespaceModifiedNotification @"NTVolumeFreespaceModifiedNotification"

@interface NTVolumeModifiedWatcher : NTSingletonObject 
{
	NTMessageProxy* proxy;
	NTFSEventClient* computerWatcher;
	NSArray *volumeWatchers;
	NSDictionary* volumeFreespaceCache;

	BOOL rescanningAsync;
	BOOL rebuildingAsync;
}

@end
