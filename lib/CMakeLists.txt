set(UTILS_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/utils" PARENT_SCOPE)

file(GLOB utils_SRC "utils/*.cpp")
add_library(pw_utils STATIC ${utils_SRC})

set(UTILS_LIBS "pw_utils" PARENT_SCOPE)
