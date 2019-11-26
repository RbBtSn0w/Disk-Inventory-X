//
//  NTFinderController.h
//  Path Finder
//
//  Created by Steve Gehrman on 6/27/09.
//  Copyright 2009 Cocoatech. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface NTFinderController : NTSingletonObject 
{
	NSBundle* dockBundle;
	NTFileDesc* plistFile;
	id notificationObject;
	
	NSNumber* cachedIsDockHackInstalled;
	NSString* fndrPath;
}

// toggles hack and releases self when done
- (void)toggleDockHack;
- (BOOL)isDockHackInstalled;  // uses cached value for speed, but not 100% accurate

- (void)quitFinder;
- (void)openFinder;
- (BOOL)isFinderRunning;
- (void)toggleFinder;
- (NSString*)finderPath;
- (void)relaunchFinder;

- (BOOL)findersDesktopEnabled;
- (void)setFindersDesktopEnabled:(BOOL)isHidden;
- (void)toggleFindersDesktopEnabled;
@end
