//
//  NTAuthOpen.h
//  CocoaTechFoundation
//
//  Created by Steve Gehrman on 4/5/05.
//  Copyright 2005 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NTFileDesc;

#define NTAuthOpenCompletionNotification @"NTAuthOpenCompletionNotification"
#define NTAuthOpenReadData @"NTAuthOpenReadData"  // exists for a read, object is NSData
#define NTAuthOpenErrorString @"NTAuthOpenErrorString"

@interface NTAuthOpen : NSObject 
{
	NTTaskController* mv_readTask;
	NTTaskController* mv_writeTask;
	
	id notificationObject;
	NSData* readData;
}

@property (retain) NSData* readData;
@property (retain) id notificationObject;

// both operations are async, read results are sent in the completion notification
// returns object that the caller uses to observer for notifications, this prevents multiple clients from getting notifications mixed up
+ (id)writeData:(NSData*)input toFile:(NTFileDesc*)desc;
+ (id)readDataFromFile:(NTFileDesc*)desc;

// short cuts for adding and removing observers
+ (void)observe:(id)target selector:(SEL)selector object:(id)object;
+ (void)remove:(id)target object:(id)object;

@end

#if 0

// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
// usage pattern

{
	id mv_authOpenNotificationObj;
	NTFileDesc* mv_authOpenDesc;
}

{
	mv_authOpenNotificationObj = [[NTAuthOpen readDataFromFile:desc] retain];
	mv_authOpenDesc = [desc retain];
	
	[NTAuthOpen observe:self selector:@selector(authOpenNotification:) object:mv_authOpenNotificationObj];		
}

- (void)authOpenNotification:(NSNotification*)notification;
{
	if ([notification object] == mv_authOpenNotificationObj)
	{
		// did an error occur?
		if ([[notification userInfo] objectForKey:NTAuthOpenErrorString])
			NSLog([[notification userInfo] objectForKey:NTAuthOpenErrorString]);
		else
		{
			NSData *readData = [[notification userInfo] objectForKey:NTAuthOpenReadData];
			
			if (readData && [readData isKindOfClass:[NSData class]])
			{
				// use data
			}
			else
			{
				// maybe it was a write call?
			}
		}
		
		[NTAuthOpen remove:self object:mv_authOpenNotificationObj];
	}
}

- (void)dealloc;
{
	[NTAuthOpen remove:self object:mv_authOpenNotificationObj];
	[mv_authOpenNotificationObj release];
	[mv_authOpenDesc release];
	
	[super dealloc];
}

#endif
