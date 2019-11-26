/*
	ImageAndTextCell.m
	Copyright (c) 2001-2002, Apple Computer, Inc., all rights reserved.
	Author: Chuck Pisula

	Milestones:
	Initially created 3/1/01

        Subclass of NSTextFieldCell which can display text and an image simultaneously.
*/

/*
 IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc. ("Apple") in
 consideration of your agreement to the following terms, and your use, installation, 
 modification or redistribution of this Apple software constitutes acceptance of these 
 terms.  If you do not agree with these terms, please do not use, install, modify or 
 redistribute this Apple software.
 
 In consideration of your agreement to abide by the following terms, and subject to these 
 terms, Apple grants you a personal, non-exclusive license, under Apple�s copyrights in 
 this original Apple software (the "Apple Software"), to use, reproduce, modify and 
 redistribute the Apple Software, with or without modifications, in source and/or binary 
 forms; provided that if you redistribute the Apple Software in its entirety and without 
 modifications, you must retain this notice and the following text and disclaimers in all 
 such redistributions of the Apple Software.  Neither the name, trademarks, service marks 
 or logos of Apple Computer, Inc. may be used to endorse or promote products derived from 
 the Apple Software without specific prior written permission from Apple. Except as expressly
 stated in this notice, no other rights or licenses, express or implied, are granted by Apple
 herein, including but not limited to any patent rights that may be infringed by your 
 derivative works or by other works in which the Apple Software may be incorporated.
 
 The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO WARRANTIES, 
 EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, 
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS 
 USE AND OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.
 
 IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR CONSEQUENTIAL 
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, 
 REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND 
 WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR 
 OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#import "ImageAndTextCell.h"
//#import <OmniAppKit/NSString-OAExtensions.h>
#import <OmniFoundation/NSString-OFUnicodeCharacters.h>

#define TEXT_OFFSET	10	//space between image and text
#define IMAGE_OFFSET	5	//space between left side of cell rect and image

@implementation ImageAndTextCell

+ (id) cell
{
	return [[[[self class] alloc] init] autorelease];
}

- (void)dealloc
{
    [_image release];
    _image = nil;
    [super dealloc];
}

- copyWithZone:(NSZone *)zone
{
    ImageAndTextCell *cell = (ImageAndTextCell *)[super copyWithZone:zone];
    cell->_image = [_image retain];
    return cell;
}

- (void)setImage:(NSImage *)anImage {
    if (anImage != _image)
	{
        [_image release];
        _image = [anImage retain];
    }
}

- (NSImage *)image
{
    return _image;
}

- (NSRect)imageFrameForCellFrame:(NSRect)cellFrame
{
    if (_image != nil) {
        NSRect imageFrame;
        imageFrame.size = [_image size];
        imageFrame.origin = cellFrame.origin;
        imageFrame.origin.x += IMAGE_OFFSET;
        imageFrame.origin.y += ceil((cellFrame.size.height - imageFrame.size.height) / 2);
        return imageFrame;
    }
    else
        return NSZeroRect;
}

- (void)editWithFrame:(NSRect)aRect inView:(NSView *)controlView editor:(NSText *)textObj delegate:(id)anObject event:(NSEvent *)theEvent
{
    NSRect textFrame, imageFrame;
    NSDivideRect (aRect, &imageFrame, &textFrame, TEXT_OFFSET + [_image size].width, NSMinXEdge);
	
    [super editWithFrame: textFrame inView: controlView editor:textObj delegate:anObject event: theEvent];
}

- (void)selectWithFrame:(NSRect)aRect inView:(NSView *)controlView editor:(NSText *)textObj delegate:(id)anObject start:(NSInteger)selStart length:(NSInteger)selLength
{
    NSRect textFrame, imageFrame;
    NSDivideRect (aRect, &imageFrame, &textFrame, TEXT_OFFSET + [_image size].width, NSMinXEdge);
    [super selectWithFrame: textFrame inView: controlView editor:textObj delegate:anObject start:selStart length:selLength];
	
}

+ (NSString *)stringByTruncatingToWidth:(CGFloat)width withFont:(NSFont *)font withString:(NSString *)string
{
    NSDictionary *attribs = @{ NSFontAttributeName : font };
    
    // Make sure string is longer than requested width
    if ([string sizeWithAttributes:attribs].width > width)
    {
        NSString *ellipsis = [NSString horizontalEllipsisString];
        
       // Accommodate for ellipsis we�ll tack on the end
        width -= [ellipsis sizeWithAttributes:attribs].width;
        
        if ( width < 0 )
        {
            // not enough space to show anything; just show "..."
            return ellipsis;
        }
        else
        {
            // Create copy that will be the returned result
            NSMutableString *truncatedString = [[string mutableCopy] autorelease];

            // Get range for last character in string
            NSRange range = {truncatedString.length - 1, 1};
            
            // Loop, deleting characters until string fits within width
            while ( [truncatedString sizeWithAttributes:attribs].width > width
                   && range.location > 0 )
            {
                // Delete character at end
                [truncatedString deleteCharactersInRange:range];
                
                // Move back another character
                range.location--;
            }
            
            // Append ellipsis
            [truncatedString replaceCharactersInRange:range withString:ellipsis];
            
            return truncatedString;
        }
    }
    else
        return string;
}

- (void)drawWithFrame:(NSRect)cellFrame inView:(NSView *)controlView
{
    if (_image != nil)
	{
        NSSize	imageSize = [_image size];
        NSRect	imageFrame;

        NSDivideRect(cellFrame, &imageFrame, &cellFrame, TEXT_OFFSET + imageSize.width, NSMinXEdge);
        if ([self drawsBackground])
		{
            [[self backgroundColor] set];
            NSRectFill(imageFrame);
        }
        imageFrame.origin.x += IMAGE_OFFSET;
        imageFrame.size = imageSize;

        if ([controlView isFlipped])
            imageFrame.origin.y += ceil((cellFrame.size.height + imageFrame.size.height) / 2);
        else
            imageFrame.origin.y += ceil((cellFrame.size.height - imageFrame.size.height) / 2);

//        [_image drawInRect: imageFrame
//                   fromRect: NSZeroRect/*entire image*/
//                  operation: NSCompositeSourceOver
//                   fraction: 1.0/*opaque*/];
        
        [_image compositeToPoint:imageFrame.origin operation:NSCompositeSourceOver];
    }
    
    NSString *truncatedString = [ImageAndTextCell stringByTruncatingToWidth: NSWidth(cellFrame)
                                                                       withFont: [self font]
                                                                     withString: [self stringValue]];

    [self setStringValue: truncatedString];

/*
	ThemeFontID themeFont = kThemeSystemFont;
	float fontSize = [[self font] pointSize];
	
	if ( fontSize == [NSFont systemFontSize] )
		themeFont = kThemeSystemFont;
	else if ( fontSize == [NSFont smallSystemFontSize] )
		themeFont = kThemeSmallSystemFont;
	else
		LOG( @"ImageTextCell can't determine appropriate truncating method" );

    [self setStringValue: [[self stringValue] truncatedStringWithMaxWidth: NSWidth(cellFrame)
															  themeFontID: themeFont
														   truncationMode: truncEnd]];
 */

    [super drawWithFrame:cellFrame inView:controlView];
}

- (NSSize)cellSize
{
    NSSize cellSize = [super cellSize];
    cellSize.width += (_image != nil ? [_image size].width : 0) + TEXT_OFFSET;
    return cellSize;
}

@end
