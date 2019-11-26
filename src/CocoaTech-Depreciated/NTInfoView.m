//
//  NTInfoView.m
//  Path Finder
//
//  Created by Steve Gehrman on Sat Jul 12 2003.
//  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
//

#import "NTInfoView.h"
#import "NTTitledInfoPair.h"
#import <CocoaTechStrings/NTLocalizedString.h>

#pragma warning "ID3 support removed"
//#import "NTID3Helper.h"

@interface NTInfoView (Private)
- (void)createInfoView;
- (void)updateInfoView;
- (NSArray*)infoPairs;
- (NSArray*)longInfoPairs;
- (void)resetForNewItem;
- (NSArray*)sizePairs:(BOOL)calcFolderSizeImmediately;
- (void)setFolderSizeInfo:(NSNumber*)size totalValence:(NSNumber*)totalValence;
//- (void)startCalcSizeThread;
@end

@implementation NTInfoView

- (id)initWithFrame:(NSRect)frame longFormat:(BOOL)longFormat;
{
    self = [super initWithFrame:frame];
    
    _longFormat = longFormat;
    
    [self setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];

    [self createInfoView];
    
    /*
	 _calcSizeThread = [[NTThreadWorkerController alloc] init];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(sizeCalcNotification:)
                                                 name:[_calcSizeThread notificationName]
                                               object:nil];
    */
    return self;
}

- (id)initWithFrame:(NSRect)frame;
{
    self = [self initWithFrame:frame longFormat:NO];
    
    return self;
}

- (void)dealloc;
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];

    [_desc release];
    [_titledInfoView release];
    //[_calcSizeThread release];
    [_calculatedFolderSize release];
    [_calculatedFolderNumItems release];
    
    [super dealloc];
}

- (NTFileDesc*)desc;
{
    return _desc;
}

- (void)setDesc:(NTFileDesc*)desc;
{    
    [self resetForNewItem];

    _desc = [desc retain];

    [self updateInfoView];
}

@end

// ===============================================================================

@implementation NTInfoView (Private)

- (void)resetForNewItem;
{
    //[_calcSizeThread halt];
    
    [_desc autorelease];
    _desc = nil;
    
    [_calculatedFolderSize release];
    _calculatedFolderSize = nil;
    
    [_calculatedFolderNumItems release];
    _calculatedFolderNumItems = nil;
}

