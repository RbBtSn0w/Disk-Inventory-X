//
//  NSImage-CocoatechFile.h
//  CocoatechFile
//
//  Created by sgehrman on Fri Oct 12 2001.
//  Copyright (c) 2001 CocoaTech. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>

@class NTFileDesc;

@interface NSImage (CocoatechFile)

+ (NSImage*)iconRef:(IconRef)iconRef toImage:(int)size;
+ (NSImage*)iconRef:(IconRef)iconRef toImage:(int)size select:(BOOL)select;
+ (NSImage*)iconRef:(IconRef)iconRef toImage:(int)size label:(int)label select:(BOOL)select;
+ (NSImage*)iconRef:(IconRef)iconRef toImage:(int)size label:(int)label select:(BOOL)select alpha:(float)alpha;
+ (NSImage*)iconRef:(IconRef)iconRef toImage:(int)size label:(int)label highlight:(BOOL)highlight; // used when clicking on an image button
+ (NSImage*)iconRef:(IconRef)iconRef
			toImage:(int)size 
			  label:(int)label 
			 select:(BOOL)select
			  alpha:(float)alpha
		  alignment:(int)alignment;

// add a badge to an image, badge added to all imageReps
- (NSImage*)imageWithBadge:(NSImage*)icon;

- (void)drawIconInRect:(NSRect)theRect aliasBadge:(BOOL)aliasBadge;

// call from thread, could be slow
// if a movie, get the poster image, if an audio file try to get the cover art, if anything else, just returns the icon
+ (NSImage*)quickLookPreviewImageOrIcon:(NTFileDesc*)desc 
								ofSize:(NSSize)ofSize 
								 asIcon:(BOOL)asIcon;

+ (NSImage *)quickLookPreviewImage:(NTFileDesc*)desc
							ofSize:(NSSize)size
							asIcon:(BOOL)icon;
@end
