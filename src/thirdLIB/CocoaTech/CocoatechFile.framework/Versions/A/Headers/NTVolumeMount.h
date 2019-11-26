//
//  NTVolumeMount.h
//  CocoatechFile
//
//  Created by Steve Gehrman on Tue Sep 03 2002.
//  Copyright (c) 2002 CocoaTech. All rights reserved.
//

#import <Foundation/Foundation.h>

@class NTFileDesc;

@interface NTVolumeMount : NSObject
{
    FSVolumeOperation volumeOp;
    
    FSVolumeMountUPP mountUPP;
    NSURL* url; // used for mount
    NSString* notificationName;
	
	NSString* dictionaryKey;
}

@property (nonatomic, retain) NSURL* url;
@property (nonatomic, retain) NSString* notificationName;
@property (nonatomic, retain) NSString* dictionaryKey;

+ (NTVolumeMount*)mountVolumeWithURL:(NSURL*)url
								user:(NSString*)user 
							password:(NSString*)password
					notifyWhenMounts:(NSString*)notificationName
					   dictionaryKey:(NSString*)theDictionaryKey;

+ (NSString*)dictionaryKey:(NSURL*)theURL userName:(NSString*)theUserName;

@end
