//
//  NTSetFileAttribute.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 8/20/09.
//  Copyright 2009 Cocoatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

typedef enum NTStateValue
{
	NTMixedState = -1,  // toggle
	NTOffState   =  0,
	NTOnState    =  1    
} NTStateValue;

@interface NTSetFileAttribute : NSObject {
}

// get perms
+ (unsigned)permissions:(int*)outUser group:(int*)outGroup path:(NSString*)path;

+ (BOOL)setPermissions:(unsigned long)permissions path:(NSString*)path;
+ (BOOL)setStickyBit:(BOOL)set path:(NSString*)path;

+ (BOOL)setGroup:(int)groupID path:(NSString*)path;
+ (BOOL)setOwner:(int)ownerID path:(NSString*)path;

+ (BOOL)setModificationDate:(NSDate*)date path:(NSString*)path;
+ (BOOL)setCreationDate:(NSDate*)date path:(NSString*)path;
+ (BOOL)setAttributeModificationDate:(NSDate*)date path:(NSString*)path;

+ (BOOL)setLock:(NSNumber*)set path:(NSString*)path;

+ (BOOL)setType:(OSType)type path:(NSString*)path;
+ (BOOL)setCreator:(OSType)creator path:(NSString*)path;
+ (BOOL)setFinderPosition:(NSPoint)point path:(NSString*)path;

+ (BOOL)setLength:(UInt64)length path:(NSString*)path;
+ (BOOL)setExtensionHidden:(NSNumber*)set path:(NSString*)path;

+ (void)setSpotlightComments:(NSString*)comments path:(NSString*)path;

// ## Finder flags
// kIsOnDesk                     = 0x0001, /* Files and folders (System 6) */
// kColor                        = 0x000E, /* Files and folders */
// kIsShared                     = 0x0040, /* Files only (Applications only) */
// kHasNoINITs                   = 0x0080, /* Files only (Extensions/Control Panels only) */
// kHasBeenInited                = 0x0100, /* Files only */
// kHasCustomIcon                = 0x0400, /* Files and folders */
// kIsStationery                 = 0x0800, /* Files only */
// kNameLocked                   = 0x1000, /* Files and folders */
// kHasBundle                    = 0x2000, /* Files only */
// kIsInvisible                  = 0x4000, /* Files and folders */
// kIsAlias                      = 0x8000 /* Files only */
+ (BOOL)set:(NSNumber*)set finderFlag:(short)finderFlag path:(NSString*)path;
+ (BOOL)setLabel:(int)label path:(NSString*)path;

@end

