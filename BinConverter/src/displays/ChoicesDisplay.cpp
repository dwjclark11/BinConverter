#include "ChoicesDisplay.hpp"
#include <imgui.h>

namespace BinConverter {
	void ChoicesDisplay::Draw()
	{
		if (!ImGui::Begin("Choices Display"))
		{
			ImGui::End();
			return;
		}

		ImGui::SeparatorText("Table Type");

		ImGui::Checkbox("Create Lua Table", &m_bCreateLuaTable);
		ImGui::Checkbox("Create C-Style Array", &m_bCreateArray);
		
		ImGui::SeparatorText("Extra Variables");
		ImGui::Checkbox("Table Size", &m_bTableSize);
		ImGui::Checkbox("Table End", &m_bTableEnd);

		ImGui::SeparatorText("Table Settings");
		ImGui::Checkbox("Zero Terminated", &m_bZeroTerminated);


		ImGui::End();
	}
	void ChoicesDisplay::Update()
	{

	}
}