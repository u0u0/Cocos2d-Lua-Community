#include <mach-o/dyld.h>
#include <string.h>

#import "ConsoleWindowController.h"
#include "AppDelegate.h"
#include "setup.h"

USING_NS_CC;

// uncomment below line, open debug console.
#define USE_CONSOLE_WINDOW

static std::string getEngineRoot(void)
{
    // get exe path size
    uint32_t size = 0;
    int res = _NSGetExecutablePath(NULL, &size);
    // get exe path, tools/runner/xxx.app/Contents/MacOS/xxx
    char *path = (char *)malloc(size + 1);
    path[size] = 0;
    res = _NSGetExecutablePath(path, &size);
    // find engine root
    char *p = strstr(path, "tools/runner");
    *p = 0; // cut str
    std::string pathTemp(path);
    free(path); // free memory
    return pathTemp;
}

static void relaunchSelf(std::string &cmdLine)
{
    NSString *nscmdLine = [NSString stringWithCString:cmdLine.c_str()
                                             encoding:NSUTF8StringEncoding];
    NSArray *args = [nscmdLine componentsSeparatedByString:@" "];
    
    NSURL *url = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
    NSMutableDictionary *cfg = [NSMutableDictionary dictionaryWithObject:args
                                                                  forKey:NSWorkspaceLaunchConfigurationArguments];
    NSError *error = nil;
    [[NSWorkspace sharedWorkspace] launchApplicationAtURL:url
                                                  options:NSWorkspaceLaunchNewInstance
                                            configuration:cfg error:&error];
    exit(0);
}

int main(int argc, char *argv[])
{
    AppDelegate app;
    
#ifdef USE_CONSOLE_WINDOW
    ConsoleWindowController *consoleController = [[ConsoleWindowController alloc] initWithWindowNibName:@"ConsoleWindow"];
    [consoleController.window orderFrontRegardless];
#endif
    
    CommandSetup *cmd = CommandSetup::getInstance();
    cmd->setRelauncher(relaunchSelf);
    cmd->setEngineRootPath(getEngineRoot());
    cmd->parseCommand(argc, argv);
    cmd->setupEngine();

    return Application::getInstance()->run();
}
