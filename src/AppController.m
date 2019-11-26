//
//  AppController.m
//  Disk Inventory X
//
//  Created by Doom on 17.02.19.
//

#import "AppController.h"
#import "DrivesPanelController.h"
#import "Preferences.h"
#import "PrefsPanelController.h"
#import "FileSystemDoc.h"

@implementation AppController

//@@test
- (void)crashWithReport:(NSString *)report
{
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    [pasteboard setString:report forType:NSStringPboardType];
    
    NSAlert *msg = [[[NSAlert alloc] init] autorelease];
    [msg setMessageText: @"internal error"];;
    [msg setInformativeText:report];
    [msg runModal];
}


/*
- (id)init;
{
    self = [super init];
    
    return self;
}

- (IBAction) showPreferencesPanel: (id) sender
{
    [[PrefsPanelController sharedPreferenceController] showPreferencesPanel: self];
    //[[OAPreferenceController sharedPreferenceController] showPreferencesPanel: self];
}

- (IBAction) gotoHomepage: (id) sender
{
    [[NSWorkspace sharedWorkspace] openURL: [NSURL URLWithString: @"http://www.derlien.com"]];
}

- (IBAction) closeDonationPanel: (id) sender;
{
    [_donationPanel close]; //will release itself
    _donationPanel = nil;
}
*/

/*
#pragma mark --------app delegate-----------------

 //Application's delegate; called if file from recent list is selected
- (BOOL) application: (NSApplication*) theApp openFile: (NSString*) fileName
{
    //if "fileName" doesn't exist or isn't a folder, return NO so that it is removed from the recent list
    NSDictionary *attribs = [[NSFileManager defaultManager] fileAttributesAtPath: fileName traverseLink: NO];
    if ( attribs == nil || ![[attribs fileType] isEqualToString: NSFileTypeDirectory] )
        return NO;
    
    [[NSDocumentController sharedDocumentController] openDocumentWithContentsOfFile: fileName
                                                                            display: [self shouldCreateUI]];
    
    //return TRUE to avoid nasty message if user canceled loading
    return TRUE;
}

#pragma mark --------app notifications-----------------

- (void) applicationWillFinishLaunching: (NSNotification*) notification
{
    [self applicationWillFinishLaunching:notification];
    
    //verify that our custom DocumentController is in use
//    NSAssert( [[NSDocumentController sharedDocumentController] isKindOfClass: [MyDocumentController class]], @"the shared DocumentController is not our custom class!" );
    
    g_EnableLogging = [[NSUserDefaults standardUserDefaults] boolForKey: EnableLogging];
    
    //show the drives panel before "applicationDidFinishLaunching" so the panel is visible before the first document is loaded
    //(e.g. through drag&drop)
    [[DrivesPanelController sharedController] showPanel];
}

- (void) applicationDidFinishLaunching:(NSNotification *)notification
{
    [self applicationDidFinishLaunching:notification];
    
    //show donate message
    if ( ![[NSUserDefaults standardUserDefaults] boolForKey: DontShowDonationMessage] )
    {
        [NSBundle loadNibNamed: @"DonationPanel" owner:self];
        [_donationPanel setWorksWhenModal: YES];
    }
    
    //    DIXFinderCMInstaller *installer = [DIXFinderCMInstaller installer];
    //    if ( ![installer isInstalled] )
    //        [installer installToDomain: kUserDomain];
}

#pragma mark -----------------NSMenu delegates-----------------------

- (void) menuNeedsUpdate: (NSMenu*) zoomStackMenu
{
    OBPRECONDITION( _zoomStackMenu == zoomStackMenu );
    
    FileSystemDoc *doc = [[NSDocumentController sharedDocumentController] currentDocument];
    NSArray *zoomStack = [doc zoomStack];
    
    //thanks to ObjC, [zoomStack count] will evaluate to 0 if there is no current doc
    unsigned i;
    for ( i = 0; i < [zoomStack count]; i++ )
    {
        FSItem *fsItem = nil;
        if ( i == 0 )
            fsItem = [doc rootItem];
        else
            fsItem = [zoomStack objectAtIndex: i-1];
        
        if ( i >= ((unsigned) [zoomStackMenu numberOfItems]) )
            [zoomStackMenu addItem: [[[NSMenuItem alloc] init] autorelease]];
        
        NSMenuItem *menuItem = [zoomStackMenu itemAtIndex: i];
        
        [menuItem setTitle: [fsItem displayName]];
        if ( i > 0 ) //no tooltip for first item as the tooltip is the same as the title
            [menuItem setToolTip: [fsItem displayPath]];
        [menuItem setImage: [fsItem iconWithSize: 16]];
        [menuItem setRepresentedObject: fsItem];
        [menuItem setTarget: nil];
        [menuItem setAction: @selector(zoomOutTo:)];
    }
    
    //remove any supernumerary menu items
    while ( ((unsigned) [zoomStackMenu numberOfItems]) > [zoomStack count] )
        [zoomStackMenu removeItemAtIndex: [zoomStackMenu numberOfItems] -1];
}
*/

@end
