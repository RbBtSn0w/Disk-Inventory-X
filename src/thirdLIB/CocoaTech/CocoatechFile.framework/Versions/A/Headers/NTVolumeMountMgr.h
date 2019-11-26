//
//  NTVolumeMountMgr.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 12/16/09.
//  Copyright 2009 Cocoatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NTVolumeMount;

@interface NTVolumeMountMgr : NTSingletonObject 
{
	NSMutableDictionary *volumeURLDictionary;
	NSMutableDictionary *activeVolumeMounters;  // used to avoid new request if it's still pending
}

- (void)mountVolumeWithScheme:(NSString*)scheme host:(NSString*)host path:(NSString*)path user:(NSString*)user password:(NSString*)password notifyWhenMounts:(NSString*)notificationName;
- (void)mountVolumeWithURL:(NSURL*)url user:(NSString*)user password:(NSString*)password notifyWhenMounts:(NSString*)notificationName;

@end

@interface NTVolumeMountMgr (UsedInternally)
- (void)volumeMountCompleted:(NTVolumeMount*)theMount;

- (NTFileDesc*)volumeForURL:(NSURL*)theUrl;
- (void)setVolume:(NTFileDesc*)volumeDesc forURL:(NSURL*)theURL;
@end

