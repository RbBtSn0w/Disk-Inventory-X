//
//  NTFileRep.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 11/30/08.
//  Copyright 2008 Cocoatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NTFileRep : NSObject <NSCoding>
{
	UInt32 nodeID;
	NSString* displayName;
	BOOL isDirectory;
	
	BOOL isVolume;
	FSVolumeRefNum volumeRefNum; // volumeRefNum can be used for quick compares of an unchanging list of files/dirs/volumes
	
	// nodeID is useless for volumes, compare url and capacity
	NSURL *volumeURL;
	UInt64 volumeCapacity;
	NSString* volumeUniqueID;  // only for local drives
}

@property (readonly, nonatomic, assign) UInt32 nodeID;
@property (readonly, nonatomic, assign) BOOL isVolume;
@property (readonly, nonatomic, assign) BOOL isDirectory;
@property (readonly, nonatomic, assign) FSVolumeRefNum volumeRefNum;
@property (readonly, nonatomic, retain) NSString* displayName;

+ (NTFileRep*)rep:(NTFileDesc*)theDesc;
+ (NSArray*)reps:(NSArray*)theDescs;

- (BOOL)matchesNodeID:(NTFileDesc*)theDesc;
- (BOOL)matchesDisplayName:(NTFileDesc*)theDesc;

// used externally, accurateMatchKey returns a combo nodeID or vrefNum string to use for matching
// guessMatchKey returns the displayName for inaccurate matching
- (NSString*)accurateMatchKey;
- (NSString*)guessMatchKey;

- (BOOL)isEqual:(NTFileRep*)object;
- (NSUInteger)hash;

@end
