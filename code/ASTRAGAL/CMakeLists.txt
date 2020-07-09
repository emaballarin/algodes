cmake_minimum_required (VERSION 2.6)
project (astragal)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -march=native -flto")

add_executable (strassen_test main.c matrix.c strassen.c test.c util.c)
