set(3PP_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/toml ${CMAKE_CURRENT_SOURCE_DIR}/mecab/mecab/src/ PARENT_SCOPE)

set(MECAB_EXE OFF)
add_subdirectory("mecab/")
