//
//  NTFSWatcherItem.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 7/6/05.
//  Copyright 2005 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NTFileDesc, NTFSEventClient, NTDispatchSourceItem, NTFSWatcherItem;

@protocol NTFSWatcherItemDelegateProtocol <NSObject>
- (void)watcherItemWasModified:(NTFSWatcherItem*)watcherItem;
@end

@interface NTFSWatcherItem : NSObject 
{
	NTMessageProxy* delegateProxy;
	NTFileDesc* desc;

	NTMessageProxy* proxy;

	NTFSEventClient* eventClient;
	NTDispatchSourceItem* sourceItem;
}

@property (readonly, nonatomic, retain) NTFileDesc *desc;

+ (NTFSWatcherItem*)itemWithDesc:(NTFileDesc*)desc delegateProxy:(NTMessageProxy*)delegateProxy;

- (NTFileDesc*)desc;
- (void)refreshDesc;
@end
