#pragma once
#include <SDL.h>
#include <memory>

/*
* SDL_Destroyer -- Custom deleters for SDL C-Style Pointers and types
*/
namespace UTILITIES {
	struct SDL_Destroyer
	{
		void operator()(SDL_Window* window) const;
		void operator()(SDL_Renderer* renderer) const;
		void operator()(SDL_Texture* texture) const;
		void operator()(SDL_GameController* controller) const;
		void operator()(SDL_Cursor* cursor) const;
	};
}

// Aliases 
using Controller	= std::shared_ptr<SDL_GameController>;
using Cursor		= std::shared_ptr<SDL_Cursor>;
using WindowPtr		= std::unique_ptr<SDL_Window, UTILITIES::SDL_Destroyer>;
using RendererPtr	= std::unique_ptr<SDL_Renderer, UTILITIES::SDL_Destroyer>;
using TexturePtr	= std::unique_ptr<SDL_Texture, UTILITIES::SDL_Destroyer>;

static Controller make_shared_controller(SDL_GameController* controller)
{
	return std::shared_ptr<SDL_GameController>(controller, UTILITIES::SDL_Destroyer{});
}

static Cursor make_shared_cursor(SDL_Cursor* cursor)
{
	return std::shared_ptr<SDL_Cursor>(cursor, UTILITIES::SDL_Destroyer{});
}