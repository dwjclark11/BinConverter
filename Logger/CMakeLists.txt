add_library(Logger
    "include/Logger/Logger.h"
    "include/Logger/Logger.inl"
    "src/Logger.cpp")

target_include_directories(
    Logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)