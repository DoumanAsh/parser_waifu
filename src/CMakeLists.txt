###########################
# QT
###########################
find_qt5(Core Gui Widgets)

file(GLOB_RECURSE ui_files_SRC "ui/*.ui")
qt5_wrap_ui(UI_HEADERS ${ui_files_SRC})

###########################
# Main exe
###########################
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB main_SRC "main.cpp")
file(GLOB ui_SRC "ui/*.cpp")

add_executable(pw WIN32 ${main_SRC} ${ui_SRC} ${UI_HEADERS})
target_link_libraries(pw ${Boost_LIBRARIES} Qt5::Widgets Qt5::Core)
target_include_directories(pw PUBLIC ${3PP_INCLUDES})

install_qt5_libs(pw "${CMAKE_BINARY_DIR}/dist/bin")
