#import "ConsoleWindowController.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

// uncomment below line, open debug console.
#define USE_CONSOLE_WINDOW

int main(int argc, char *argv[])
{
    AppDelegate app;
    
#ifdef USE_CONSOLE_WINDOW
    ConsoleWindowController *consoleController = [[ConsoleWindowController alloc] initWithWindowNibName:@"ConsoleWindow"];
    [consoleController.window orderFrontRegardless];
#endif

    return Application::getInstance()->run();
}
