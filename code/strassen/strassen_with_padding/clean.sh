#!/bin/sh
cmake -G "Unix Makefiles" CMakeLists.txt
make clean
rm -R -f ./CMakeFiles ./cmake_install.cmake ./CMakeCache.txt ./Makefile
