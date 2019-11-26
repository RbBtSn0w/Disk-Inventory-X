//
//  NTFilePasteboardSource.h
//  Path Finder
//
//  Created by Steve Gehrman on Sun Feb 02 2003.
//  Copyright (c) 2003 CocoaTech. All rights reserved.
//

// NTFilePasteboardSource isn't included in the CocoaTech Frameworks any more
// (and there is no replacement class either).
// So I copied this class to the Disk Inventory X project.

@class NTFileDesc;

@interface NTFilePasteboardSource : NSObject
{
    NSArray *_descs;
}

+ (NTFilePasteboardSource*)files:(NSArray*)descArray toPasteboard:(NSPasteboard *)pboard types:(NSArray *)types;
+ (NTFilePasteboardSource*)file:(NTFileDesc*)desc toPasteboard:(NSPasteboard *)pboard types:(NSArray *)types;

+ (NSArray*)defaultTypes;
+ (NSArray*)imageTypes;

@end
