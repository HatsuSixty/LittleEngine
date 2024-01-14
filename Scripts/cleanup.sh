#!/bin/bash

if [ -z "$1" ]; then
    echo "ERROR: no folder to cleanup was provided" >&2
    exit 1
fi

echo "Removing Emacs' backup files..."
find $1 -name "*~" -exec rm {} +
if [ -d "$1/build" ]; then
    echo "Removing build folder..."
    rm -rf $1/build
fi
if [ -d "$1/.cache" ]; then
    echo "Removing .cache folder..."
    rm -rf $1/.cache
fi
