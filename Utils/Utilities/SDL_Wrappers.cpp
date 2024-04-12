#include "SDL_Wrappers.h"
#include <Logger.h>

namespace UTILITIES {
	void SDL_Destroyer::operator()(SDL_Window* window) const
	{
		SDL_DestroyWindow(window);
		LOG("Destroyed SDL_Window!");
	}

	void SDL_Destroyer::operator()(SDL_Renderer* renderer) const
	{
		SDL_DestroyRenderer(renderer);
		LOG("Destroyed SDL_Renderer!");
	}

	void SDL_Destroyer::operator()(SDL_Texture* texture) const
	{
		SDL_DestroyTexture(texture);
		LOG("Destroyed SDL_Texture!");
	}

	void SDL_Destroyer::operator()(SDL_GameController* controller) const
	{
		SDL_GameControllerClose(controller);
		controller = nullptr;
		LOG("Closed SDL Game Controller!");
	}

	void SDL_Destroyer::operator()(SDL_Cursor* cursor) const
	{
		SDL_FreeCursor(cursor);
		LOG("Freed SDL Cursor");
	}
}