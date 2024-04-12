#include "Application.hpp"

#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <SDL_opengl.h>
#include <Logger.h>

namespace BinConverter {

	Application& Application::GetInstance()
	{
		static Application instance{};
		return instance;
	}

	void BinConverter::Application::Run()
	{
		if (!Initialize())
			m_bIsRunning = false;

		while (m_bIsRunning)
		{
			ProcessEvents();
			Update();
			Render();
		}

		CleanUp();
	}

	bool BinConverter::Application::Initialize()
	{
		// Init SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::string error = SDL_GetError();
			ERROR("Failed to initialize SDL: " + error);
			return false;
		}

		// Load the GL library
		if (SDL_GL_LoadLibrary(NULL) != 0)
		{
			std::string error = SDL_GetError();
			ERROR("Failed to OpenGL library: " + error);
			return false;
		}

		// Set the OpenGL attributes
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		// Create the Window
		m_pWindow = std::make_unique<WINDOWING::Window>("SCION-2D Editor", m_WindowWidth, m_WindowHeight);

		// Create the OpenGL Context
		m_pWindow->SetGLContext(SDL_GL_CreateContext(m_pWindow->GetWindow().get()));

		if (!m_pWindow->GetGLContext())
		{
			std::string error = SDL_GetError();
			ERROR("Failed to initialize OpenGL Context: " + error);
			return false;
		}

		SDL_GL_MakeCurrent(m_pWindow->GetWindow().get(), m_pWindow->GetGLContext());
		SDL_GL_SetSwapInterval(1); // Enable vsync

		// Initialize Glad
		if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0)
		{
			ERROR("Failed to LoadGL --> GLAD");
			return false;
		}

		// Initialize Imgui
		const char* glsl_version = "#version 450";
		IMGUI_CHECKVERSION();

		if (!ImGui::CreateContext())
		{
			ERROR("Failed to create imgui context!");
			return false;
		}

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		

		// Config fonts
		// auto fontAtlas = io.Fonts;
		//ImFontConfig config;
		//config.GlyphRanges = fontAtlas->GetGlyphRangesDefault();
		//io.Fonts->AddFontFromFileTTF("./assets/fonts/segoeui.ttf", 18.f, &config, config.GlyphRanges);

		//config.MergeMode = true;
		////config.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
		//static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		//auto font = io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAS, 16.0f, &config, icon_ranges);
		//font->FallbackChar = '#';

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		// Only want the windows to be moved by the titlebar
		io.ConfigWindowsMoveFromTitleBarOnly = true;

		// Setup Platform/Renderer backends
		if (!ImGui_ImplSDL2_InitForOpenGL(
			m_pWindow->GetWindow().get(),
			m_pWindow->GetGLContext()
		))
		{
			ERROR("Failed to initialize ImGui_SDL2_For_OpenGL!");
			return false;
		}

		if (!ImGui_ImplOpenGL3_Init(glsl_version))
		{
			ERROR("Failed to initialize ImGui_OpenGL3!");
			return false;
		}

	}

	void BinConverter::Application::ProcessEvents()
	{
		while (SDL_PollEvent(&m_Event))
		{
			ImGui_ImplSDL2_ProcessEvent(&m_Event);
			// Handle Core SDL Events
			switch (m_Event.type)
			{
			case SDL_QUIT:
				m_bIsRunning = false;
				break;
			case SDL_KEYDOWN:

				break;
			case SDL_KEYUP:

				break;
			case SDL_MOUSEBUTTONDOWN:

				break;
			case SDL_MOUSEBUTTONUP:
	
				break;
			case SDL_MOUSEWHEEL:

				break;
			case SDL_MOUSEMOTION:

				break;
			case SDL_DROPFILE:
				
				break;
	
			default:
				break;
			}
		}
	}

	void BinConverter::Application::Update()
	{

	}

	void BinConverter::Application::Render()
	{
		glViewport(0, 0, 1366, 768);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ==============================================================================
		// Start the Dear ImGui frame
		// ==============================================================================
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		// ==============================================================================

		ImGui::ShowDemoWindow();

		// ==============================================================================
		// END IMGUI
		// ==============================================================================
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(
				m_pWindow->GetWindow().get(),
				backup_current_context);
		}
		// ==============================================================================
		SDL_GL_SwapWindow(m_pWindow->GetWindow().get());
	}

	void BinConverter::Application::CleanUp()
	{
		
	}
}