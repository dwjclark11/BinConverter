add_executable(BinConverter
    "src/Application.cpp"
    "src/Application.hpp"
    "src/main.cpp"

    "src/displays/ChoicesDisplay.hpp"
    "src/displays/ChoicesDisplay.cpp"
	"src/displays/LogDisplay.hpp"
    "src/displays/LogDisplay.cpp"
	"src/displays/UploadDisplay.hpp"
    "src/displays/UploadDisplay.cpp"
	"src/utilities/ImGuiUtils.hpp"
    "src/utilities/ImGuiUtils.cpp"
	"src/utilities/LuaTableWriter.hpp"
    "src/utilities/LuaTableWriter.cpp"
	"src/utilities/TableGenerator.hpp"
    "src/utilities/TableGenerator.cpp")

target_include_directories(
    BinConverter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(BinConverter PRIVATE Logger Utils Window glad nfd imgui)

set_target_properties(BinConverter PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/")