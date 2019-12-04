//
//  DrivesPanelController.m
//  Disk Inventory X
//
//  Created by Tjark Derlien on 15.11.04.
//  Copyright 2004 Tjark Derlien. All rights reserved.
//

#import "DrivesPanelController.h"
#import "FileSizeFormatter.h"
#import "VolumeNameTransformer.h"
#import "VolumeUsageTransformer.h"

//NTStringShare is a private class in the CocoaFoundation framework; but as it is not fully thread safe,
//we need to declare it here to be accessible (see [DrivesPanelController init])
@interface NTStringShare : NSObject
+ (NTStringShare*)sharedInstance;
@end

//============ interface DrivesPanelController(Private) ==========================================================

@interface DrivesPanelController(Private)

- (void) rebuildVolumesArrayUsingCocoaTech;
- (void) rebuildVolumesArrayUsingNSFileManager;
- (void) rebuildProgressIndicatorArray;
- (void) onVolumesChanged: (NSNotification*) notification;

@end


@implementation DrivesPanelController

+ (DrivesPanelController*) sharedController
{
	static DrivesPanelController *controller = nil;
	
	if ( controller == nil )
		controller = [[DrivesPanelController alloc] init];
	
	return controller;
}

- (id) init
{
	self = [super init];
	
	//[NTStringShare sharedInstance] is not thread safe. NTStringShare's init method may be called concurrently
	//which may lead to concurrent calls to NSBundle (which isn't thread safe).
	//In our case here NTVolumeThread and our main thread may call [NTStringShare sharedInstance] concurretly.
	//
	//NTVolumeThread's call stack to NSBundle (passing [NTStringShare sharedInstance]):
	//  4   com.apple.Foundation       	0x926e14f0 -[NSBundle localizedStringForKey:value:table:] + 82
	//	5   CocoaTechFoundation        	0x1b047aaf +[NTStringShare(StandardKindStrings) folderKindString] + 103
	//	6   CocoaTechFoundation        	0x1b0481d2 -[NTStringShare(Private) defaultKindStrings] + 119
	//	7   CocoaTechFoundation        	0x1b0476eb -[NTStringShare init] + 159
	//	8   CocoaTechFoundation        	0x1b0477b2 +[NTStringShare sharedInstance] + 76
	//	9   CocoaTechFoundation        	0x1b00c8ba -[NTFileDesc extension] + 164
	//	10  CocoaTechFoundation        	0x1b00dec1 -[NTFileDesc isPathFinderAlias] + 154
	//	11  CocoaTechFoundation        	0x1b00dd6d -[NTFileDesc isAlias] + 90
	//	12  CocoaTechFoundation        	0x1b0110ee -[NTFileDesc(Private) resolvedDesc:] + 181
	//	13  CocoaTechFoundation        	0x1b00b147 +[NTFileDesc descResolve:] + 108
	//	14  CocoaTechFoundation        	0x1b028301 +[NTVolumeMgr(Utils) userVolumeAtMountPoint:] + 81
	//	15  CocoaTechFoundation        	0x1b02815d +[NTVolumeMgr(Private) mountedVolumesUsingUnix:] + 609
	//	16  CocoaTechFoundation        	0x1b028538 -[NTVolumeThread doWorkerMethod:] + 49
	//
	//main thread's call stack to NSBundle (also passing [NTStringShare sharedInstance]):
	//	5   com.apple.Foundation       	0x928f1510 -[NSBundle localizedStringForKey:value:table:] + 68
	//	6   CocoaTechFoundation        	0x1b043f04 +[NTStringShare(StandardKindStrings) symbolicLinkKindString] + 84 (icplusplus.c:27)
	//	7   CocoaTechFoundation        	0x1b044578 -[NTStringShare(Private) defaultKindStrings] + 132 (icplusplus.c:27)
	//	8   CocoaTechFoundation        	0x1b043ae4 -[NTStringShare init] + 136 (icplusplus.c:27)
	//	9   CocoaTechFoundation        	0x1b043bb0 +[NTStringShare sharedInstance] + 68 (icplusplus.c:27)
	//	10  CocoaTechFoundation        	0x1b00c9a0 -[NTFileDesc extension] + 136 (icplusplus.c:27)
	//	11  CocoaTechFoundation        	0x1b00de58 -[NTFileDesc isPathFinderAlias] + 104 (icplusplus.c:27)
	//	12  CocoaTechFoundation        	0x1b00dd24 -[NTFileDesc isAlias] + 84 (icplusplus.c:27)
	//	13  CocoaTechFoundation        	0x1b0111f8 -[NTFileDesc(Private) resolvedDesc:] + 148 (icplusplus.c:27)
	//	14  CocoaTechFoundation        	0x1b00b2ac +[NTFileDesc descResolve:] + 92 (icplusplus.c:27)
	//	15  CocoaTechFoundation        	0x1b02659c +[NTVolumeMgr(Utils) userVolumeAtMountPoint:] + 76 (icplusplus.c:27)
	//	16  CocoaTechFoundation        	0x1b0263dc +[NTVolumeMgr(Private) mountedVolumesUsingUnix:] + 468 (icplusplus.c:27)
	//	17  com.derlien.DiskInventoryX 	0x000099c8 -[DrivesPanelController(Private) rebuildVolumesArray] + 56 (crt.c:300)
	//	18  com.derlien.DiskInventoryX 	0x00009618 -[DrivesPanelController init] + 292 (crt.c:300)
	//	19  com.derlien.DiskInventoryX 	0x000094dc +[DrivesPanelController sharedController] + 68 (crt.c:300)
	
	//to avoid concurrent calls to NTStringShare's init, we ensure that the singleton is created and initialized prior
	//spawning NTVolumeThread (this will be done in [NTVolumeMgr sharedInstance])
	[NTStringShare sharedInstance];
	
	//register volume transformers needed in the volume tableview (before Nib is loaded!)
	[NSValueTransformer setValueTransformer:[VolumeNameTransformer transformer] forName: @"volumeNameTransformer"];
	[NSValueTransformer setValueTransformer:[VolumeUsageTransformer transformer] forName: @"volumeUsageTransformer"];

    // we no longer use CocoaTech's volume manager; we use NSWorkspace and NSFileManager instead
    /*
	[[NSNotificationCenter defaultCenter] addObserver: self
											 selector: @selector(onVolumesChanged:)
												 name: kNTVolumeMgrVolumeListHasChangedNotification
											   object: [NTMountedVolumeMgr sharedInstance]];
    */
    NSNotificationCenter *wsNotiCenter = [[NSWorkspace sharedWorkspace] notificationCenter];
    [wsNotiCenter addObserver: self
                     selector: @selector(onVolumesChanged:)
                         name: NSWorkspaceDidMountNotification
                       object: nil];
    
    [wsNotiCenter addObserver: self
                     selector: @selector(onVolumesChanged:)
                         name: NSWorkspaceDidUnmountNotification
                       object: nil];
    
    [wsNotiCenter addObserver: self
                     selector: @selector(onVolumesChanged:)
                         name: NSWorkspaceDidRenameVolumeNotification
                       object: nil];

	
	[self rebuildVolumesArrayUsingNSFileManager];
	
	//load Nib with volume panel
    if ( ![NSBundle loadNibNamed: @"VolumesPanel" owner: self] )
	{
		[self release];
		self = nil;
	}
	else
	{
		//open volume on double clicked (can't be configured in IB?)
		[_volumesTableView setDoubleAction: @selector(openVolume:)];
		
		//set FileSizeFormatter for the columns displaying sizes (capacity, free)
		FileSizeFormatter *sizeFormatter = [[[FileSizeFormatter alloc] init] autorelease];
		[[[_volumesTableView tableColumnWithIdentifier: @"totalSize"] dataCell] setFormatter: sizeFormatter];
		[[[_volumesTableView tableColumnWithIdentifier: @"freeBytes"] dataCell] setFormatter: sizeFormatter];
	}
	
	[_volumesPanel makeFirstResponder: _volumesTableView];
	
	return self;
}

