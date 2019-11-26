#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>

@class NTFileDesc;

@interface NTProcess : NSObject <NSCoding>
{
    BOOL mIsValid;
    NSDictionary* mDictionary;
    NTFileDesc* mDesc;
    ProcessSerialNumber	mPsn;
}

+ (NTProcess*)processWithPSN:(ProcessSerialNumber)psn;

- (BOOL)isValid;
- (NTFileDesc *)desc;
- (ProcessSerialNumber)psn;

- (NSString*)displayName;  // name is localized
- (NSString*)name;        // full name including extension ie: [[self desc] name]
- (NSString*)processCreatorCode;

- (BOOL)isBackgroundOnly;
- (BOOL)isBackgroundOnlyWithUI;

- (NSNumber*)processID;  // UInt32

- (BOOL)isEqualToCurrent;
- (BOOL)isEqualToFront;

- (BOOL)isStillRunning;

- (void)show;
- (void)hide;
- (BOOL)isHidden;

- (void)quit; // sends a quit event
- (void)kill;

- (void)makeFront:(BOOL)frontWindowOnly unminimizeWindows:(BOOL)unminimizeWindows;

- (NSComparisonResult)compareByProcessName:(NTProcess *)fsi;

@end

