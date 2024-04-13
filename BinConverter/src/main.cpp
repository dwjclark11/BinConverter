#define SDL_MAIN_HANDLED 1 
#include "Application.hpp"

#ifdef _WIN32
	#include <Windows.h>
#else
	// TODO: Include OS specific libs
#endif

int main()
{
	// We want to hide the console in release, show otherwise
#ifdef NDEBUG
	#ifdef _WIN32
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	#else
		// TODO: Add other OS Console functions
	#endif
#else
	#ifdef _WIN32
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	#else
		// TODO: Add other OS Console functions
	#endif
#endif

	auto& app = BinConverter::Application::GetInstance();
	app.Run();

	return 0;
}