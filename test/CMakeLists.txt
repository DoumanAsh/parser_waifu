set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include(DownloadProject)
download_project(
    PROJ googletest
    URL  https://github.com/google/googletest/archive/release-1.8.0.zip
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

file(GLOB_RECURSE test_SRC "*.cpp")
add_executable(utest "${test_SRC}")
target_link_libraries(utest mecab ${UTILS_LIBS} ${PARSER_LIBS} gtest gtest_main)
target_include_directories(utest PUBLIC ${UTILS_INCLUDES} ${PARSER_INCLUDES})

enable_testing()
add_test(NAME all COMMAND $<TARGET_FILE:utest>)