
#import "ConsoleWindowController.h"

@interface ConsoleWindowController ()

@end

#define MAX_LINES_COUNT     200

@implementation ConsoleWindowController
@synthesize textView;

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self)
    {
        // Initialization code here.
        linesCount = [[NSMutableArray arrayWithCapacity:MAX_LINES_COUNT + 1] retain];
        // init pipe
        NSPipe *pipe = [NSPipe pipe];
        readHandle = [pipe fileHandleForReading];
        int outfd = [[pipe fileHandleForWriting] fileDescriptor];
        if (dup2(outfd, fileno(stderr)) != fileno(stderr) || dup2(outfd, fileno(stdout)) != fileno(stdout)) {
            perror("Unable to redirect output");
        } else {
            [[NSNotificationCenter defaultCenter] addObserver: self
                                                     selector: @selector(handleNotification:)
                                                         name: NSFileHandleReadCompletionNotification
                                                       object: readHandle];
            [readHandle readInBackgroundAndNotify];
        }
    }

    return self;
}

- (void)dealloc
{
    [linesCount release];
    [super dealloc];
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

- (void)handleNotification:(NSNotification *)note
{
    [readHandle readInBackgroundAndNotify];
    NSData *data = [[note userInfo] objectForKey:NSFileHandleNotificationDataItem];
    NSString *str = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];
    if (str) {
        [self trace:str];
    } else {
        NSLog(@"Received non utf8 data, can't print");
    }
}

- (void) trace:(NSString*)msg
{
    NSFont *font = [NSFont fontWithName:@"Monaco" size:12.0];
    NSDictionary *attrsDictionary = [NSDictionary dictionaryWithObject:font forKey:NSFontAttributeName];
    NSAttributedString *string = [[[NSAttributedString alloc] initWithString:msg attributes:attrsDictionary] autorelease];
    NSNumber *len = [NSNumber numberWithUnsignedInteger:[string length]];
    [linesCount addObject:len];

	NSTextStorage *storage = [textView textStorage];
	[storage beginEditing];
	[storage appendAttributedString:string];

    if ([linesCount count] >= MAX_LINES_COUNT)
    {
        len = [linesCount objectAtIndex:0];
        [storage deleteCharactersInRange:NSMakeRange(0, [len unsignedIntegerValue])];
        [linesCount removeObjectAtIndex:0];
    }

	[storage endEditing];
    [textView setTextColor:[NSColor systemBlueColor]];// log text color
    [self changeScroll];
}

- (void) changeScroll
{
    BOOL scroll = [checkScroll state] == NSControlStateValueOn;
    if(scroll)
    {
        [self.textView scrollRangeToVisible: NSMakeRange(self.textView.string.length, 0)];
    }
}

- (IBAction)onClear:(id)sender
{
    NSTextStorage *storage = [textView textStorage];
    [storage setAttributedString:[[[NSAttributedString alloc] initWithString:@""] autorelease]];
}

- (IBAction)onScrollChange:(id)sender
{
    [self changeScroll];
}

- (IBAction)onTopChange:(id)sender
{
    BOOL isTop = [topCheckBox state] == NSControlStateValueOn;
    if(isTop)
    {
        [self.window setLevel:NSFloatingWindowLevel];
    }
    else
    {
        [self.window setLevel:NSNormalWindowLevel];
    }
}

@end
