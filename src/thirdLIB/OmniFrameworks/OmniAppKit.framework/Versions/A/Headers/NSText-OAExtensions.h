// Copyright 1997-2019 Omni Development, Inc. All rights reserved.
//
// This software may only be used and reproduced according to the
// terms in the file OmniSourceLicense.html, which should be
// distributed with this project and can also be found at
// <http://www.omnigroup.com/developer/sourcecode/sourcelicense/>.

#import <AppKit/NSText.h>

#import <AppKit/NSNibDeclarations.h> // For IBAction
#import <OmniAppKit/OAFindControllerTargetProtocol.h>

@interface NSText (OAExtensions) <OAFindControllerTarget>
- (IBAction)jumpToSelection:(id)sender;
- (NSUInteger)textLength;
- (void)appendTextString:(NSString *)string;
- (void)appendRTFData:(NSData *)data;
- (void)appendRTFDData:(NSData *)data;
- (void)appendRTFString:(NSString *)string;
- (NSData *)textData;
- (NSData *)rtfData;
- (NSData *)rtfdData;
- (void)setRTFData:(NSData *)rtfData;
- (void)setRTFDData:(NSData *)rtfdData;
- (void)setRTFString:(NSString *)string;
- (void)setTextFromString:(NSString *)aString;
- (NSString *)substringWithRange:(NSRange)aRange;
- (NSRange)trackingAndKerningRange; // tracking/kerning is special because it refers to space between characters, but the attribute is attached _to_ characters, so the tracking and kerning range is based on the selection range, but is usually different.
- (BOOL)findPattern:(id <OAFindPattern>)pattern backwards:(BOOL)backwards ignoreSelection:(BOOL)ignoreSelection;
@end
