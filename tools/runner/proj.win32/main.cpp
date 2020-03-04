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

#include "main.h"
#include "cocos2d.h"
#include "../Classes/AppDelegate.h"
#include "setup.h"

USING_NS_CC;

// uncomment below line, open debug console
#define USE_WIN32_CONSOLE

static WNDPROC oldWinProc = nullptr;
static FILE *fpLogFile = nullptr;

LRESULT CALLBACK winProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_COPYDATA: {
            PCOPYDATASTRUCT pMyCDS = (PCOPYDATASTRUCT)lParam;
            if (fpLogFile && pMyCDS->dwData == 1) {
                const char *szBuf = (const char*)(pMyCDS->lpData);
                fputs(szBuf, fpLogFile);
                fflush(fpLogFile);
                break;
            }
        }
    }
    return oldWinProc(hWnd, uMsg, wParam, lParam);
}

static std::string getEngineRoot(void)
{
    TCHAR szAppDir[MAX_PATH] = { 0 };
    if (!GetModuleFileName(NULL, szAppDir, MAX_PATH))
        return "";
    
    int len = wcslen(szAppDir) + 1;
    char *chAppDir = (char *)malloc(len);
    wcstombs(chAppDir, szAppDir, len);
    chAppDir[len - 1] = '\0';

    // find engine root
    char *p = strstr(chAppDir, "tools\\runner");
    if (p) *p = 0; // cut str
    std::string pathTemp(chAppDir);
    free(chAppDir); // free memory
    return pathTemp;
}

static void relaunchSelf(std::string& cmdLine)
{
    // get exe path
    TCHAR szAppDir[MAX_PATH] = { 0 };
    if (!GetModuleFileName(NULL, szAppDir, MAX_PATH))
        return;

    int len = wcslen(szAppDir) + 1;
    char* chAppDir = (char*)malloc(len);
    wcstombs(chAppDir, szAppDir, len);
    chAppDir[len - 1] = '\0';

    std::string exePath(chAppDir);
    free(chAppDir); // free memory

    std::string winCmd = exePath + " " + cmdLine;

    // http://msdn.microsoft.com/en-us/library/windows/desktop/ms682499(v=vs.85).aspx
    SECURITY_ATTRIBUTES sa = { 0 };
    sa.nLength = sizeof(sa);

    PROCESS_INFORMATION pi = { 0 };
    STARTUPINFO si = { 0 };
    si.cb = sizeof(STARTUPINFO);

#define MAX_COMMAND 1024 // lenth of commandLine is always beyond MAX_PATH

    WCHAR command[MAX_COMMAND];
    memset(command, 0, sizeof(command));
    MultiByteToWideChar(CP_ACP, 0, winCmd.c_str(), -1, command, MAX_COMMAND);

    BOOL success = CreateProcess(NULL,
        command,   // command line
        NULL,      // process security attributes
        NULL,      // primary thread security attributes
        FALSE,     // handles are inherited
        0,         // creation flags
        NULL,      // use parent's environment
        NULL,      // use parent's current directory
        &si,       // STARTUPINFO pointer
        &pi);      // receives PROCESS_INFORMATION
    if (!success) {
        printf("relaunchSelf fail: %s", winCmd.c_str());
    }
    exit(0);
}

int WINAPI _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
    AppDelegate app;
    
    // convert __wargv to argv
    char **argv = (char **)malloc(__argc * sizeof(char *));
    for (int i = 0; i < __argc; ++i) {
        int len = wcslen(__wargv[i]) + 1;
        char *buf = (char *)malloc(len);
        wcstombs(buf, __wargv[i], len);
        buf[len - 1] = '\0';
        argv[i] = buf;
    }

    CommandSetup* cmd = CommandSetup::getInstance();
    cmd->setRelauncher(relaunchSelf);
    cmd->setEngineRootPath(getEngineRoot());
    cmd->parseCommand(__argc, argv);
    cmd->setupEngine();

    // free argv
    for (int i = 0; i < __argc; ++i) {
        free(argv[i]);
    }
    free(argv);

    HWND hwnd = Director::getInstance()->getOpenGLView()->getWin32Window();
    oldWinProc = (WNDPROC)SetWindowLong(hwnd, GWL_WNDPROC, (LONG)winProc);
    std::string logPath = cmd->getLogPath();
    if (logPath.size() > 0) {
        fpLogFile = fopen(logPath.c_str(), "w");
        if (!fpLogFile) {
            printf("Open debug file fail:%s", logPath.c_str());
        }
    }

    int ret = Application::getInstance()->run();

    if (fpLogFile) {
        fclose(fpLogFile);
    }
#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
