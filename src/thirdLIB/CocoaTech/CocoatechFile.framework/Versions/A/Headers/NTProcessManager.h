#import "NTProcess.h"
#import <Cocoa/Cocoa.h>

#define NTPM (NTProcessManager*)[NTProcessManager sharedInstance]

// sends out this notification when an app launches or terminates
#define kNTProcessManagerNotification @"kNTProcessManagerNotification"

@interface NTProcessManager : NTSingletonObject
{
    NSArray *mProcesses;
    NTProcess* _currentProcess;
}

// system UI server controls the menu extras 
+ (void)restartSystemUIServer;

- (NTProcess*)currentProcess;
- (NTProcess*)frontProcess;
- (NTProcess*)processWithLocalizedName:(NSString*)name;  // localized name
- (NTProcess*)processWithName:(NSString*)name;          // full name "Finder.app"
- (NTProcess*)processWithPath:(NSString*)path;

- (NSArray *)processes;
- (NSArray*)foregroundProcesses;
- (NSArray*)backgroundOnlyProcesses;

- (NSArray*)foregroundProcessDescs;
- (NSArray*)processDescs;
- (NSArray*)backgroundOnlyProcessDescs;

- (void)hideAllExcept:(NTProcess*)process;

@end
