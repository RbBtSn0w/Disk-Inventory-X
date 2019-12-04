//
//  NTSizeCalculatorThread.m
//  CocoatechFile
//
//  Created by sgehrman on Mon Oct 29 2001.
//  Copyright (c) 2001 CocoaTech. All rights reserved.
//

#import "DirectoryScanThread.h"
#import "NTFileDesc-Utilities.h"

NS_ASSUME_NONNULL_BEGIN

@interface DirectoryScanThread(Private)
- (void) setDirectoryToScan: (NTFileDesc*) desc;
- (void) setDirectoryContent: (NSArray*_Nullable) result; //result; array of NTFileDesc
@end


@implementation DirectoryScanThread

+ (NTThreadRunner*)thread:(NTFileDesc*) directoryToScan
				 delegate:(id<NTThreadRunnerDelegateProtocol>)delegate;
{
    DirectoryScanThread* param = [[[DirectoryScanThread alloc] init] autorelease];
    
    [param setDirectoryToScan: directoryToScan];

	return [NTThreadRunner thread:param
						 priority:1
						 delegate:delegate];	
}

- (void) dealloc
{
	[_directoryToScan release];
	[_directoryContent release];
	
	[super dealloc];
}

- (NTFileDesc*) directoryToScan
{
	return _directoryToScan;
}

//result; array of NTFileDesc
- (NSArray*) directoryContent
{
	return _directoryContent;
}


@end

@implementation DirectoryScanThread(Private)

- (void) setDirectoryToScan: (NTFileDesc*) desc
{
	if ( desc != _directoryToScan )
	{
		[_directoryToScan release];
		_directoryToScan = [desc retain];
	}
}

//result; array of NTFileDesc
- (void) setDirectoryContent: (NSArray*_Nullable) result
{
	if ( result != _directoryContent )
	{
		[_directoryContent release];
		_directoryContent = [result retain];
	}
}

@end



@implementation DirectoryScanThread (Thread)

// must subclass to do work
- (BOOL)doThreadProc;
{
    NTFileDesc* directory = [self directoryToScan];
	
    NSArray *result = [directory directoryContentsAutoreleased];
    
	if (![[self helper] killed])
		[self setDirectoryContent: result];
		
    return (![[self helper] killed]);
}

@end

NS_ASSUME_NONNULL_END
