#!/bin/bash

echo "This Shell Script will install dependencies for Cocos2d-Lua-Community" 
echo -n "Are you continue? (y/n) "
read answer
if echo "$answer" | grep -iq "^y" ;then
    echo "It will take few minutes"
else
    exit
fi

sudo apt-get update

DEPENDS+=' libx11-dev'
DEPENDS+=' libxmu-dev'
DEPENDS+=' libglu1-mesa-dev'
DEPENDS+=' libgl2ps-dev'
DEPENDS+=' libxi-dev'
DEPENDS+=' libfontconfig1-dev'
DEPENDS+=' libglew-dev'
DEPENDS+=' libgtk-3-dev'
DEPENDS+=' libxxf86vm-dev'
DEPENDS+=' binutils'

sudo apt-get install --yes $DEPENDS
