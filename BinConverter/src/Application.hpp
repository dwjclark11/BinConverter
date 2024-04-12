#pragma once
#include <Window.h>
#include "ImGuiUtils.hpp"
#include "displays/IDisplay.hpp"
#include <map>

namespace BinConverter {

	enum class DisplayType
	{
		UPLOAD, // TODO: Add more display types
	};

	class Application
	{
	public:
		static Application& GetInstance();
		void Run();

	private:
		std::unique_ptr<WINDOWING::Window> m_pWindow{ nullptr };
		std::unique_ptr<ImGuiUtils::ImguiExt> m_pImGuiEx{ nullptr };
		std::map<DisplayType, std::unique_ptr<IDisplay>> m_mapDisplays;

		SDL_Event m_Event{};
		bool m_bIsRunning{ true };
		int m_WindowWidth{ 1366 }, m_WindowHeight{ 768 };

	private:
		bool Initialize();
		bool InitDisplays();
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