#pragma once
#include "IDisplay.hpp"
#include <string>

namespace BinConverter {
	class UploadDisplay : public IDisplay
	{
	private:
		std::string m_sUploadedFile{""};
		bool m_bFileUploaded{ false };
	public:
		UploadDisplay() = default;
		~UploadDisplay() = default;

		void Draw() override;
		void SetUploadFile(const std::string& sUploadedFile);
	};
}