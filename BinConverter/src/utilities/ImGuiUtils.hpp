#pragma once
#include <string>

namespace WINDOWING { class Window; }

namespace ImGuiUtils {

	class ImguiExt {
	public:
		bool Initialize(WINDOWING::Window& window);
		void Begin();
		void End(WINDOWING::Window& window);
		void Render();
		void DropFile(const std::string& sDroppedFile);

	private:
		void MainMenu();
		void SetStyle();
		
	};
	
}