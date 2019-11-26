//
//  NTVolumeUnmounter.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 1/4/09.
//  Copyright 2009 Cocoatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NTFileDesc;

@interface NTVolumeUnmounter : NSObject
{
	FSVolumeOperation volumeOp;

    FSVolumeEjectUPP ejectUPP;
    FSVolumeUnmountUPP unmountUPP;
	
    NTFileDesc *desc;
	
}

+ (void)unmountVolume:(NTFileDesc*)desc;
+ (void)ejectVolume:(NTFileDesc*)desc;

// option key ejects all, control key ejects only this volume, pass 0 to ask user
+ (void)ejectVolumeWithModifiers:(NTFileDesc*)theDesc;

// this was added to handle a list of volumes, for example a drag to trash, or CM click
+ (void)ejectVolumesWithModifiers:(NSArray*)theDescs;

@end
