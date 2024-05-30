add_subdirectory(glad)
add_subdirectory(nfd)
add_subdirectory(imgui)

set_target_properties(glad nfd imgui PROPERTIES FOLDER "Dependencies")