#include "UploadDisplay.hpp"
#include <imgui.h>
#include <string>

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
		// TODO: 
	}

	ImGui::End();
}