- (void) dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver: self];

    [_volumes release];
	[_progressIndicators release];
	
    [super dealloc];
}

- (NSArray*) volumes
{
	return _volumes;
}

- (IBAction)openVolume:(id)sender
{
	NSIndexSet *selectedIndexes = [_volumesTableView selectedRowIndexes];
	NSUInteger index = [selectedIndexes firstIndex];
	
	//open volume in each of the selected rows
    while (index != NSNotFound)
    {
		NTVolume *volume = [[_volumes objectAtIndex: index] objectForKey: @"volume"];
		NSString *path = [[volume mountPoint] path];
		NSAssert1( path != nil, @"no path for volume with ref num %hi", [volume volumeRefNum] );
		
		//defer it till the next loop cycle (otherwise the "Open Volume" button stays in "pressed" mode during the loading)
		[[NSRunLoop currentRunLoop] performSelector: @selector(openDocumentWithContentsOfFile:)
											 target: [NSDocumentController sharedDocumentController]
										   argument: path
											  order: 1
											  modes: [NSArray arrayWithObject: NSDefaultRunLoopMode]];

        index = [selectedIndexes indexGreaterThanIndex: index];
    }	
}

- (BOOL) panelIsVisible
{
	return [[self panel] isVisible];
}

- (void) showPanel
{
	[[self panel] orderFront: nil];
}

