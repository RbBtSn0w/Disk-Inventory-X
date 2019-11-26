//
//  FileKindsPopupController.h
//  Disk Inventory X
//
//	This class implements the controller for the popup button which let the user
//	choose between the file kinds (positioned above the TableView listing all files of the
//	selected kind).
//
//  Created by Tjark Derlien on 31.03.05.
//  Copyright 2005 Tjark Derlien. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GenericArrayController.h"
#import "FileSystemDoc.h"

//the first entry in the kinds popup button is a faked FileKindStatistic object
//(it represents the "all kinds" entry)
@interface FileKindStatistic(AllKinds)
- (BOOL) isAllFileKindsItem;
@end
@interface NSDictionary(AllKinds)
- (BOOL) isAllFileKindsItem;
@end

@interface FileKindsPopupController : GenericArrayController {
	IBOutlet NSPopUpButton *_kindsPopUpButton;
	IBOutlet id _windowController;
}

- (FileSystemDoc*) document;

@end
