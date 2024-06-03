#include "UploadDisplay.hpp"
#include <imgui.h>
#include <nfd.hpp>
#include <Logger/Logger.h>

#include "../utilities/TableGenerator.hpp"
#include "../Settings.hpp"

BinConverter::UploadDisplay::UploadDisplay(Settings& settings)
	: m_Settings{settings}
{
}

void BinConverter::UploadDisplay::Draw()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
	if (!ImGui::Begin("Content Display", nullptr, flags))
	{
		ImGui::End();
		return;
	}

	ImGui::Text("In File: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), m_sUploadedFile.c_str());
	ImGui::Text("Out File: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), m_sOutFile.c_str());

	static std::string sUploadButton{"UPLOAD FILE"};

	auto windowSize = ImGui::GetWindowSize();
	auto textSize = ImGui::CalcTextSize(sUploadButton.c_str());

	ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);
	ImGui::SetCursorPosY((windowSize.y - textSize.y) * 0.5f);

	if (ImGui::Button("UPLOAD FILE"))
	{
		NFD::UniquePath outPath;
		auto result = NFD::OpenDialog(outPath);
		if (result == NFD_OKAY)
		{
			m_sUploadedFile = std::string{outPath.get()};
		}
		else if (result == NFD_CANCEL)
		{
			ImGui::End();
			return;
		}
		else
		{
			ERROR("Failed to open dialog: {}", NFD::GetError());
		}
	}
	static std::string sDropFile{"or Drop File"};
	textSize = ImGui::CalcTextSize(sDropFile.c_str());
	ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);
	ImGui::Text(sDropFile.c_str());

	if (m_sUploadedFile.empty())
	{
		ImGui::End();
		return;
	}

	ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);
	if (ImGui::Button("SET OUT FILE"))
	{
		NFD::UniquePath outPath;
		auto result = NFD::SaveDialog(outPath);
		if (result == NFD_OKAY)
		{
			m_sOutFile = std::string{outPath.get()};
		}
		else if (result == NFD_CANCEL)
		{
			ImGui::End();
			return;
		}
		else
		{
			ERROR("Failed to save dialog: {}", NFD::GetError());
		}
	}

	if (!m_sOutFile.empty() && !m_sUploadedFile.empty())
	{
		std::string sGenerateText{"GENERATE TABLE"};
		textSize = ImGui::CalcTextSize(sGenerateText.c_str());
		ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);

		if (ImGui::Button(sGenerateText.c_str()))
		{
			TableGenerator tableGen{m_sUploadedFile, m_sOutFile};

			if (m_Settings.bCreateArray)
			{
				if (!tableGen.GenerateArray(m_Settings.sTableName,
											m_Settings.bZeroTerminated,
											m_Settings.bTableSize,
											false,
											m_Settings.bTableEnd))
				{
					ERROR("Failed to Generate C-Style Array [{}] from [{}] to [{}]!",
						  m_Settings.sTableName,
						  m_sUploadedFile,
						  m_sOutFile);
				}
				else
				{
					LOG("Successfully Generated C-Style Array [{}] from [{}] to [{}]!",
						m_Settings.sTableName,
						m_sUploadedFile,
						m_sOutFile);
				}
			}
			else if (m_Settings.bCreateLuaTable)
			{
				if (!tableGen.GenerateLuaTable(m_Settings.sTableName,
											   m_Settings.bZeroTerminated,
											   m_Settings.bTableSize,
											   false,
											   m_Settings.bTableEnd))
				{
					ERROR("Failed to Generate Lua Table [{}] from [{}] to [{}]!",
						  m_Settings.sTableName,
						  m_sUploadedFile,
						  m_sOutFile);
				}
				else
				{
					LOG("Successfully Generated Lua Table [{}] from [{}] to [{}]!",
						m_Settings.sTableName,
						m_sUploadedFile,
						m_sOutFile);
				}
			}
		}
	}

	ImGui::End();
}

void BinConverter::UploadDisplay::Update()
{
	//
}

void BinConverter::UploadDisplay::SetUploadFile(const std::string& sUploadedFile)
{
	if (sUploadedFile.empty())
		return;

	m_sUploadedFile = sUploadedFile;
	m_bFileUploaded = true;
}
