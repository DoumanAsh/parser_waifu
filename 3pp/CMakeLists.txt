set(3PP_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/toml ${CMAKE_CURRENT_SOURCE_DIR}/mecab/mecab/src/ PARENT_SCOPE)

set(MECAB_EXE OFF)
add_subdirectory("mecab/")

# Remove warnings on mecab since i'm not going to fix it here
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(mecab PRIVATE "-w")
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_definitions(mecab PRIVATE _SCL_SECURE_NO_WARNINGS)
    target_compile_options(mecab PRIVATE "/w")
endif()
