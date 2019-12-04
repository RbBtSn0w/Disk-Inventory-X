//
//  NTFileDesc-Utilities.h
//  Disk Inventory X
//
//  Created by Tjark Derlien on 08.04.05.
//  Copyright 2005 Tjark Derlien. All rights reserved.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface NTFileDesc(Utilities)

- (NSString*) displayPath;
- (NSImage*) iconImageWithSize: (unsigned) size;
- (NSArray*_Nullable) directoryContentsAutoreleased;

@end

NS_ASSUME_NONNULL_END
