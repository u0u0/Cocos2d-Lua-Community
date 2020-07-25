/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AppDelegate.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "cocos2d.h"
#include "scripting/lua-bindings/manual/lua_module_register.h"
#include "external/xxtea/xxtea.h"

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0 };

    GLView::setGLContextAttrs(glContextAttrs);
}

int register_custom_module(lua_State* L)
{
    // Register your custom module add in Classes here.
    return 1;
}

static void decoder(Data &data)
{
    unsigned char sign[] = "Xt";
    unsigned char key[] = "aaa";

    // decrypt XXTEA
    if (!data.isNull()) {
        bool isEncoder = false;
        unsigned char *buf = data.getBytes();
        ssize_t size = data.getSize();
        ssize_t len = strlen((char *)sign);
        if (size <= len) {
            return;
        }

        for (int i = 0; i < len; ++i) {
            isEncoder = buf[i] == sign[i];
            if (!isEncoder) {
                break;
            }
        }

        if (isEncoder) {
            xxtea_long newLen = 0;
            unsigned char* buffer = xxtea_decrypt(buf + len,
                    (xxtea_long)(size - len),
                    (unsigned char*)key,
                    (xxtea_long)strlen((char *)key),
                    &newLen);
            data.clear();
            data.fastSet(buffer, newLen);
        }
    }
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
        glview = cocos2d::GLViewImpl::create("__PROJECT_COCOS_NAME__");
        director->setOpenGLView(glview);
        director->startAnimation();
    }

    // set default FPS
    director->setAnimationInterval(1.0 / 60.0f);

    // register lua module
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    LuaStack *stack = engine->getLuaStack();
    lua_State *L = stack->getLuaState();
    lua_module_register(L);
    //register custom function
    register_custom_module(L);

    // resource decode, game32.zip & game64.zip deal as resoruce.
    //FileUtils::getInstance()->setFileDataDecoder(decoder);
#if 0 // set to 1 for release mode
    // use luajit bytecode package
#if defined(__aarch64__) || defined(__arm64__) || defined(__x86_64__)
    stack->loadChunksFromZIP("res/game64.zip");
#else
    stack->loadChunksFromZIP("res/game32.zip");
#endif
    stack->executeString("require 'main'");
#else // #if 0
    // use discrete files
    engine->executeScriptFile("src/main.lua");
#endif

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("APP_ENTER_BACKGROUND_EVENT");
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("APP_ENTER_FOREGROUND_EVENT");
}
