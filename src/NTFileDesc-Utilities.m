//
//  NTFileDesc-Utilities.m
//  Disk Inventory X
//
//  Created by Tjark Derlien on 08.04.05.
//  Copyright 2005 Tjark Derlien. All rights reserved.
//

#import "NTFileDesc-Utilities.h"
#import "NTFileDesc-AccessExtensions.h"
#import <CocoaTechFile/NTFileDesc-Private.h>
#import <CocoaTechFile/NTFileDescData.h>
#import <CocoaTechFile/NTFileDescMemCache.h>

@implementation NTFileDesc(Utilities)

- (id) initWithName: (NSString*) name
			  fsRef: (FSRef*) fsRef
		catalogInfo: (FSCatalogInfo *)catalogInfo
  catalogInfoBitmap: (FSCatalogInfoBitmap) catalogBitmap
{
	NTFSRefObject *fsRefObject = [[NTFSRefObject alloc] initWithRef: fsRef
														catalogInfo: catalogInfo
															 bitmap: catalogBitmap
															   name: name];
	
	self = [self initWithFSRefObject: fsRefObject];
	[fsRefObject release];
	
	if ( ( catalogBitmap & (kFSCatInfoDataSizes | kFSCatInfoRsrcSizes) ) != 0
			&& ![self isDirectory] )
	{
		//although NTFSRefObject encapsulates the FSRef and CatalogInfo structures, it does
		//not handle size information; this is done by NSFileDescData
		//so we need to store the size infomation in _fileDesc's cache object
		NTFileDescData * dataCache = [self cache];
		
		[dataCache setFileSize:catalogInfo->dataPhysicalSize + catalogInfo->rsrcPhysicalSize];	
		[dataCache setPhysicalFileSize:catalogInfo->dataLogicalSize + catalogInfo->rsrcLogicalSize];
		
		// data fork
		[dataCache setDataForkSize:catalogInfo->dataPhysicalSize];
		[dataCache setDataForkPhysicalSize:catalogInfo->dataLogicalSize];
		
		// rsrc fork
		[dataCache setRsrcForkSize:catalogInfo->rsrcLogicalSize];
		[dataCache setRsrcForkPhysicalSize:catalogInfo->rsrcPhysicalSize];
	}
	
    return self;
}

- (NSString*) displayPath
{
	NSArray *fsRefPath = [self FSRefPath: YES /*includeSelf*/];
	NSString *displayPath = NSOpenStepRootDirectory();
	NSUInteger i = [fsRefPath count];
	while ( i-- )
	{
		NTFSRefObject *fsRef = [fsRefPath objectAtIndex: i];
		NTFileDesc *fileDesc = [[NTFileDesc alloc] initWithFSRefObject: fsRef];
		
		displayPath = [displayPath stringByAppendingPathComponent: [fileDesc displayName]];
		
		[fileDesc release];
	}
	
	return displayPath;
}

- (NSImage*) iconImageWithSize: (unsigned) size
{
	NTIcon *ntIcon = [self  icon];
	return [ntIcon imageForSize: size label: 0 select: NO];
}

- (NSArray*_Nullable) directoryContentsAutoreleased
{
	const FSCatalogInfoBitmap catalogInfoBitmapBulk =
												kDefaultCatalogInfoBitmap //define in CocoatechFile
												| kFSCatInfoNodeFlags
												| kFSCatInfoVolume
												| kFSCatInfoFinderInfo
												| kFSCatInfoDataSizes
												| kFSCatInfoRsrcSizes
												| kFSCatInfoPermissions
												| kFSCatInfoAttrMod
												| kFSCatInfoContentMod;
	
    NSMutableArray *result = nil;
	
	OSStatus outStatus;
	FSIterator iterator;
	
	outStatus = FSOpenIterator( [self FSRefPtr], kFSIterateFlat, &iterator );
	if (outStatus == noErr)
	{
		NTFileDescMem* cache = [[NTFileDescMemCache sharedInstance] checkout];
		
		FSRef *refArray = [cache refArray];
		FSCatalogInfo *catalogInfoArray = [cache catalogInfoArray];
		HFSUniStr255 *nameArray = [cache nameArray];
		
		do
		{
			ItemCount actualCount;
			
			outStatus = FSGetCatalogInfoBulk( iterator,
											 [cache capacity],
											 &actualCount,
											 NULL,
											 catalogInfoBitmapBulk,
											 catalogInfoArray,
											 refArray,
											 NULL,
											 nameArray);
			
			if (outStatus == noErr || outStatus == errFSNoMoreItems)
			{
				unsigned i;
				
				for( i = 0; i < actualCount; i++ )
				{
					NTFileDesc *fileDesc = [[NTFileDesc alloc] initWithName: [NSString fileNameWithHFSUniStr255:&nameArray[i]]
																	  fsRef: &refArray[i]
																catalogInfo: &catalogInfoArray[i]
														  catalogInfoBitmap: catalogInfoBitmapBulk];
											 
					if ( result == nil )
					{
                        result = [[NSMutableArray alloc] initWithCapacity: actualCount];
					}
					
					[result addObject:fileDesc];
					
					[fileDesc release];
				}
			}
		} while (outStatus == noErr);
		
		if (outStatus == errFSNoMoreItems)
			outStatus = noErr;
		
		FSCloseIterator(iterator);
		
		[[NTFileDescMemCache sharedInstance] checkin:cache];
	}
	
    if (result) {
        return [result autorelease];
    } else {
        return nil;
    }
}


@end
