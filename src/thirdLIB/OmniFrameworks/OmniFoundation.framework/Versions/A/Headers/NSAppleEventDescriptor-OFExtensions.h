// Copyright 1997-2008 Omni Development, Inc.  All rights reserved.
//
// This software may only be used and reproduced according to the
// terms in the file OmniSourceLicense.html, which should be
// distributed with this project and can also be found at
// <http://www.omnigroup.com/developer/sourcecode/sourcelicense/>.
//
// $Header: svn+ssh://source.omnigroup.com/Source/svn/Omni/tags/OmniSourceRelease/2008-09-09/OmniGroup/Frameworks/OmniFoundation/AppleScript/NSAppleEventDescriptor-OFExtensions.h 104389 2008-08-27 17:59:28Z wiml $

#import <Foundation/NSAppleEventDescriptor.h>

@interface NSAppleEventDescriptor (OFExtensions)
+ (NSAppleEventDescriptor *)descriptorWithFileURL:(NSURL *)furl;
@end

@interface NSDictionary (OFExtensions_NSAppleEventDescriptor)
+ (NSDictionary *)dictionaryWithUserRecord:(NSAppleEventDescriptor *)descriptor;
- (NSAppleEventDescriptor *)userRecordValue;
@end
