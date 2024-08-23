cmake_minimum_required(VERSION 3.30)
project(archosuAssistent)

set(CMAKE_CXX_STANDARD 23)
include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
)

FetchContent_MakeAvailable(fmt)

add_executable(archosuAssistent main.cpp
        textPrint.cpp
        textPrint.h)


TARGET_LINK_LIBRARIES(archosuAssistent fmt)
