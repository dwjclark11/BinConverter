#pragma once
#include "IDisplay.hpp"
#include <string>

namespace BinConverter
{
class ChoicesDisplay : public IDisplay
{
  private:
	struct Settings& m_Settings;

  public:
	ChoicesDisplay(struct Settings& settings);
	~ChoicesDisplay() = default;

	void Draw() override;
	void Update() override;
};
} // namespace BinConverter