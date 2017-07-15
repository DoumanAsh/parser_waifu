###########################
# Init
##########################
cmake_minimum_required(VERSION 3.5)
set(MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${MODULE_DIR})
include(LazyUtils)
include(QtUtils)

# Generates compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

read_version("${CMAKE_CURRENT_SOURCE_DIR}/version.pri" VER_MAJOR VER_MINOR VER_PATCH)
set(PROJECT_VERSION "${VER_MAJOR}.${VER_MINOR}.${VER_PATCH}")

add_definitions(-DTW_VERSION="${PROJECT_VERSION}")
add_definitions(-DTW_VERSION_MAJOR=${VER_MAJOR})
add_definitions(-DTW_VERSION_MINOR=${VER_MINOR})
add_definitions(-DTW_VERSION_PATCH=${VER_PATCH})

project(ParserWaifu LANGUAGES CXX VERSION ${VER_MAJOR}.${VER_MINOR}.${VER_PATCH})

###########################
# Compiler flags
##########################
set_msvc_flags_if("/W4 /EHsc /O2 /std:c++latest")
set_gcc_flags_if("-Wall -Wextra -O2")
# For MinGW we assume that minimum runtime is Vista
if (WIN32)
    set_gcc_flags_if("-D_WIN32_WINNT=0x0600")
endif()

###########################
# Output dir
##########################
set_output_dir("${CMAKE_BINARY_DIR}/dist")

###########################
# 3PP
##########################
add_subdirectory("3pp/")

###########################
# SRC
##########################
add_subdirectory("src/")

###########################
# cppcheck
##########################
add_custom_target(
    cppcheck
    COMMAND cppcheck
    --enable=all
    --force
    -I "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    ${tw_SRC}
)

############
# Tests
############
option(UNIT_TEST "Build unit tests" OFF)
if (UNIT_TEST)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    include(DownloadProject)
    download_project(
        PROJ googletest
        URL  https://github.com/google/googletest/archive/release-1.8.0.zip
    )

    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

    file(GLOB test_SRC "test/*.cpp")
    add_executable(utest "${test_SRC}")
    target_link_libraries(utest gtest gtest_main)
endif()
