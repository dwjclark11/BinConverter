#include "UploadDisplay.hpp"
#include <imgui.h>
#include <string>

#include <nfd.hpp>
#include <Logger.h>

void BinConverter::UploadDisplay::Draw()
{
	if (!ImGui::Begin("Content Display"))
	{
		ImGui::End();
		return;
	}

	static std::string sUploadButton{ "UPLOAD FILE" };
	
	auto windowSize = ImGui::GetWindowSize();
	auto textSize = ImGui::CalcTextSize(sUploadButton.c_str());

	ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);
	ImGui::SetCursorPosY((windowSize.y - textSize.y) * 0.5f);

	if (ImGui::Button("UPLOAD FILE"))
	{
		NFD::UniquePath outPath;
		auto result = NFD::PickFolder(outPath);
		if (result == NFD_OKAY)
		{
			LOG("Success: {}", outPath.get());
		}
		else if (result == NFD_CANCEL)
		{
			LOG("User Cancelled!");
		}
		else
		{
			ERROR("Failed to open dialog: {}", NFD::GetError());
		}
	}

	ImGui::End();
}

void BinConverter::UploadDisplay::SetUploadFile(const std::string& sUploadedFile)
{
	if (sUploadedFile.empty())
		return;

	m_sUploadedFile = sUploadedFile; 
	m_bFileUploaded = true;
}
