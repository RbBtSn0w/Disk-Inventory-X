
#import <Cocoa/Cocoa.h>

// ======================================================

@interface DirectoryScanThread : NTThreadRunnerParam
{
	NTFileDesc *_directoryToScan;
	NSArray	*_directoryContent;
}

+ (NTThreadRunner*)thread:(NTFileDesc*) directoryToScan
				 delegate:(id<NTThreadRunnerDelegateProtocol>)delegate;

- (NTFileDesc*) directoryToScan;
- (NSArray*) directoryContent; //result; array of NTFileDesc

@end
