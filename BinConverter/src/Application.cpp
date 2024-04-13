#include "Application.hpp"
#include <Logger.h>
#include <glad/glad.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <SDL_opengl.h>

#define NFD_THROWS_EXCEPTIONS
#include <nfd.hpp>

// Displays 
#include "displays/UploadDisplay.hpp"

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
#ifdef NDEBUG
		LOG_INIT(false, true);
#else
		LOG_INIT(true, true);
#endif

		// Init SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::string error = SDL_GetError();
			ERROR("Failed to initialize SDL: " + error);
			return false;
		}

		// Init NFD
		if (NFD_Init() != NFD_OKAY) {
			ERROR("Failed to initialize NFD -- NativeFileDialog!");
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
		m_pWindow = std::make_unique<WINDOWING::Window>(
			"BIN CONVERTER", 
			m_WindowWidth, m_WindowHeight, 
			SDL_WINDOWPOS_CENTERED,	
			SDL_WINDOWPOS_CENTERED,	
			true, SDL_WINDOW_OPENGL
		);

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

		// Initialize ImGui 
		m_pImGuiEx = std::make_unique<ImGuiUtils::ImguiExt>();
		if (!m_pImGuiEx->Initialize(*m_pWindow))
		{
			ERROR("Failed to Initialize ImGui and Extensions!");
			return false;
		}

		if (!InitDisplays())
		{
			ERROR("Failed to initialize Displays!");
			return false;
		}
	}

	bool Application::InitDisplays()
	{
		m_mapDisplays.emplace(DisplayType::UPLOAD, std::make_unique<UploadDisplay>());

		return true;
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
			{
				auto pUploadDisplay = dynamic_cast<UploadDisplay*>(m_mapDisplays[DisplayType::UPLOAD].get());
				pUploadDisplay->SetUploadFile(std::string{ m_Event.drop.file });
				break;
			}
	
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

		m_pImGuiEx->Begin();
		m_pImGuiEx->Render();

		for (const auto& [eType, pDisplay] : m_mapDisplays)
		{
			pDisplay->Draw();
		}

		m_pImGuiEx->End(*m_pWindow);
		
		//ImGui::ShowDemoWindow();

		SDL_GL_SwapWindow(m_pWindow->GetWindow().get());
	}

	void BinConverter::Application::CleanUp()
	{
		NFD_Quit();
		SDL_Quit();
	}
}