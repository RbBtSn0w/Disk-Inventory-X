//
//  NTFileSystemEventMessage.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 4/27/10.
//  Copyright 2010 Cocoatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NTFileSystemEventMessage : NSObject {
	NSString* path;	
	BOOL rescanSubdirectories;	
	NSString* relativePath_storage;
	NSString* mountPoint_storage;
}

@property (readonly, nonatomic, retain) NSString* path;
@property (readonly, nonatomic, assign) BOOL rescanSubdirectories;

+ (NTFileSystemEventMessage*)message:(NSString*)thePath rescanSubdirectories:(BOOL)theRescanSubdirectories;
- (void)updateMessage:(BOOL)theRescanSubdirectories;

- (NSString*)relativePath;
- (NSString*)mountPoint;
@end
