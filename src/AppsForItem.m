//
//  AppsForItem.m
//  Disk Inventory X new
//
//  Created by Tjark Derlien on 20.01.06.
//  Copyright 2006 Tjark Derlien. All rights reserved.
//

#import "AppsForItem.h"
#import <OmniFoundation/NSMutableArray-OFExtensions.h>

@interface AppsForItem(Private)

+ (NSArray*)applicationURLsForItemURL:(NSURL*)inItemURL;
- (BOOL) checkAppDesc: (NTFileDesc*) appDesc checkDefaultApp: (BOOL) checkDefApp;

@end


@implementation AppsForItem

+ (id) appsForItemDesc: (NTFileDesc*) item
{
	AppsForItem *appsForFile = [[[self class] alloc] initWithItemDesc: item];
		
	return [appsForFile autorelease];
}

- (id) initWithItemDesc: (NTFileDesc*) item
{
	self = [super init];
	if ( self != nil )
	{
		_itemDesc = [[item newDesc] retain];
	}
	
	return self;
}

- (void) dealloc
{
	[_itemDesc release];
	[_defaultAppDesc release];
	[_additionalAppDescs release];	
	
	[super dealloc];
}

- (NTFileDesc*) defaultAppDesc //may return nil
{
	if ( _defaultAppDesc == nil )
	{
		_defaultAppDesc = (id) [NSNull null]; //retain not necessary for NSNull
		
		LSRolesMask RoleMask = kLSRolesViewer | kLSRolesEditor;
		FSRef appRef;
		if ( LSGetApplicationForItem( [[self itemDesc] FSRefPtr], RoleMask, &appRef, NULL ) == noErr )
		{
			NTFileDesc *appDesc = [NTFileDesc descFSRef: &appRef];
			if ( [self checkAppDesc: appDesc checkDefaultApp: NO] )
				_defaultAppDesc = [appDesc retain];
		}
	}
	
	return (_defaultAppDesc == (id)[NSNull null]) ? nil : _defaultAppDesc;
}

- (NSArray*) additionalAppDescs //may return empty array (but never nil)
{
	if ( _additionalAppDescs == nil )
	{
		NSURL *itemURL = [[self itemDesc] URL];
		NSArray *appURLs = [[self class] applicationURLsForItemURL: itemURL];
		
		//fill an array of NTFileDesc objects for the array of URLs 
		_additionalAppDescs = [[NSMutableArray alloc] initWithCapacity: [appURLs count]];
		unsigned i = 0;
		for ( i = 0; i < [appURLs count]; i++ )
		{
			NSURL *appURL = [appURLs objectAtIndex: i];
			if ( [appURL isFileURL] )
			{
				NTFileDesc *appDesc = [NTFileDesc descNoResolve: [appURL path]];
				if ( [self checkAppDesc: appDesc checkDefaultApp: YES] )
					[_additionalAppDescs addObject: appDesc];
			}
		}
		
		[_additionalAppDescs sortOnAttribute: @selector(name) usingSelector: @selector(caseInsensitiveCompare:)];
	}
	
	return _additionalAppDescs;
}

- (NTFileDesc*) itemDesc
{
	return _itemDesc;
}

- (void) openItemWithAppDesc: (NTFileDesc*) appDesc
{
	[[self class] openItemDesc: [self itemDesc] withAppDesc: appDesc];
}

+ (void) openItemDesc: (NTFileDesc*) itemDesc withAppDesc: (NTFileDesc*) appDesc
{
	[[NSWorkspace sharedWorkspace] openFile: [itemDesc path] withApplication: [appDesc path]];
}

@end

@implementation AppsForItem(Private)

- (BOOL) checkAppDesc: (NTFileDesc*) appDesc checkDefaultApp: (BOOL) checkDefApp
{
	if ( appDesc == nil )
		return NO;
	
	NTFileDesc *itemDesc = [self itemDesc];
	
	if ( checkDefApp && [appDesc isEqualToDesc: [self defaultAppDesc]] )
		return NO;
	
	BOOL isDIX = [[appDesc name] isEqualToString: @"Disk Inventory X.app"];
	BOOL isFinder = [[appDesc name] isEqualToString: @"Finder.app"];
	
	//filter out the Finder (for simple folders, the Finder is returned by "LSGetApplicationForItem" and "LSCopyApplicationURLsForURL")
	//it would be better to identify the Finder by it's bundle identifier, but then we would have to load it's bundle (?)
	return !isDIX
			&& ( [itemDesc isFile]
				 || [itemDesc isPackage] 
				 || !isFinder );
}

// get a list of apps that can open a document
// NOTE: this searches network volumes!!
+ (NSArray*) applicationURLsForItemURL:(NSURL*)inItemURL;
{
    CFArrayRef outURLs;
    NSMutableArray* result=nil;
	
    outURLs = LSCopyApplicationURLsForURL( (CFURLRef) inItemURL, kLSRolesViewer | kLSRolesEditor );
    if (outURLs)
    {
        if ([(id)outURLs isKindOfClass:[NSArray class]])
        {
            result = [NSMutableArray arrayWithArray:(NSArray*)outURLs];
            
            // filter out .exe files
            int i, cnt = [result count];
            NSURL *url;
            
            for (i=(cnt-1);i>=0;i--)
            {
                url = [result objectAtIndex:i];
                
                if ([[[url path] pathExtension] isEqualToStringCaseInsensitive:@"exe"])
                    [result removeObjectAtIndex:i];
            }            
        }
        
        CFRelease(outURLs);
    }
	
    return result;
}

@end
