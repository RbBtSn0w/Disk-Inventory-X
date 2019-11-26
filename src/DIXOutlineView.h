//
//  DIXOutlineView.h
//  Disk Inventory X
//
// DIXOutlineView derives from NSOutlineView and add some commonly used functionality
// (e.g. context menu support, drag&drop support)
//
//  Created by Tjark Derlien on 29.03.05.
//  Copyright 2005 Tjark Derlien. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface DIXOutlineView: NSOutlineView

- (id) selectedItem;

@end

@interface NSObject(DIXOutlineViewDelegate)
- (NSMenu*) outlineView: (NSOutlineView *) outlineView menuForTableColumn: (NSTableColumn*) column item: (id) item;
	//delegate will be asked what menu to show (if not implemented by delegate [self menu] is used)

//- (NSDragOperation) draggingSourceOperationMaskForLocal:(BOOL)isLocal;
	//ask the delegate which drag operations are supported (if TableView is the dragging source);
	//as this selector is already part of NSDraggingSource category, we don't need to re-declare it here
@end

