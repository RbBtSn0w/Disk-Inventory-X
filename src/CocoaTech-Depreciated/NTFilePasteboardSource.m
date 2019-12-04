//
//  NTFilePasteboardSource.m
//  Path Finder
//
//  Created by Steve Gehrman on Sun Feb 02 2003.
//  Copyright (c) 2003 CocoaTech. All rights reserved.
//

#import "NTFilePasteboardSource.h"
#import <OmniAppKit/OAPasteboardHelper.h>

// SNG 666 add NSPICTPboardType

@interface NTFilePasteboardSource (Private)
- (NSArray*)pasteboardTypes:(NSArray *)types;
@end

@implementation NTFilePasteboardSource

- (id)initWithDescs:(NSArray*)descs;
{
    self = [super init];

    _descs = [descs retain];

    return self;
}

- (void)dealloc;
{
    [_descs release];

    [super dealloc];
}

+ (NSArray*)defaultTypes;
{
    return [NSArray arrayWithObjects:
        NSTIFFPboardType,
        NSPDFPboardType,
        NSPostScriptPboardType,

        NSRTFPboardType,
        NSRTFDPboardType,
        NSHTMLPboardType,

        NSFileContentsPboardType,

        NSFilenamesPboardType,
        NSStringPboardType,
        nil];
}

+ (NSArray*)imageTypes;
{
    return [NSArray arrayWithObjects:
        NSTIFFPboardType,
        NSPDFPboardType,
        NSPostScriptPboardType,
        nil];
}

+ (NTFilePasteboardSource*)file:(NTFileDesc*)desc toPasteboard:(NSPasteboard *)pboard types:(NSArray *)types;
{
    return [NTFilePasteboardSource files:[NSArray arrayWithObject:desc] toPasteboard:pboard types:types];
}

+ (NTFilePasteboardSource*)files:(NSArray*)descArray toPasteboard:(NSPasteboard *)pboard types:(NSArray *)types;
{
    NTFilePasteboardSource* source = [[[NTFilePasteboardSource alloc] initWithDescs:descArray] autorelease];
    OAPasteboardHelper *helper;
    NSArray* pasteboardTypes = [source pasteboardTypes:types];

    if (pasteboardTypes)
    {
        helper = [OAPasteboardHelper helperWithPasteboard:pboard];

        // the helper is retained for as long as it stays in the pasteboard, the source is retained by the helper
        [helper declareTypes:pasteboardTypes owner:source];
    }

    return source;
}

@end

@implementation NTFilePasteboardSource (Private)

- (NSArray*)pasteboardTypes:(NSArray *)types;
{
    if ([_descs count])
    {
        NTFileDesc* desc = [_descs objectAtIndex:0];

        // figure out what type of file the current selection is
        if (desc)
        {
            NSMutableArray *pasteTypes = [NSMutableArray array];
            NTFileTypeIdentifier* identifier = [desc typeIdentifier];
            NSUInteger i, cnt = [types count];
            NSString* type;

            for (i=0;i<cnt;i++)
            {
                type = [types objectAtIndex:i];

                if ([type isEqualToString:NSFilenamesPboardType])
                    [pasteTypes addObject:type];
                else if ([type isEqualToString:NSStringPboardType])
                    [pasteTypes addObject:type];
                else if ([type isEqualToString:NSFileContentsPboardType])
                    [pasteTypes addObject:type];

                else if ([type isEqualToString:NSPostScriptPboardType] && [identifier isPostscript])
                    [pasteTypes addObject:type];
                else if ([type isEqualToString:NSTIFFPboardType]) // we use the icon if not an image, so don't check isImage && [identifier isImage])
                    [pasteTypes addObject:type];
                else if ([type isEqualToString:NSRTFPboardType] && [identifier isRTF])
                    [pasteTypes addObject:type];
                else if ([type isEqualToString:NSRTFDPboardType] && [identifier isRTFD])
                    [pasteTypes addObject:type];
                else if ([type isEqualToString:NSHTMLPboardType] && [identifier isHTML])
                    [pasteTypes addObject:type];
                else if ([type isEqualToString:NSPDFPboardType] && [identifier isPDF])
                    [pasteTypes addObject:type];
            }

            if ([pasteTypes count])
                return pasteTypes;
        }
    }

    return nil;
}

- (void)pasteboard:(NSPasteboard *)pboard provideDataForType:(NSString *)type
{
    if (_descs && [_descs count])
    {
        NTFileDesc* desc = [_descs objectAtIndex:0];

        if (desc)
        {
            NTFileTypeIdentifier* identifier = [desc typeIdentifier];

            if ([type isEqualToString:NSFilenamesPboardType])
            {
                NSUInteger i, cnt = [_descs count];
                NSMutableArray* pathsArray = [NSMutableArray array];

                for (i=0;i<cnt;i++)
                    [pathsArray addObject:[[_descs objectAtIndex:i] path]];

                [pboard setPropertyList:pathsArray forType:NSFilenamesPboardType];
            }
            else if ([type isEqualToString:NSStringPboardType])
            {
                // set the path
                [pboard setString:[desc path] forType:NSStringPboardType];
            }
            else if ([type isEqualToString:NSFileContentsPboardType])
            {
                // write the contents
                [pboard writeFileContents:[desc path]];
            }
            else if ([type isEqualToString:NSPostScriptPboardType])
            {
                if ([identifier isPostscript])
                    [pboard setData:[NSData dataWithContentsOfFile:[desc path]] forType:NSPostScriptPboardType];
            }
            else if ([type isEqualToString:NSTIFFPboardType])
            {
                if ([identifier isTIFF])
                    [pboard setData:[NSData dataWithContentsOfFile:[desc path]] forType:NSTIFFPboardType];
                else if ([identifier isImage])
                {
                    // open the image and return TIFFRepresentation
                    NSImage *image = [[[NSImage alloc] initWithContentsOfFile:[desc path]] autorelease];

                    if (image)
                    {
                        NSData* data = [image TIFFRepresentation];

                        if (data)
                            [pboard setData:data forType:NSTIFFPboardType];
                    }
                }
                else // else send the icon
                {
                    // open the image and return TIFFRepresentation
                    NSImage* image = [NSImage iconRef:[[desc icon] iconRef] toImage:128 label:[desc label] select:NO];

                    if (image)
                    {
                        NSData* data = [image TIFFRepresentation];

                        if (data)
                            [pboard setData:data forType:NSTIFFPboardType];
                    }                    
                }
            }
            else if ([type isEqualToString:NSRTFPboardType])
            {
                if ([identifier isRTF])
                    [pboard setData:[NSData dataWithContentsOfFile:[desc path]] forType:NSRTFPboardType];
            }
            else if ([type isEqualToString:NSRTFDPboardType])
            {
                if ([identifier isRTFD])
                {
                    NSFileWrapper *tempRTFDData = [[[NSFileWrapper alloc] initWithPath:[desc path]] autorelease];
                    [pboard setData:[tempRTFDData serializedRepresentation] forType:NSRTFDPboardType];
                }
            }
            else if ([type isEqualToString:NSHTMLPboardType])
            {
                if ([identifier isHTML])
                    [pboard setData:[NSData dataWithContentsOfFile:[desc path]] forType:NSHTMLPboardType];
            }
            else if ([type isEqualToString:NSPDFPboardType])
            {
                if ([identifier isPDF])
                    [pboard setData:[NSData dataWithContentsOfFile:[desc path]] forType:NSPDFPboardType];
            }
        }
    }
}

@end
