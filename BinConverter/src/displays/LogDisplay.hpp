#pragma once
#include "IDisplay.hpp"
#include <imgui.h>

namespace BinConverter
{
class LogDisplay : public IDisplay
{
  private:
	ImGuiTextBuffer m_TextBuffer;
	ImVector<int> m_TextOffsets;

	bool m_bAutoScroll;

  private:
	void Clear();
	void GetLogs();

  public:
	LogDisplay();

	void Draw() override;
	void Update() override;
};
} // namespace BinConverter