//
//  NTThumbnail.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 2/15/05.
//  Copyright 2005 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NTThumbnail : NSObject 
{
	BOOL isValid;
		
	NSImage* image;
	NSImage* selectedImage;
	BOOL drawFrame;
	NSSize maxSize;
}

@property (readonly, retain) NSImage* image;
@property (readonly, assign) BOOL isValid;
@property (readonly, assign) NSSize maxSize;

+ (NTThumbnail*)thumbnailWithDesc:(NTFileDesc*)imageFile
						   asIcon:(BOOL)asIcon
						  maxSize:(NSSize)maxSize;

+ (NTThumbnail*)thumbnailWithImage:(NSImage*)image;

- (NSRect)imageRectForRect:(NSRect)rect;

- (void)drawInRect:(NSRect)rect flipped:(BOOL)flipped selected:(BOOL)selected;

@end
