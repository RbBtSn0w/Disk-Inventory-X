//
//  NSRunningApplication-NTExtensions.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 9/14/09.
//  Copyright 2009 Cocoatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

// this is added to keep the griddataset happy, it's not functional
@interface NSRunningApplication (NTExtensionsNSCoding) <NSCoding>
@end

@interface NSRunningApplication (NTExtensions)
+ (NSRunningApplication*)activeApplication;
- (BOOL)isRegular;
- (BOOL)isBackgroundOnly;
- (BOOL)isBackgroundOnlyWithUI;

// recreated everytime, not cached since we are a category
- (NTFileDesc*)desc;

- (BOOL)activateAllWindows:(BOOL)allWindows unminimize:(BOOL)unminimize;
@end