- (NSWindow*) panel
{
	return _volumesPanel;
}


@end

//============ implementation DrivesPanelController(Private) ==========================================================

@implementation DrivesPanelController(Private)

//fill array "_volumes" with mounted volumes and their images
- (void) rebuildVolumesArrayUsingCocoaTech
{
    NSArray *vols = nil;//[[NTMountedVolumeMgr sharedInstance] mountedVolumes];
	
	[self willChangeValueForKey: @"volumes"];

	NS_DURING
		[_volumes release];
		_volumes = [[NSMutableArray alloc] initWithCapacity: [vols count]];
		
		NTVolume *volume = nil;
		NSEnumerator *volEnum = [vols objectEnumerator];
		while ( ( volume = [volEnum nextObject] ) != nil )
		{
			//filter out the virtual "Network" volume
			if ( ![[volume fileSystemName] isEqualToString: @"Network"] )
			{
				//put NTVolume object for key "volume" in the entry dictionary
				NSMutableDictionary *entry = [NSMutableDictionary dictionaryWithObject: volume forKey: @"volume"];
				
				//put volume icon for key "image" in the entry dictionary
				NSImage *volImage = [[volume mountPoint] iconImage: 32];
                
                NSAssert( volImage != nil, @"volImage != nil");
				
				[entry setObject: ( volImage == nil ? (id)[NSNull null] : volImage )
						  forKey: @"image"];
				
				[_volumes addObject: entry];
			}
		}
	NS_HANDLER
	NS_ENDHANDLER
	
	[self rebuildProgressIndicatorArray];
	
	[self didChangeValueForKey: @"volumes"];
}

//fill array "_volumes" with mounted volumes and their images
- (void) rebuildVolumesArrayUsingNSFileManager
{
    NSArray<NSURL *> *vols = [[NSFileManager defaultManager] mountedVolumeURLsIncludingResourceValuesForKeys: [NSArray array]
                                                                                                     options: NSVolumeEnumerationSkipHiddenVolumes];
    
    [self willChangeValueForKey: @"volumes"];
    
    NS_DURING
    [_volumes release];
    _volumes = [[NSMutableArray alloc] initWithCapacity: [vols count]];
    
    for ( NSURL *volumeURL in vols )
    {
        NSString *volumePath = [NSString stringWithUTF8String:[volumeURL fileSystemRepresentation]];
        NTFileDesc *volumeDesc = [NTFileDesc descNoResolve:volumePath];
        
        //put NTVolume object for key "volume" in the entry dictionary
        NTVolume *volume = [volumeDesc volume];
        NSMutableDictionary *entry = [NSMutableDictionary dictionaryWithObject: volume forKey: @"volume"];
        
        //put volume icon for key "image" in the entry dictionary
        NSImage *volImage = [[volume mountPoint] iconImage: 32];
        
        [entry setObject: ( volImage == nil ? (id)[NSNull null] : volImage )
                  forKey: @"image"];
        
        [_volumes addObject: entry];
    }
    NS_HANDLER
    NS_ENDHANDLER
    
    [self rebuildProgressIndicatorArray];
    
    [self didChangeValueForKey: @"volumes"];
}

