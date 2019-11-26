//
//  NTFileDesc-AccessExtensions.m
//  Disk Inventory X
//
//  Created by Tjark Derlien on 03.10.04.
//  Copyright 2004 Tjark Derlien. All rights reserved.
//

#import "NTFileDesc-AccessExtensions.h"
#import <CocoaTechFile/NTFileDesc-Private.h>
#import <CocoaTechFile/NTFileDescData.h>
#import <CocoaTechFile/NTFileDesc.h>

@implementation NTFileDesc(AccessExtensions)

- (void) setKindString: (NSString*) kindString
{
 	[[self cache] setKind: kindString];
}

- (BOOL) isKindStringSet
{
	return [self kindString_initialized];
}

//PathFinders spawns a thread to calculate a folder's size in the background.
//We calculate the size during the folder traversal so we don't need the thread.
//(we just add the logical sizes of the data and resource forks to get a file's size)
- (void) setSize: (UInt64) size
{
	[self setFolderSize: size physicalSize: size];
}

//this method tries to avoid to call LSCopyDisplayNameForRef (in NTFileDesc.displayName)
- (NSString*) displayName_fast
{
	//directories (especially packages) may have localized names, so we don't do any optimization in this case
	if ( [self displayName_initialized] || [self isDirectory] )
		return [self displayName];
	
	//if a file's name has no extension or if we know wether the extennsion is hidden, we can determine
	//the display name without any help, otherwise call [self displayName]
	BOOL nameHasExtension = NO;
	
	NSString *name = [self name];
	NSRange extensionRange = {0,0};
	if ( [[self cache] extension_initialized: nil] )
	{
		//if we know the extenson already, use that
		NSUInteger extensionLength = [[self extension] length];
		nameHasExtension = (extensionLength > 0);
		if ( nameHasExtension )
		{
			//calculate the extenson's position and length so that the file name without it's extension
			//can be build below
			extensionRange.location = [name length] - extensionLength -1;
			extensionRange.length = extensionLength;
		}
	}
	else
	{
		//determine the extension by ourself ([self extension] would allocate the extension and we don't want that here)
		extensionRange = [name rangeOfString: @"." options: NSLiteralSearch | NSBackwardsSearch];
		if ( extensionRange.location != NSNotFound && extensionRange.location > 0 )
			// search for a space (only if the part after the period contains no space it is considered as a valid file name extension)
			nameHasExtension = [name rangeOfString:@" " options: NSLiteralSearch range: extensionRange].location == NSNotFound;
	}
	
	if ( !nameHasExtension || [self itemInfo_initialized] )
	{
		NSString *displayName = nil;
		if ( !nameHasExtension || ![self isExtensionHidden] )
			displayName = name;
		else
			displayName = [name substringToIndex: extensionRange.location];
		
		[[self cache] setDisplayName: displayName];
		
		return displayName;
	}
	else
		return [self displayName];
}

@end
