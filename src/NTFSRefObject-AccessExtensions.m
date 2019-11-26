//
//  NTFSRefObject-AccessExtensions.m
//  Disk Inventory X
//
//  Created by Tjark Derlien on 29.11.04.
//  Copyright 2004 Tjark Derlien. All rights reserved.
//

#import "NTFSRefObject-AccessExtensions.h"

@interface NTFSRefObject(MakeVisible)
- (void)updateForFlags:(FSCatalogInfoBitmap)flags;
@end

@implementation NTFSRefObject(AccessExtensions)
/*
- (UInt64)rsrcForkPhysicalSize;
{
    if (!_isValid)
        return 0;
	
    [self updateForFlags:kFSCatInfoDataSizes | kFSCatInfoRsrcSizes];
	
    return _catalogInfo.rsrcPhysicalSize;
}
 */

/*
- (UInt64)dataForkPhysicalSize;
{
	return [self dataPhysicalSize];
    if (!_isValid)
        return 0;
	
    [self updateForFlags:kFSCatInfoDataSizes | kFSCatInfoRsrcSizes];
	
    return _catalogInfo.dataPhysicalSize;
}
 */

@end
