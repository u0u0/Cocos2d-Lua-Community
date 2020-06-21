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

#include "../Classes/AppDelegate.h"
#include "cocos2d.h"
#include "setup.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <limits.h>

USING_NS_CC;

static std::string getEngineRoot(void)
{
    char processdir[NAME_MAX] = {0};
	if (readlink("/proc/self/exe", processdir, sizeof(processdir))  > 0) {
		char *p = strstr(processdir, "tools/runner");
        if (p) *p = 0; // cut str
	}
	return processdir;
}

#define MAX_ARGS (32) // 32 param is enough for LuaGameRunner
static void relaunchSelf(std::string &cmdLine)
{
    char processdir[NAME_MAX] = {0};
    if (readlink("/proc/self/exe", processdir, sizeof(processdir))  <= 0) {
        printf("Error, relaunchSelf() get bin path fail\n");
        return;
    }

    char *argv[MAX_ARGS] = {0};
    argv[0] = processdir;// first arg is bin path
    int index = 1;

    char *tokenPtr = strtok((char *)cmdLine.c_str(), " ");
    while (tokenPtr && index < MAX_ARGS) {
        argv[index++] = tokenPtr;
        tokenPtr = strtok(NULL, " ");
    }

    execv("/proc/self/exe", argv);
    exit(0);
}
#undef MAX_ARGS

int main(int argc, char **argv)
{
    // create the application instance
    AppDelegate app;

    CommandSetup *cmd = CommandSetup::getInstance();
    cmd->setRelauncher(relaunchSelf);
    cmd->setEngineRootPath(getEngineRoot());
    cmd->parseCommand(argc, argv);
    cmd->setupEngine();

    return Application::getInstance()->run();
}
