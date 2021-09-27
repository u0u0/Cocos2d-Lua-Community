# Cocos2d-Lua-Community

Cocos2d-Lua-Community is a improved of Cocos2d-x 4.0, and easy to use Lua game engine. It's Lua "frameworks" compatible with Quick-Cocos2dx-Community v3.7.x.

## Get Help

* [http://www.cocos2d-lua.org/](http://www.cocos2d-lua.org/)
* QQ qun:
	* 社区版 千人群(1群)号：361920466
	* 社区版 2群：138934064

## Feature

* No installation required, No Environment Setup.
* OpenAL audio output engine, designed for Lua.
* Integrate more thirdpart Lua libraries: protobuf,lsqlite3 etc.
* Refactor TMX runtime, support Tiled Map Editor 1.2+.
* Spine runtime update to 3.8.
* Support FairyGUI.

## Develop Requirements

* Mac OS X 10.11+, Xcode 10+
* Windows 7+, Visual Studio 2019
* Python 3.5+
* Android: NDK r20+, Android Studio 3.4+
* Cmake 3.16+ (In Android Studio's cmake plugin 3.10+)

## Runtime Requirements

* iOS 9.0+ for iPhone / iPad games
* Android 3.0.0+ for Android
* Mac OS X v10.11+ for Mac games
* Windows 7+ for Win games, [Microsoft Visual C++ Redistributable for Visual Studio 2019 x86](https://aka.ms/vs/16/release/VC_redist.x86.exe), [Microsoft Visual C++ Redistributable for Visual Studio 2019 x64](https://aka.ms/vs/16/release/VC_redist.x64.exe)

## Lua Game Runner

> Binary of LuaGameRunner is distribute https://github.com/u0u0/Cocos2d-Lua-Community/releases

LuaGameRunner is a replacement of old Player. I just "Keep It Simple and Stupid".

* By default, it run engine test cases.
* By pass parameter, it can run specified project's Lua code.
* Support Shortcut keys:
	* "F5": reload current project.

### Run LuaGameRunner on Mac

```
$cd Cocos2d-Lua-Community
$open ./tools/runner/bin/LuaGameRunner.app
```
### Run LuaGameRunner on Win

```
>cd Cocos2d-Lua-Community
>tools/runner/bin/win32/LuaGameRunner.exe
```

### Parameter

* --width (int), Game window width.
* --height (int), Game window height.
* --scale (int), Window scale factor, the value devide by 100 to get the final scale.
* --log, Write log to file.
* --gamedir, Lua Game project fullpath.
* --writedir, writeable path. Default is same with gamedir.

example:

```
>LuaGameRunner.exe --width 1136 --height 640 --scale 75 --log --gamedir /newprj --writedir /newprj/output
```

## New a game project

Require Python 3.5+ installed.

To create a new project.

```
$cd Cocos2d-Lua-Community
$./tools/CreateProject.py -p www.www.newgame -o /ParentPath
```

> The prject root directory is `/ParentPath/newgame`.

To get help info of CreateProject.py.

```
$CreateProject.py -h
```