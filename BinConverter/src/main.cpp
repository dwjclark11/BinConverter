#define SDL_MAIN_HANDLED 1 
#include "Application.hpp"

int main()
{
	auto& app = BinConverter::Application::GetInstance();
	app.Run();

	return 0;
}