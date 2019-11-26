//
//  NTFileDescData.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 10/24/05.
//  Copyright 2005 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NTVolume, NTFileTypeIdentifier;

@interface NTFileDescData : NSObject
{
	NTObjectContainer* cache;
	NTUInt64Container* cache64;
	NTUInt32Container* cache32;
	
	struct {
        unsigned int cachedIsFile:1;
		
		unsigned int cachedIsApplication:1;
		unsigned int cachedIsPackage:1;
		unsigned int cachedIsCarbonAlias:1;
		unsigned int cachedIsPathFinderAlias:1;
        unsigned int cachedIsSymbolicLink:1;
		
		unsigned int cachedIsInvisible:1;        
		unsigned int cachedIsExtensionHidden:1;
        unsigned int cachedIsLocked:1;
        unsigned int cachedHasCustomIcon:1;
        unsigned int cachedIsStationery:1;
        unsigned int cachedIsBundleBitSet:1;
        unsigned int cachedIsAliasBitSet:1;
        unsigned int cachedIsReadable:1;
        unsigned int cachedIsExecutable:1;
        unsigned int cachedIsWritable:1;
        unsigned int cachedIsDeletable:1;
        unsigned int cachedIsRenamable:1;
        unsigned int cachedIsReadOnly:1;
        unsigned int cachedIsMovable:1;
						
		unsigned int cachedIsStickyBitSet:1;
		unsigned int cachedIsPipe:1;
        unsigned int cachedIsVolume:1;
        unsigned int cachedHasDirectoryContents:1;
        unsigned int cachedHasVisibleDirectoryContents:1;
		unsigned int cachedIsServerAlias:1;
        unsigned int cachedIsBrokenAlias:1;
				
		unsigned int cachedIsParentAVolume:1;
        unsigned int cachedIsNameLocked:1;
        unsigned int cachedHasBeenModified:1;
        unsigned int cachedHasBeenRenamed:1;
		
    } bools;    
	
	struct {
        unsigned int displayName_initialized:1;
        unsigned int iconImage_initialized:1;
        unsigned int isFile_initialized:1;
		
        unsigned int kind_initialized:1;
        unsigned int architecture_initialized:1;
        unsigned int extension_initialized:1;
        unsigned int icon_initialized:1;
		
		unsigned int modificationDate_initialized:1;
		unsigned int creationDate_initialized:1;
		unsigned int attributeDate_initialized:1;
		unsigned int accessDate_initialized:1;
		unsigned int lastUsedDate_initialized:1;
		
		unsigned int version_initialized:1;
		unsigned int bundleVersion_initialized:1;
		unsigned int getInfo_initialized:1;
		unsigned int application_initialized:1;
		unsigned int comments_initialized:1;
		unsigned int cachedURL_initialized:1;
		unsigned int dictionaryKey_initialized:1;		
		unsigned int strictDictionaryKey_initialized:1;		
		
		unsigned int permissionString_initialized:1;		
		unsigned int ownerName_initialized:1;		
		unsigned int groupName_initialized:1;		
		unsigned int uniformTypeID_initialized:1;		
		unsigned int bundleSignature_initialized:1;		
		unsigned int bundleIdentifier_initialized:1;		
		unsigned int itemInfo_initialized:1;		
		
		unsigned int volume_initialized:1;		
		unsigned int typeIdentifier_initialized:1;		
		
		unsigned int isPackage_initialized:1;
		unsigned int isApplication_initialized:1;
		unsigned int isCarbonAlias_initialized:1;
        unsigned int isPathFinderAlias_initialized:1;
        unsigned int isSymbolicLink_initialized:1;		
		
		unsigned int isInvisible_initialized:1;
        unsigned int isExtensionHidden_initialized:1;
        unsigned int isLocked_initialized:1;
        unsigned int hasCustomIcon_initialized:1;
        unsigned int isStationery_initialized:1;
        unsigned int isBundleBitSet_initialized:1;
        unsigned int isAliasBitSet_initialized:1;
        unsigned int isReadable_initialized:1;
        unsigned int isExecutable_initialized:1;
        unsigned int isWritable_initialized:1;
        unsigned int isDeletable_initialized:1;
        unsigned int isRenamable_initialized:1;
        unsigned int isReadOnly_initialized:1;
        unsigned int isMovable_initialized:1;
	
