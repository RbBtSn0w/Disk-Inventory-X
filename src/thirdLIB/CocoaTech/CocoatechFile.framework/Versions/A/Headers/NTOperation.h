//
//  NTOperation.h
//  CocoatechFile
//
//  Created by Steve Gehrman on 1/20/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NTOperation;

@protocol NTOperationDelegateProtocol <NSObject>
// called on main thread
- (void)operation_complete:(NTOperation*)operation;
@end

@interface NTOperation : NSOperation
{
	id<NTOperationDelegateProtocol> delegate; // not retained
	id parameter;
	id result;
}
@property (assign) id<NTOperationDelegateProtocol> delegate;
@property (retain) id parameter;
@property (retain) id result;

+ (NTOperation*)operation:(id<NTOperationDelegateProtocol>)theDelegate
				parameter:(id)theParameter;

- (void)clearDelegate;

// override instead of main
- (void)doMain;

@end
