add_library(Utils
    "include/Utilities/SDL_Wrappers.h"
    "src/SDL_Wrappers.cpp")
	
target_include_directories(
    Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Utils PUBLIC Logger SDL2::SDL2)