		unsigned int posixPermissions_initialized:1;
		unsigned int posixFileMode_initialized:1;
		unsigned int vRefNum_initialized:1;
		unsigned int valence_initialized:1;
		unsigned int fileSize_initialized:1;
		unsigned int physicalFileSize_initialized:1;
		unsigned int metadata_initialized:1;
		
		unsigned int isStickyBitSet_initialized:1;
		unsigned int isPipe_initialized:1;
        unsigned int isVolume_initialized:1;
        unsigned int hasDirectoryContents_initialized:1;
        unsigned int hasVisibleDirectoryContents_initialized:1;
        unsigned int isServerAlias_initialized:1;
        unsigned int isBrokenAlias_initialized:1;
				
		unsigned int resolvedDesc_initialized:1;
		
		unsigned int rsrcForkSize_initialized:1;
		unsigned int dataForkSize_initialized:1;

		unsigned int mRsrcForkPhysicalSize_initialized:1;
		unsigned int mDataForkPhysicalSize_initialized:1;

		unsigned int type_initialized:1;
		unsigned int creator_initialized:1;
		unsigned int label_initialized:1;
		unsigned int groupID_initialized:1;
		unsigned int ownerID_initialized:1;
		
		unsigned int nodeID_initialized:1;
		unsigned int parentDirID_initialized:1;

		unsigned int isParentAVolume_initialized:1;
        unsigned int isNameLocked_initialized:1;
		
		unsigned int originalAliasFilePath_initialized:1;
        unsigned int hasBeenModified_initialized:1;
        unsigned int hasBeenRenamed_initialized:1;

	} flags;    
}

- (BOOL)displayName_initialized:(NSString**)outValue;
- (void)setDisplayName:(NSString*)value;

- (BOOL)iconImage_initialized:(NSImage**)outValue;
- (void)setIconImage:(NSImage*)value;

- (BOOL)isFile_initialized:(BOOL*)outValue;
- (void)setIsFile:(BOOL)value;

- (BOOL)kind_initialized:(NSString**)outValue;
- (void)setKind:(NSString*)value;

- (BOOL)architecture_initialized:(NSString**)outValue;
- (void)setArchitecture:(NSString*)value;

- (BOOL)extension_initialized:(NSString**)outValue;
- (void)setExtension:(NSString*)value;

- (BOOL)icon_initialized:(NTIcon**)outValue;
- (void)setIcon:(NTIcon*)value;

- (BOOL)modificationDate_initialized:(NSDate**)outValue;
- (void)setModificationDate:(NSDate*)value;

- (BOOL)attributeDate_initialized:(NSDate**)outValue;
- (void)setAttributeDate:(NSDate*)value;

- (BOOL)accessDate_initialized:(NSDate**)outValue;
- (void)setAccessDate:(NSDate*)value;

- (BOOL)creationDate_initialized:(NSDate**)outValue;
- (void)setCreationDate:(NSDate*)value;

- (BOOL)lastUsedDate_initialized:(NSDate**)outValue;
- (void)setLastUsedDate:(NSDate*)value;

- (BOOL)version_initialized:(NSString**)outValue;
- (void)setVersion:(NSString*)value;

- (BOOL)bundleVersion_initialized:(NSString**)outValue;
- (void)setBundleVersion:(NSString*)value;

- (BOOL)bundleIdentifier_initialized:(NSString**)outValue;
- (void)setBundleIdentifier:(NSString*)value;

- (BOOL)getInfo_initialized:(NSString**)outValue;
- (void)setGetInfo:(NSString*)value;

- (BOOL)application_initialized:(NTFileDesc**)outValue;
- (void)setApplication:(NTFileDesc*)value;

- (BOOL)comments_initialized:(NSString**)outValue;
- (void)setComments:(NSString*)value;

