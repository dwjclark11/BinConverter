#pragma once
#include <Utilities/SDL_Wrappers.h>
#include <string>

namespace WINDOWING
{
class Window
{
  private:
	WindowPtr m_pWindow;
	SDL_GLContext m_GLContext;
	std::string m_sTitle;
	int m_Width, m_Height, m_CurrentWidth, m_CurrentHeight;
	Uint32 m_WindowFlags;
	void CreateNewWindow(int xPos, int yPos, Uint32 flags);

  public:
	Window(const std::string& title, int width, int height, int xPos = SDL_WINDOWPOS_CENTERED,
		   int yPos = SDL_WINDOWPOS_CENTERED, bool v_sync = true,
		   Uint32 flags = (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_MAXIMIZED));
	~Window();

	void SetGLContext(SDL_GLContext gl_context) { m_GLContext = gl_context; }
	inline WindowPtr& GetWindow() { return m_pWindow; }
	inline SDL_GLContext& GetGLContext() { return m_GLContext; }
	inline const std::string& GetWindowName() const { return m_sTitle; }
	void SetWindowName(const std::string& window_name);
};
} // namespace WINDOWING