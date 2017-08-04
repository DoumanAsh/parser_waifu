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

set(VER_MAJOR 0)
set(VER_MINOR 1)
set(VER_PATCH 0)
add_definitions(-DTW_VERSION_MAJOR=${VER_MAJOR})
add_definitions(-DTW_VERSION_MINOR=${VER_MINOR})
add_definitions(-DTW_VERSION_PATCH=${VER_PATCH})
add_definitions(-DTW_VERSION="${VER_MAJOR}.${VER_MINOR}.${VER_PATCH}")

project(ParserWaifu LANGUAGES CXX VERSION ${VER_MAJOR}.${VER_MINOR}.${VER_PATCH})

remove_msvc_default_warning_level()

###########################
# Compiler flags
##########################
if (WIN32)
    # For MinGW we assume that minimum runtime is Vista
    set_gcc_flags_if("-D_WIN32_WINNT=0x0600")

    # Enforces WinAPI to use unicode version of functions
    add_definitions(-DUNICODE)
    add_definitions(-D_UNICODE)
endif()

###########################
# Output dir
##########################
set_output_dir("${CMAKE_BINARY_DIR}/dist")

###########################
# Boost
##########################
#lazy_find_boost(FileSystem)

###########################
# 3PP
##########################
add_subdirectory("3pp/")

###########################
# Max compile warnings for own code only
##########################
set_msvc_flags_if("/W4")
set_gcc_flags_if("-Wall -Wextra")

###########################
# LIB
##########################
add_subdirectory("lib/")

###########################
# SRC
##########################
add_subdirectory("src/")

############
# Tests
############
option(UNIT_TEST "Build unit tests" OFF)
if (UNIT_TEST)
    add_subdirectory("test/")
endif()

###########################
# cppcheck
##########################
add_custom_target(
    cppcheck
    COMMAND cppcheck
    --enable=all
    --force
    -I "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    -I ${PARSER_INCLUDES}
    --suppress=unusedFunction:*:*
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_SOURCE_DIR}/lib
)
