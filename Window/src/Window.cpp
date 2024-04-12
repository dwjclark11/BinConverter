#include "Window.h"
#include <Logger.h>

namespace WINDOWING {
	void Window::CreateNewWindow(int xPos, int yPos, Uint32 flags)
	{
		m_pWindow = WindowPtr(SDL_CreateWindow(
			m_sTitle.c_str(),
			xPos,
			yPos,
			m_Width,
			m_Height,
			flags
		));

		if (!m_pWindow)
		{
			std::string error = SDL_GetError();
			ERROR("Failed to create Window: " + error);
			return;
		}
	}

	Window::Window(const std::string& title, int width, int height, int xPos, int yPos, bool v_sync, Uint32 flags)
		: m_pWindow{ nullptr }, m_GLContext{}, m_sTitle{ title }
		, m_Width{ width }, m_Height{ height }, m_CurrentWidth{ width }, m_CurrentHeight{ height }
		, m_WindowFlags{ flags }
	{
		CreateNewWindow(xPos, yPos, flags);

		// Enable VSync
		if (v_sync)
		{
			if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"))
				ERROR("Failed to enable VSYNC");
		}
	}

	Window::~Window()
	{

	}

	void Window::SetWindowName(const std::string& window_name)
	{
		SDL_SetWindowTitle(m_pWindow.get(), window_name.c_str());
	}
}