- (BOOL)cachedURL_initialized:(NSURL**)outValue;
- (void)setCachedURL:(NSURL*)value;
- (void)removeCachedURL; // reset back to uninitialized

- (BOOL)dictionaryKey_initialized:(NSString**)outValue;
- (void)setDictionaryKey:(NSString*)value;

- (BOOL)strictDictionaryKey_initialized:(NSString**)outValue;
- (void)setStrictDictionaryKey:(NSString*)value;

- (BOOL)permissionString_initialized:(NSString**)outValue;
- (void)setPermissionString:(NSString*)value;

- (BOOL)ownerName_initialized:(NSString**)outValue;
- (void)setOwnerName:(NSString*)value;

- (BOOL)groupName_initialized:(NSString**)outValue;
- (void)setGroupName:(NSString*)value;

- (BOOL)uniformTypeID_initialized:(NSString**)outValue;
- (void)setUniformTypeID:(NSString*)value;

- (BOOL)bundleSignature_initialized:(NSString**)outValue;
- (void)setBundleSignature:(NSString*)value;

- (BOOL)itemInfo_initialized:(NSString**)outValue;
- (void)setItemInfo:(NSString*)value;

- (BOOL)volume_initialized:(NTVolume**)outValue;
- (void)setVolume:(NTVolume*)value;

- (BOOL)typeIdentifier_initialized:(NTFileTypeIdentifier**)outValue;
- (void)setTypeIdentifier:(NTFileTypeIdentifier*)value;

- (BOOL)isPackage_initialized:(BOOL*)outValue;
- (void)setIsPackage:(BOOL)value;

- (BOOL)isApplication_initialized:(BOOL*)outValue;
- (void)setIsApplication:(BOOL)value;

- (BOOL)isCarbonAlias_initialized:(BOOL*)outValue;
- (void)setIsCarbonAlias:(BOOL)value;

- (BOOL)isPathFinderAlias_initialized:(BOOL*)outValue;
- (void)setIsPathFinderAlias:(BOOL)value;

- (BOOL)isSymbolicLink_initialized:(BOOL*)outValue;
- (void)setIsSymbolicLink:(BOOL)value;

- (BOOL)isInvisible_initialized:(BOOL*)outValue;
- (void)setIsInvisible:(BOOL)value;

- (BOOL)isExtensionHidden_initialized:(BOOL*)outValue;
- (void)setIsExtensionHidden:(BOOL)value;

- (BOOL)isLocked_initialized:(BOOL*)outValue;
- (void)setIsLocked:(BOOL)value;

- (BOOL)hasCustomIcon_initialized:(BOOL*)outValue;
- (void)setHasCustomIcon:(BOOL)value;

- (BOOL)isStationery_initialized:(BOOL*)outValue;
- (void)setIsStationery:(BOOL)value;

- (BOOL)isBundleBitSet_initialized:(BOOL*)outValue;
- (void)setIsBundleBitSet:(BOOL)value;

- (BOOL)isAliasBitSet_initialized:(BOOL*)outValue;
- (void)setIsAliasBitSet:(BOOL)value;

- (BOOL)isReadable_initialized:(BOOL*)outValue;
- (void)setIsReadable:(BOOL)value;

- (BOOL)isWritable_initialized:(BOOL*)outValue;
- (void)setIsWritable:(BOOL)value;

- (BOOL)isExecutable_initialized:(BOOL*)outValue;
- (void)setIsExecutable:(BOOL)value;

- (BOOL)isDeletable_initialized:(BOOL*)outValue;
- (void)setIsDeletable:(BOOL)value;

- (BOOL)isRenamable_initialized:(BOOL*)outValue;
- (void)setIsRenamable:(BOOL)value;

- (BOOL)isReadOnly_initialized:(BOOL*)outValue;
- (void)setIsReadOnly:(BOOL)value;

- (BOOL)isMovable_initialized:(BOOL*)outValue;
- (void)setIsMovable:(BOOL)value;

