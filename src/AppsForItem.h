//
//  AppsForItem.h
//  Disk Inventory X new
//
//  Created by Tjark Derlien on 20.01.06.
//  Copyright 2006 Tjark Derlien. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface AppsForItem : NSObject {
	NTFileDesc *_defaultAppDesc;
	NSMutableArray *_additionalAppDescs;
	NTFileDesc *_itemDesc; //file/folder for which to search for applications
}

+ (id) appsForItemDesc: (NTFileDesc*) item;
- (id) initWithItemDesc: (NTFileDesc*) item;

- (NTFileDesc*) defaultAppDesc; //may return nil
- (NSArray*) additionalAppDescs; //may return empty array (but never nil)

- (NTFileDesc*) itemDesc;

- (void) openItemWithAppDesc: (NTFileDesc*) appDesc;
+ (void) openItemDesc: (NTFileDesc*) item withAppDesc: (NTFileDesc*) appDesc;

@end
