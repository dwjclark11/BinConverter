#pragma once
#include "IDisplay.hpp"
#include <string>

namespace BinConverter {
	class UploadDisplay : public IDisplay
	{
	private:
		std::string m_sUploadedFile{ "" }, m_sOutFile{ "" };
		bool m_bFileUploaded{ false };
		struct Settings& m_Settings;

	public:
		UploadDisplay(struct Settings& settings);
		~UploadDisplay() = default;

		void Draw() override;
		void Update() override;
		void SetUploadFile(const std::string& sUploadedFile);
	};
}