- (BOOL)posixPermissions_initialized:(UInt32*)outValue;
- (void)setPosixPermissions:(UInt32)value;

- (BOOL)posixFileMode_initialized:(UInt32*)outValue;
- (void)setPosixFileMode:(UInt32)value;

- (BOOL)vRefNum_initialized:(FSVolumeRefNum*)outValue;
- (void)setVRefNum:(FSVolumeRefNum)value;

- (BOOL)valence_initialized:(UInt32*)outValue;
- (void)setValence:(UInt32)value;

- (BOOL)fileSize_initialized:(UInt64*)outValue;
- (void)setFileSize:(UInt64)value;

- (BOOL)physicalFileSize_initialized:(UInt64*)outValue;
- (void)setPhysicalFileSize:(UInt64)value;

- (BOOL)metadata_initialized:(NTMetadata**)outValue;
- (void)setMetadata:(NTMetadata*)value;

- (BOOL)isStickyBitSet_initialized:(BOOL*)outValue;
- (void)setIsStickyBitSet:(BOOL)value;

- (BOOL)isPipe_initialized:(BOOL*)outValue;
- (void)setIsPipe:(BOOL)value;

- (BOOL)isVolume_initialized:(BOOL*)outValue;
- (void)setIsVolume:(BOOL)value;

- (BOOL)hasDirectoryContents_initialized:(BOOL*)outValue;
- (void)setHasDirectoryContents:(BOOL)value;

- (BOOL)hasVisibleDirectoryContents_initialized:(BOOL*)outValue;
- (void)setHasVisibleDirectoryContents:(BOOL)value;

- (BOOL)isServerAlias_initialized:(BOOL*)outValue;
- (void)setIsServerAlias:(BOOL)value;

- (BOOL)isBrokenAlias_initialized:(BOOL*)outValue;
- (void)setIsBrokenAlias:(BOOL)value;

- (BOOL)resolvedDesc_initialized:(NTFileDesc**)outValue;
- (void)setResolvedDesc:(NTFileDesc*)value;

- (BOOL)rsrcForkSize_initialized:(UInt64*)outValue;
- (void)setRsrcForkSize:(UInt64)value;

- (BOOL)dataForkSize_initialized:(UInt64*)outValue;
- (void)setDataForkSize:(UInt64)value;

- (BOOL)rsrcForkPhysicalSize_initialized:(UInt64*)outValue;
- (void)setRsrcForkPhysicalSize:(UInt64)value;

- (BOOL)dataForkPhysicalSize_initialized:(UInt64*)outValue;
- (void)setDataForkPhysicalSize:(UInt64)value;

- (BOOL)type_initialized:(OSType*)outValue;
- (void)setType:(OSType)value;

- (BOOL)creator_initialized:(OSType*)outValue;
- (void)setCreator:(OSType)value;

- (BOOL)label_initialized:(UInt32*)outValue;
- (void)setLabel:(UInt32)value;

- (BOOL)groupID_initialized:(UInt32*)outValue;
- (void)setGroupID:(UInt32)value;

- (BOOL)ownerID_initialized:(UInt32*)outValue;
- (void)setOwnerID:(UInt32)value;

- (BOOL)nodeID_initialized:(UInt32*)outValue;
- (void)setNodeID:(UInt32)value;

- (BOOL)parentDirID_initialized:(UInt32*)outValue;
- (void)setParentDirID:(UInt32)value;

- (BOOL)isParentAVolume_initialized:(BOOL*)outValue;
- (void)setIsParentAVolume:(BOOL)value;

- (BOOL)isNameLocked_initialized:(BOOL*)outValue;
- (void)setIsNameLocked:(BOOL)value;

- (BOOL)originalAliasFilePath_initialized:(NSString**)outValue;
- (void)setOriginalAliasFilePath:(NSString*)value;

- (BOOL)hasBeenModified_initialized:(BOOL*)outValue;
- (void)setHasBeenModified:(BOOL)value;

- (BOOL)hasBeenRenamed_initialized:(BOOL*)outValue;
- (void)setHasBeenRenamed:(BOOL)value;

@end

