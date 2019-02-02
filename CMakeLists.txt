cmake_minimum_required (VERSION 3.10 FATAL_ERROR)
project(TheLittleInvaders LANGUAGES CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
#include(WarningLevel)
#include(WarningAsError)

# Erase any warning level set by default for MSVC compilers
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]|/Wall")
        string(REGEX REPLACE "/W[0-4]|/Wall" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    endif()
endif()

add_subdirectory(src/common)
add_subdirectory(src/engine)
add_subdirectory(src/game)
add_subdirectory(src/launcher)
