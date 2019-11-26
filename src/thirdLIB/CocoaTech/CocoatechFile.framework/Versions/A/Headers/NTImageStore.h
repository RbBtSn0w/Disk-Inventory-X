//
//  NTImageStore.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 9/6/09.
//  Copyright 2009 Cocoatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#define NTMS ((NTImageStore*)[NTImageStore sharedInstance])

@interface NTImageStore : NTSingletonObject
{
	NSBundle* coreTypesBundle;
	NSMutableDictionary* images;
	
	NSImage* countBadgeImage;
	NSImage* countBadgeImage3;
	NSImage* countBadgeImage4;
	NSImage* countBadgeImage5;
}

- (NSImage *)imageWithName:(NSString*)name; // images in CoreTypes.bundle.  for example: ToolbarPicturesFolderIcon
- (NSImage*)imageForSystemType:(OSType)type size:(NSUInteger)size;

- (NSImage *)aliasBadge;
- (NSImage *)lockBadge;
- (NSImage *)makeFolderBadge;
- (NSImage *)appleScriptBadge;

- (NSImage *)computerIcon;
- (NSImage *)documentIcon;
- (NSImage *)textDocumentIcon;
- (NSImage *)clippingsDocumentIcon;
- (NSImage *)folderIcon;

- (NSImage *)trashIcon;
- (NSImage *)trashFullIcon;
- (NSImage *)ejectIcon;
- (NSImage *)backwardsIcon;
- (NSImage *)forwardsIcon;
- (NSImage *)connectToIcon;
- (NSImage *)iDiskIcon;
- (NSImage *)iDiskPublicIcon;
- (NSImage *)hardDiskIcon;
- (NSImage *)previewIcon;
- (NSImage *)iTunesIcon;
- (NSImage *)colorPanelIcon;

- (NSImage *)networkIcon;
- (NSImage *)fileServerIcon;
- (NSImage *)macFileServerIcon;
- (NSImage *)genericPCServerIcon;
- (NSImage *)CDROMIcon;
- (NSImage *)multipleFilesIcon;
- (NSImage *)smallMultipleFilesIcon;
- (NSImage *)spotlightIcon;

- (NSImage *)homeIcon;
- (NSImage *)favoritesIcon;
- (NSImage *)deleteIcon;
- (NSImage *)finderIcon;
- (NSImage *)desktopIcon;
- (NSImage *)windowIcon;
- (NSImage *)publicIcon;
- (NSImage *)picturesIcon;
- (NSImage *)makeFolderIcon;
- (NSImage *)makeFileIcon;
- (NSImage *)musicIcon;
- (NSImage *)moviesIcon;
- (NSImage *)infoIcon;
- (NSImage *)findIcon;
- (NSImage *)documentsIcon;
- (NSImage *)applicationsIcon;
- (NSImage *)noWriteIcon;
- (NSImage *)writeIcon;
- (NSImage *)drawerIcon;
- (NSImage *)burnIcon;
- (NSImage *)eraseIcon;
- (NSImage *)recentItemsIcon;
- (NSImage *)libraryIcon;
- (NSImage *)sitesIcon;
- (NSImage *)downloadsIcon;
- (NSImage *)utilitiesIcon;
- (NSImage *)stopIcon;
- (NSImage *)zoomOutIcon;
- (NSImage *)zoomInIcon;
- (NSImage *)zoomToActualSizeIcon;
- (NSImage *)nextPageIcon;
- (NSImage *)previousPageIcon;
- (NSImage *)preferencesIcon;
- (NSImage *)applicationIcon;

- (NSImage *)screenSharingIcon;
- (NSImage *)screenSharingNetworkIcon;

- (NSImage *)rotateLeftIcon;
- (NSImage *)rotateRightIcon;

- (NSImage*)miniFolder; // 12x12 generic folder icon (used for brower or tableview)
- (NSImage*)miniFile;  // 12x12 generic file icon
- (NSImage*)miniApplication;  // 12x12 generic file icon

// standard images
- (NSImage*)quickLookImage;
- (NSImage*)slideshowImage;
- (NSImage*)coverflowImage;
- (NSImage*)reloadImage;
- (NSImage*)countBadgeImage:(int)numDigits;

- (NSImage*)openFolderImage;
- (NSImage*)unknownFSObjectImage;
@end




