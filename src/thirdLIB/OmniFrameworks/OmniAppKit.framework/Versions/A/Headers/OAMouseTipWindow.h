// Copyright 2002-2019 Omni Development, Inc. All rights reserved.
//
// This software may only be used and reproduced according to the
// terms in the file OmniSourceLicense.html, which should be
// distributed with this project and can also be found at
// <http://www.omnigroup.com/developer/sourcecode/sourcelicense/>.

#import <AppKit/NSPanel.h>

@class NSAttributedString;
@class NSTimer;
@class OAMouseTipView;

typedef enum {
    OAMouseTipUnsetStyle = -1,
    OAMouseTipTooltipStyle,
    OAMouseTipExposeStyle,
    OAMouseTipDockStyle,
} OAMouseTipStyle;

#define OAMouseTipsEnabledPreferenceKey (@"OADisplayMouseTips")
#define OAMouseTipsNotesEnabledPreferenceKey (@"OADisplayNoteMouseTips")

@interface OAMouseTipWindow : NSPanel
{
    id nonretainedOwner;
    OAMouseTipView *mouseTipView;
    OAMouseTipStyle currentStyle;
    NSTimer *waitTimer;
    BOOL hasRegisteredForNotification;
}

// API

+ (void)setStyle:(OAMouseTipStyle)aStyle;
+ (NSDictionary *)textAttributesForCurrentStyle;
+ (void)setLevel:(int)windowLevel;

+ (void)showMouseTipWithTitle:(NSString *)aTitle;
+ (void)showMouseTipWithTitle:(NSString *)aTitle activeRect:(NSRect)activeRect edge:(NSRectEdge)onEdge delay:(CGFloat)delay;
+ (void)showMouseTipWithAttributedTitle:(NSAttributedString *)aTitle;
+ (void)showMouseTipWithAttributedTitle:(NSAttributedString *)aTitle activeRect:(NSRect)activeRect maxWidth:(CGFloat)maxWidth edge:(NSRectEdge)onEdge delay:(CGFloat)delay;
+ (void)hideMouseTip;

// A way to keep objects from hiding the tip if it is now being used by someone else 
// +hideMouseTipForOwner: does nothing if the owner doesn't match the last +setOwner call
+ (void)setOwner:(id)owner;
+ (void)hideMouseTipForOwner:(id)owner;

@end