//keeps array of progress indicators (for graphical usage display) in sync with volumes array
- (void) rebuildProgressIndicatorArray
{
	if ( _progressIndicators == nil )
		_progressIndicators = [[NSMutableArray alloc] initWithCapacity: [_volumes count]];
	
	unsigned i;
	for ( i = 0; i < [_volumes count]; i++ )
	{
		NSProgressIndicator *progrInd = nil;
		if ( i >= [_progressIndicators count] )
		{
			progrInd = [[[NSProgressIndicator alloc] init] autorelease];
			[progrInd setStyle: NSProgressIndicatorBarStyle];
			[progrInd setIndeterminate: NO];
			
			[_progressIndicators addObject: progrInd];
		}
		else
			//reuse existing progress indicator
			progrInd = [_progressIndicators objectAtIndex: i];
		
		NTVolume *vol = [[_volumes objectAtIndex: i] objectForKey : @"volume"];
		
		[progrInd setMinValue: 0];
		[progrInd setMaxValue: [vol totalBytes]];
		[progrInd setDoubleValue: ([vol totalBytes] - [vol freeBytes])];
	}
	
	while ( [_progressIndicators count] > [_volumes count] )
	{
		[[_progressIndicators lastObject] removeFromSuperviewWithoutNeedingDisplay];
		[_progressIndicators removeLastObject];
	}
}

#pragma mark --------NTVolumeMgr notifications-----------------

- (void) onVolumesChanged: (NSNotification*) notification
{
    // we no longer use CocoaTech's volume manager; we use NSWorkspace and NSFileManager instead
    //[self rebuildVolumesArrayUsingCocoaTech];
    [self rebuildVolumesArrayUsingNSFileManager];
}

#pragma mark --------NSTableView notifications-----------------

- (void) tableViewSelectionDidChange: (NSNotification*) notification
{
}

#pragma mark --------NSTableView delegates-----------------

- (void) tableView:(NSTableView *) tableView willDisplayCell:(id) cell forTableColumn:(NSTableColumn *) tableColumn row:(int) row
{
	if ( [[tableColumn identifier] isEqualToString: @"usagePercent"] )
	{
		NSProgressIndicator *progrInd = [_progressIndicators objectAtIndex: row];
		
		//add progress indicator as subview of table view
		if ( [progrInd superview] != tableView )
			[tableView addSubview: progrInd];
		
		NSInteger colIndex = [tableView columnWithIdentifier: [tableColumn identifier]];
		NSRect cellRect = [tableView frameOfCellAtColumn: colIndex row: row];
		
		const float progrIndThickness = NSProgressIndicatorPreferredLargeThickness; 
		const float extraSpace = 16; //space before and after progress indicator (relative to left and right side of cell)
		
		//center it vertically in cell
		NSAssert( NSHeight(cellRect) > progrIndThickness, @"rows need to be higher than progress indicator thickness" );
		cellRect.origin.y += (NSHeight(cellRect) - progrIndThickness) / 2;
		cellRect.size.height = progrIndThickness;

		//add space before and after
		cellRect.origin.x += extraSpace;
		cellRect.size.width -= 2*extraSpace;
		
		[progrInd setFrame: cellRect];
		[progrInd stopAnimation: nil];
	}
}



@end
