add_library(Window
    "include/window/Window.h"
    "src/Window.cpp")

target_include_directories(
    Window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Window PUBLIC Utils)