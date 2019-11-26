//
//  NTVolumeMgr.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 2/28/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NTVolumeSpec;

@interface NTVolumeMgr : NTSingletonObject 
{
	NTVolumeMgrState* state;
	NSArray* volumeSpecArray;
	NSMutableDictionary* volumeSpecDictionary;	
	NSArray* mountPoints;
}

- (NSArray*)volumes;
- (NSArray*)volumeSpecs;
- (NSArray*)freshVolumeSpecs;

// get a volumespec from the cache
- (NTVolumeSpec *)volumeSpecForRefNum:(FSVolumeRefNum)vRefNum;

@end

@interface NTVolumeMgr (MountPoints)
- (NSString*)relativePath:(NSString*)thePath outMountPoint:(NSString**)outMountPoint;
@end
