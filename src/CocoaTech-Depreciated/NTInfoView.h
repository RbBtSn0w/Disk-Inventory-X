//
//  NTInfoView.h
//  Path Finder
//
//  Created by Steve Gehrman on Sat Jul 12 2003.
//  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
//

#import "NTTitledInfoView.h"

@interface NTInfoView : NSView 
{
    NTTitledInfoView* _titledInfoView;
    NTFileDesc* _desc;
    BOOL _longFormat;
    
    NSString* _calculatedFolderSize, *_calculatedFolderNumItems;

//	Tjark Derlien Sep 2009: threaded folder size calculation removed as a folder's size
//	is calculated while traversing the file system and thus will be available when
//	the info pane is opened for a folder
//    NTThreadWorkerController *_calcSizeThread;
}

- (id)initWithFrame:(NSRect)frame longFormat:(BOOL)longFormat;
- (id)initWithFrame:(NSRect)frame;  // long format is NO by default

- (NTFileDesc*)desc;
- (void)setDesc:(NTFileDesc*)desc;

@end
