#pragma once
#include <Window.h>

namespace BinConverter {
	class Application
	{
	public:
		static Application& GetInstance();
		void Run();

	private:
		std::unique_ptr<WINDOWING::Window> m_pWindow{ nullptr };

		SDL_Event m_Event{};
		bool m_bIsRunning{ true };
		int m_WindowWidth{ 1366 }, m_WindowHeight{ 768 };

	private:
		bool Initialize();
		void ProcessEvents();
		void Update();
		void Render();
		void CleanUp();

		Application() = default;
		~Application() = default;
		Application Applicaton(const Application&) = delete;
		Application& operator=(const Application&) = delete;
	};
}