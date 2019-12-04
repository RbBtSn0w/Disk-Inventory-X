
#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN
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
NS_ASSUME_NONNULL_END
