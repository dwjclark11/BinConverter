#include "LogDisplay.hpp"
#include <ranges>
#include <Logger/Logger.h>

namespace BinConverter {

	LogDisplay::LogDisplay()
		: m_bAutoScroll{ true }
	{

	}

	void LogDisplay::Clear()
	{
		m_TextBuffer.clear();
		m_TextOffsets.clear();
	}

	void LogDisplay::GetLogs()
	{
		if (LOGGER::Logger::GetInstance().LogAdded())
		{
			Clear();

			std::ranges::reverse_view reversedLogs{ LOGGER::Logger::GetInstance().GetLogEntries() };

			for (auto& log : reversedLogs)
			{
				int oldTexSize = m_TextBuffer.size();
				m_TextBuffer.append(log.message.c_str());
				m_TextOffsets.push_back(oldTexSize + 1);
			}

			LOGGER::Logger::GetInstance().ResetLogAddition();
		}
	}

	void LogDisplay::Draw()
	{
		if (!ImGui::Begin("Log"))
		{
			ImGui::End();
			return;
		}

		ImGui::SameLine();

		if (ImGui::Button("Clear"))
		{
			Clear();
			LOG_CLEAR();
		}

		ImGui::SameLine();
		if (ImGui::Button("Copy"))
		{
			ImGui::LogToClipboard();
		}

		ImGui::SameLine();
		
		ImGui::Separator();
		ImGui::BeginChild("scrolling", ImVec2{ 0, 0 }, false, ImGuiWindowFlags_HorizontalScrollbar);
		
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
		ImGuiListClipper clipper;
		clipper.Begin(m_TextOffsets.Size);
		while (clipper.Step())
		{
			for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
			{
				const char* line_start = m_TextBuffer.begin() + m_TextOffsets[line_no] - 1;
				const char* line_end = 
					(line_no + 1 < m_TextOffsets.Size) ?
					(m_TextBuffer.begin() + m_TextOffsets[line_no + 1] - 1) : m_TextBuffer.end();

				std::string text{ line_start, line_end };
				ImVec4 color;
				
				if (text.find("INFO") != std::string::npos)
					color = ImVec4{ 0.f, 1.f, 0.f, 1.f };
				else if (text.find("ERROR") != std::string::npos)
					color = ImVec4{ 1.f, 0.f, 0.f, 1.f };
				else if (text.find("WARN") != std::string::npos)
					color = ImVec4{ 1.f, 1.f, 0.f, 1.f };
				else
					color = ImVec4{ 1.f, 1.f, 1.f, 1.f };

				ImGui::PushStyleColor(ImGuiCol_Text, color);
				ImGui::TextUnformatted(line_start, line_end);
				ImGui::PopStyleColor();
			}
		}
		clipper.End();

		ImGui::PopStyleVar();

		if (m_bAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);

		ImGui::EndChild();
		ImGui::End();
	}

	void LogDisplay::Update()
	{
		GetLogs();
	}

}