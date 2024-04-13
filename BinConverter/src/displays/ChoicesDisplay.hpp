#pragma once
#include "IDisplay.hpp"
#include <string>

namespace BinConverter {
	class ChoicesDisplay : public IDisplay
	{
	private:
		bool m_bCreateLuaTable{ false }, m_bCreateArray{ true };
		bool m_bTableSize{ true }, m_bZeroTerminated{ false };
		bool m_bTableEnd{ false };
		
		struct Settings& m_Settings;

	public:
		ChoicesDisplay(struct Settings& settings);
		~ChoicesDisplay() = default;

		void Draw() override;
		void Update() override;

	};
}