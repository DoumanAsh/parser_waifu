#########
# utils
#########
set(UTILS_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/utils" PARENT_SCOPE)

file(GLOB utils_SRC "utils/*.cpp")
add_library(pw_utils STATIC ${utils_SRC})

set(UTILS_LIBS "pw_utils" PARENT_SCOPE)

#########
# parser
#########
set(PARSER_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/parser" PARENT_SCOPE)

file(GLOB parser_SRC "parser/*.cpp")
add_library(pw_parser STATIC ${parser_SRC})
target_include_directories(pw_parser PUBLIC ${3PP_INCLUDES})
target_link_libraries(pw_parser mecab)

set(PARSER_LIBS "pw_parser" PARENT_SCOPE)
