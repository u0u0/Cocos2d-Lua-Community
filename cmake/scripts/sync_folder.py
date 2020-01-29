#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
"""
NAME
    sync_folder --

SYNOPSIS
    sync_folder [-h]

    -h show help
    -s src path
    -d dest path
"""

import os
import sys
import getopt
import shutil

def joinDir(root, *dirs):
    for item in dirs:
        root = os.path.join(root, item)
    return root

def copyFile(src, dest):
    inFp = open(src, 'rb')
    outFp = open(dest, 'wb')
    buff = inFp.read()
    outFp.write(buff)
    inFp.close()
    outFp.close()

def copyDir(src, dest):
    for item in os.listdir(src):
        if "." == item[0]: # ignore hidden files
            continue

        nSrc = joinDir(src, item)
        nDest = joinDir(dest, item)
        if os.path.isfile(nSrc):
            copyFile(nSrc, nDest)
        else:
            if not os.path.exists(nDest):
                os.mkdir(nDest)
            copyDir(nSrc, nDest)

if __name__ == "__main__":
    # ===== parse args =====
    try:
        opts, args = getopt.getopt(sys.argv[1:], "hs:d:")
    except getopt.GetoptError:
        # print help information and exit:
        print(__doc__)
        sys.exit(-2)

    srcDir = ""
    destDir = ""
    for o, a in opts:
        if o == "-h":
            # print help information and exit:
            print(__doc__)
            sys.exit(0)
        if o == "-s":
            srcDir = a
        if o == "-d":
            destDir = a

    if len(srcDir) == 0:
        print("Error: use -s xxx to set src path")
        sys.exit(-2)
    if len(destDir) == 0:
        print("Error: use -d xxx to set dest path")
        sys.exit(-2)

    # start sync
    if os.path.exists(destDir):
        shutil.rmtree(destDir)
    os.makedirs(destDir)
    copyDir(srcDir, destDir)
