#include "ChoicesDisplay.hpp"
#include "../Settings.hpp"

#include <imgui.h>
#include <algorithm>
#include <format>

constexpr const char* letters = "!\n\t\r\?@#$%&\'\"[]{}+-|~`\\/ ";

namespace BinConverter
{
ChoicesDisplay::ChoicesDisplay(Settings& settings)
	: m_Settings{settings}
{
}

void ChoicesDisplay::Draw()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
	if (!ImGui::Begin("Choices Display", nullptr, flags))
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
	char tableNamebuf[ 256 ];
	memset(tableNamebuf, 0, sizeof(tableNamebuf));

#ifdef _WIN32
	strcpy_s(tableNamebuf, m_Settings.sTableName.c_str());
#else
	strcpy(tableNamebuf, m_Settings.sTableName.c_str());
#endif

	ImGui::Text("Table Name");
	ImGui::SameLine();
	ImGui::SetCursorPosX(75.f);
	if (ImGui::InputText("##Table Name", tableNamebuf, sizeof(tableNamebuf)))
	{
		m_Settings.sTableName = std::string{tableNamebuf};
		std::replace_if(
			m_Settings.sTableName.begin(),
			m_Settings.sTableName.end(),
			[](const char c) { return std::string{letters}.find(c) != std::string::npos; },
			'_');
	}

	if (!m_Settings.sTableName.empty() && std::isdigit(m_Settings.sTableName[ 0 ]))
	{
		ImGui::TextColored(
			ImVec4{1.f, 0, 0, 1.f},
			std::format("Table Name [{}] is invalid.\nCannot start with a number!", m_Settings.sTableName).c_str());
	}

	ImGui::End();
}

void ChoicesDisplay::Update()
{
	// Nothing to do here
}
} // namespace BinConverter