- (void)createInfoView;
{
    NSRect contentRect;
    NSScrollView* scrollView;
    
    scrollView = [[[NSScrollView alloc] initWithFrame:[self bounds]] autorelease];
    
    [scrollView setAutohidesScrollers:YES];
    [scrollView setHasHorizontalScroller:NO];
    [scrollView setHasVerticalScroller:YES];
    [scrollView setAutoresizesSubviews:YES];
    [scrollView setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
    [scrollView setBorderType:NSNoBorder];
    [scrollView setScrollsDynamically:YES];
    [scrollView setDrawsBackground:YES];
    [[scrollView contentView] setCopiesOnScroll:YES];
    
    // set small scrollbars
    if ([scrollView verticalScroller])
        [[scrollView verticalScroller] setControlSize:NSSmallControlSize];
    if ([scrollView horizontalScroller])
        [[scrollView horizontalScroller] setControlSize:NSSmallControlSize];
    
    contentRect = [scrollView bounds];
    contentRect.size = [scrollView contentSize];
    
    _titledInfoView = [[NTTitledInfoView alloc] initWithFrame:contentRect];
    
    // longFormat is used in the GetInfo window, keep the extra space in that case
    if (!_longFormat)
        [_titledInfoView setHorizontalOffset:0];  // don't waste any horizontal space
    
    // add the document view to the scroller
    [scrollView setDocumentView:_titledInfoView];
    
    [self addSubview:scrollView];
}

- (void)updateInfoView;
{
    NSArray* array;
    
    if (_longFormat)
        array = [self longInfoPairs];
    else
        array = [self infoPairs];
    
    [_titledInfoView setWithArray:array];
}

- (NSArray*)infoPairs;
{
    NSMutableArray* infoPairs = [NSMutableArray arrayWithCapacity:15];
    
    if (_desc && [_desc isValid])
    {
        NSString* version;
        NTFileTypeIdentifier* typeID = [_desc typeIdentifier];
        NTFileDesc* descPref = [_desc descResolveIfAlias];
        
        int valence = -1;        
        if ([_desc isDirectory] && ![_desc isPackage])
            valence = [_desc valence];        
        
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Name:" table:@"preview"] info:[_desc displayName]]];
        
        if (valence > 0)
            [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Kind:" table:@"preview"] info:[NSString stringWithFormat:@"%@ (%d)", [_desc kindString], valence]]];
        else
            [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Kind:" table:@"preview"] info:[_desc kindString]]];
        
        if ([_desc isNetwork])
            [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"URL:"] info:[[[_desc volume] volumeURL] absoluteString]]];
#pragma warning "support webloc files removed"
/*
        else
        {
            NSURL* url = [NTWeblocFile urlFromWeblocFile:_desc];
            if (url)
                [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"URL:"] info:[url absoluteString]]];
        }
 */
        [infoPairs addObjectsFromArray:[self sizePairs:NO]];
        
        // old version using CocoaTech's NTDateFormatter
        /*
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Modified:" table:@"preview"] info:[[_desc modificationDate] dateString:kMediumDate relative:YES]]];
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Created:" table:@"preview"] info:[[_desc creationDate] dateString:kMediumDate relative:YES]]];
        */
        // now using NSDateFormatter (NTDateFormatter does not work on newer OS versions)
        {
            NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init] autorelease];
            [dateFormatter setDateStyle:NSDateFormatterMediumStyle];
            [dateFormatter setTimeStyle:NSDateFormatterMediumStyle];
            [dateFormatter setLocale:[NSLocale currentLocale]];
            
            [infoPairs addObject:[NTTitledInfoPair infoPair: [NTLocalizedString localize:@"Modified:" table:@"preview"]
                                                       info: [dateFormatter stringFromDate:[_desc modificationDate]]]];
            [infoPairs addObject:[NTTitledInfoPair infoPair: [NTLocalizedString localize:@"Created:" table:@"preview"]
                                                       info: [dateFormatter stringFromDate:[_desc creationDate]]]];
        }
        
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Owner:" table:@"preview"] info:[_desc ownerName]]];
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Group:" table:@"preview"] info:[_desc groupName]]];
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Permission:" table:@"preview"] info:[_desc permissionString]]];
        
        if ([_desc type])
            [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Type:" table:@"preview"] info:NSFileTypeForHFSTypeCode([_desc type])]];
        if ([_desc creator])
            [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Creator:" table:@"preview"] info:NSFileTypeForHFSTypeCode([_desc creator])]];
        
        version = [_desc infoString];
        if (!version || ![version length])
            version = [_desc versionString];
        if (version && [version length])
            [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Version:" table:@"preview"] info:version]];
        
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Path:" table:@"preview"] info:[_desc path]]];
        
        // if alias or symbolic link - resolved:
        if ([_desc isAlias])
        {
            NTFileDesc* resolved = [_desc descResolveIfAlias];
            
            if (resolved)
                [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Resolved:" table:@"preview"] info:[resolved path]]];
        }
        
        // make sure the item is resolved (match the pref)
        if ([descPref application] != nil)
        {  
            NTFileDesc* appDesc = [descPref application];
            
            if ([appDesc isValid])
                [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Application:" table:@"preview"] info:[appDesc displayName]]];
        }

#pragma warning "ID3 support disabled"
/*
        if ([typeID isMP3])
        {
            NTID3Helper* helper = [NTID3Helper helperWithPath:[_desc path]];
            [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"MP3:" table:@"preview"] info:[helper infoString]]];
        }
*/
		NTVolume *volume = [_desc volume];
        
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Format:" table:@"preview"] info:[volume fileSystemName]]];
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Mount Point:" table:@"preview"] info:[[volume mountPoint] path]]];
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Device:" table:@"preview"] info:[volume mountDevice]]];
    }
    
    return infoPairs;
}

//	Tjark Derlien Sep 2009: threaded folder size calculation removed as a folder's size
//	is calculated while traversing the file system and thus will be available when
//	the info pane is opened for a folder
/*
- (void)startCalcSizeThread;
{
    // this cancels any thread already in progress
    [_calcSizeThread runThread:[SizeCalculatorThread class] param:[SizeCalculatorParam paramWithTokens:[NSArray arrayWithObject:[CalcSizeToken calcSizeForDesc:_desc withItemIdentifier:nil]]]];
}

- (void)calcFolderSizeButton:(id)sender;
{
    [self startCalcSizeThread];
    
    [self updateInfoView];
}

- (void)sizeCalcNotification:(NSNotification*)notification;
{
    NSDictionary *userInfo = [notification userInfo];
    SizeCalculatorParam* param = (SizeCalculatorParam*) [userInfo objectForKey:@"data"];
    
    if (param)
    {
        NSArray* sizes = [param resultsArray];
        
        if ([sizes count] > 0)
        {
            CalcSizeResult* result = [sizes objectAtIndex:0];
            
            NSNumber* size = [result size];
            NSNumber* totalValence = nil;
                        
            // this is false for volumes
            if ([result isNumItemsValid])
                totalValence = [result numItems];
                
            [self setFolderSizeInfo:size totalValence:totalValence];
            [self updateInfoView];

            // record the size in our desc
            [_desc setFolderSize:[size unsignedLongLongValue]];
            
            if (totalValence)
                [_desc setTotalValence:[totalValence unsignedLongLongValue]];
        }
    }
}
 */

- (NSArray*)longInfoPairs;
{
    NSMutableArray* infoPairs = [NSMutableArray arrayWithCapacity:15];
    
    if (_desc && [_desc isValid])
    {
        NTFileTypeIdentifier* typeID = [_desc typeIdentifier];
        NTFileDesc* descPref = [_desc descResolveIfAlias];
        
        int valence = -1;        
        if ([_desc isDirectory] && ![_desc isPackage] )
            valence = [_desc valence];
        
        if (valence > 0)
            [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Kind:" table:@"preview"] info:[NSString stringWithFormat:@"%@ (%d)", [_desc kindString], valence]]];
        else
            [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Kind:" table:@"preview"] info:[_desc kindString]]];

        if ([_desc isNetwork])
            [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"URL:"] info:[[[_desc volume] volumeURL] absoluteString]]];
#pragma warning "support webloc files removed"
        /*
       else
        {
            NSURL* url = [NTWeblocFile urlFromWeblocFile:_desc];
            if (url)
                [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"URL:"] info:[url absoluteString]]];
        }
*/
        
        [infoPairs addObjectsFromArray:[self sizePairs:YES]];
        
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Modified:" table:@"preview"] info:[[_desc modificationDate] dateString:kLongDate relative:NO]]];
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Created:" table:@"preview"] info:[[_desc creationDate] dateString:kLongDate relative:NO]]];
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Path:" table:@"preview"] info:[_desc path]]];
        
        // if alias or symbolic link - resolved:
        if ([_desc isAlias])
        {
            NTFileDesc* resolved = [_desc descResolveIfAlias];
            
            if (resolved)
                [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Resolved:" table:@"preview"] info:[resolved path]]];
        }
        
        // version
        {
            NSString* version = [_desc infoString];
            
            if (!version || ![version length])
                version = [_desc versionString];
            
            if (version && [version length])
                [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Version:" table:@"preview"] info:version]];
        }
        
        // make sure the item is resolved (match the pref)
        if ([descPref application] != nil)
        {  
            NTFileDesc* appDesc = [descPref application];
            
            if ([appDesc isValid])
                [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Application:" table:@"preview"] info:[appDesc displayName]]];
        }
		
#pragma warning "ID3 support removed"
        // mp3
       /*
       if ([typeID isMP3])
        {
            NTID3Helper* helper = [NTID3Helper helperWithPath:[_desc path]];
            [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"MP3:" table:@"preview"] info:[helper infoString]]];
        }
        */
		NTVolume *volume = [_desc volume];
         
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Volume:" table:@"preview"] info:[[volume mountPoint] displayName]]];
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Capacity:" table:@"preview"] info:[[NTSizeFormatter sharedInstance] fileSize:[volume totalBytes]]]];
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Free:" table:@"preview"] info:[[NTSizeFormatter sharedInstance] fileSize:[volume freeBytes]]]];
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Format:" table:@"preview"] info:[volume fileSystemName]]];
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Mount Point:" table:@"preview"] info:[[volume mountPoint] path]]];
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Device:" table:@"preview"] info:[volume mountDevice]]];
    }
    
    return infoPairs;
}

- (NSArray*)sizePairs:(BOOL)calcFolderSizeImmediately;
{
    NSMutableArray* infoPairs = [NSMutableArray arrayWithCapacity:2];

    if ([_desc isFile])
    {
        UInt64 dataSize = 0, rsrcSize = 0;
        NSMutableString* sizeResult;
        NSNumberFormatter* numFormatter = [[[NSNumberFormatter alloc] init] autorelease];
        
        [numFormatter setFormat:@"#,##0"];
        
        dataSize = [_desc dataForkSize];
        rsrcSize = [_desc rsrcForkSize];
        
        sizeResult = [NSMutableString stringWithString:[[NTSizeFormatter sharedInstance] fileSize:[_desc size]]];;
        
        if (dataSize)
        {
            [sizeResult appendString:@"\n"];
            [sizeResult appendString:[NTLocalizedString localize:@"data:" table:@"preview"]];
            [sizeResult appendString:[numFormatter stringForObjectValue:[NSNumber numberWithUnsignedLongLong:dataSize]]];
            [sizeResult appendString:[NTLocalizedString localize:@" bytes" table:@"preview"]];
        }
        
        if (rsrcSize)
        {
            [sizeResult appendString:@"\n"];
            [sizeResult appendString:[NTLocalizedString localize:@"rsrc:" table:@"preview"]];
            [sizeResult appendString:[numFormatter stringForObjectValue:[NSNumber numberWithUnsignedLongLong:rsrcSize]]];
            [sizeResult appendString:[NTLocalizedString localize:@" bytes" table:@"preview"]];
        }
        
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Size:" table:@"preview"] info:sizeResult]];
    }
    else if ([_desc isVolume])
    {
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Capacity:" table:@"preview"] info:[[NTSizeFormatter sharedInstance] fileSize:[NTFileDesc volumeTotalBytes:_desc]]]];
        [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Free:" table:@"preview"] info:[[NTSizeFormatter sharedInstance] fileSize:[NTFileDesc volumeFreeBytes:_desc]]]];
    }
    else // is folder
    {
		[self setFolderSizeInfo: [NSNumber numberWithUnsignedLongLong:[_desc size]]
				   totalValence: [NSNumber numberWithUnsignedLongLong:[_desc valence]]];

		/*       
		 //	Tjark Derlien Sep 2009: threaded folder size calculation removed as a folder's size
		 //	is calculated while traversing the file system and thus will be available when
		 //	the info pane is opened for a folder
		 
        // check if folder size is already calced		
        if (!_calculatedFolderSize)
        {
            if ([_desc folderSizeIsCalculated])
            {
                NSNumber* totalValence = nil;
                if ([_desc folderTotalValenceIsCalculated])
                    totalValence = [NSNumber numberWithUnsignedLongLong:[_desc totalValence]];
                
                [self setFolderSizeInfo:[NSNumber numberWithUnsignedLongLong:[_desc size]] totalValence:totalValence];
            }
        }
		
        if (_calculatedFolderSize)
        {
            [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Size:" table:@"preview"] info:_calculatedFolderSize]];
            
            // volumes return 0 items, so we keep it nil
            if (_calculatedFolderNumItems != nil)
                [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Contents:" table:@"preview"] info:_calculatedFolderNumItems]];
        }
        else
        {        
            if (calcFolderSizeImmediately && [_calcSizeThread idle])
                [self startCalcSizeThread];
            
            // if thread is idle, put up a "Calculate" button
            if ([_calcSizeThread idle])
                [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Size:" table:@"preview"] info:[NTLocalizedString localize:@"Calculate" table:@"preview"] action:@selector(calcFolderSizeButton:) target:self]];
            else
            {
                [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Size:" table:@"preview"] info:[NTLocalizedString localize:@"Calculating..." table:@"preview"]]];
                [infoPairs addObject:[NTTitledInfoPair infoPair:[NTLocalizedString localize:@"Contents:" table:@"preview"] info:[NTLocalizedString localize:@"Calculating..." table:@"preview"]]];
            }
        }  
  */
    }
    
    return infoPairs;
}

- (void)setFolderSizeInfo:(NSNumber*)size totalValence:(NSNumber*)totalValence;
{
    _calculatedFolderSize = [[[NTSizeFormatter sharedInstance] fileSize:[size unsignedLongLongValue]] retain];
    
    // this is nil for volumes
    if (totalValence)
    {
        NSNumberFormatter* formatter = [[[NSNumberFormatter alloc] init] autorelease];
        
        [formatter setPositiveFormat:@"#,###"];
        [formatter setAllowsFloats:NO];
        [formatter setAttributedStringForZero:[[[NSAttributedString alloc] initWithString:@"0"] autorelease]];
        
        _calculatedFolderNumItems = [[[formatter stringForObjectValue:totalValence] stringByAppendingString:[NTLocalizedString localize:@" items" table:@"preview"]] retain];
    }
}

@end
