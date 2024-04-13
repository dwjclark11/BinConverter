#pragma once
#include <Window.h>
#include "utilities/ImGuiUtils.hpp"
#include "displays/IDisplay.hpp"
#include <map>

namespace BinConverter {

	enum class DisplayType
	{
		UPLOAD, 
		CHOICES,
		LOGS,
		// TODO: Add more display types
	};

	class Application
	{
	public:
		static Application& GetInstance();
		void Run();

	private:
		std::unique_ptr<WINDOWING::Window> m_pWindow{ nullptr };
		std::unique_ptr<ImGuiUtils::ImguiExt> m_pImGuiEx{ nullptr };
		std::unique_ptr<struct Settings> m_pSettings{ nullptr };

		std::map<DisplayType, std::unique_ptr<IDisplay>> m_mapDisplays;

		SDL_Event m_Event{};
		bool m_bIsRunning{ true };
		int m_WindowWidth{ 768 }, m_WindowHeight{ 480 };

	private:
		bool Initialize();
		bool InitDisplays(struct Settings& settings);
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