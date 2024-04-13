#include "ChoicesDisplay.hpp"
#include <imgui.h>
#include "../Settings.hpp"
namespace BinConverter {
	ChoicesDisplay::ChoicesDisplay(Settings& settings)
		: m_Settings{settings}
	{

	}

	void ChoicesDisplay::Draw()
	{
		if (!ImGui::Begin("Choices Display"))
		{
			ImGui::End();
			return;
		}
		ImGui::NewLine();
		ImGui::SeparatorText("Table Type");

		if (ImGui::Checkbox("Create Lua Table", &m_Settings.bCreateLuaTable))
		{
			if (m_Settings.bCreateLuaTable) 
				m_Settings.bCreateArray = false;
		}

		if (ImGui::Checkbox("Create C-Style Array", &m_Settings.bCreateArray))
		{
			if (m_Settings.bCreateArray)
				m_Settings.bCreateLuaTable = false;
		}
		ImGui::NewLine();
		ImGui::SeparatorText("Extra Variables");
		ImGui::Checkbox("Table Size", &m_Settings.bTableSize);
		ImGui::Checkbox("Table End", &m_Settings.bTableEnd);
		ImGui::NewLine();
		ImGui::SeparatorText("Table Settings");
		ImGui::Checkbox("Zero Terminated", &m_Settings.bZeroTerminated);

		ImGui::NewLine();
		char tableNamebuf[256];
		memset(tableNamebuf, 0, sizeof(tableNamebuf));
		strcpy_s(tableNamebuf, m_Settings.sTableName.c_str());
		ImGui::Text("Table Name");
		ImGui::SameLine();
		ImGui::SetCursorPosX(75.f);
		if (ImGui::InputText("##Table Name", tableNamebuf, sizeof(tableNamebuf)))
		{
			m_Settings.sTableName = std::string{ tableNamebuf };
		}

		ImGui::End();
	}

	void ChoicesDisplay::Update()
	{
		// Nothing to do here
	}
}