// Copyright 2020 KeNan Liu
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
    if (p) *p = 0; // cut str
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

static void setupMenu()
{
    // custom app MainMenu
    NSMenu *menubar = [[NSMenu new] autorelease];
    [NSApp setMainMenu:menubar];
    
    // LuaGameRunner
    NSMenuItem *appMenuItem = [[NSMenuItem new] autorelease];
    [menubar addItem:appMenuItem];
    NSMenu *appMenu = [[NSMenu new] autorelease];
    [appMenuItem setSubmenu:appMenu];
    // LuaGameRunner -> About
    NSMenuItem *aboutMenuItem = [[[NSMenuItem alloc] initWithTitle:@"About"
        action:@selector(orderFrontStandardAboutPanel:) keyEquivalent:@""] autorelease];
    [appMenu addItem:aboutMenuItem];
    // LuaGameRunner -> Quit LuaGameRunner
    NSString *appName = [[NSProcessInfo processInfo] processName];
    NSMenuItem *quitMenuItem = [[[NSMenuItem alloc] initWithTitle:[@"Quit " stringByAppendingString:appName]
        action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
    [appMenu addItem:quitMenuItem];
    
    // Edit
    NSMenuItem *editMenuItem = [[NSMenuItem new] autorelease];
    [menubar addItem:editMenuItem];
    NSMenu *editMenu = [[NSMenu new] autorelease];
    editMenu.title = @"Edit";
    [editMenuItem setSubmenu:editMenu];
    // Edit -> copy
    NSMenuItem *cpoyMenuItem = [[[NSMenuItem alloc] initWithTitle:@"Copy"
        action:@selector(copy:) keyEquivalent:@"c"] autorelease];
    [editMenu addItem:cpoyMenuItem];
    // Edit -> Select All
    NSMenuItem *selectAllMenuItem = [[[NSMenuItem alloc] initWithTitle:@"Select All"
        action:@selector(selectAll:) keyEquivalent:@"a"] autorelease];
    [editMenu addItem:selectAllMenuItem];
}

int main(int argc, char *argv[])
{
    AppDelegate app;
    
    CommandSetup *cmd = CommandSetup::getInstance();
    cmd->setRelauncher(relaunchSelf);
    cmd->setEngineRootPath(getEngineRoot());
    if (argc > 2 && strcmp(argv[1], "-NSDocumentRevisionsDebugMode") == 0) {
        argc = 1; // not parse -NSDocumentRevisionsDebugMode YES
    }
    cmd->parseCommand(argc, argv);
    cmd->setupEngine();
    
#ifdef USE_CONSOLE_WINDOW
    // create after GLView inited
    ConsoleWindowController *consoleController = [[ConsoleWindowController alloc] initWithWindowNibName:@"ConsoleWindow"];
    [consoleController.window orderFrontRegardless];

    std::string logPath = cmd->getLogPath();
    if (logPath.size() > 0) {
        [consoleController openLogToFile:logPath.c_str()];
    }
#endif
    
    setupMenu();// after GLView inited

    return Application::getInstance()->run();
}
