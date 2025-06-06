#pragma once
#include <string>

namespace BinConverter
{
struct Settings;

class TableGenerator
{
  public:
	TableGenerator(const std::string& sInFile, const std::string& sOutFile);

	bool GenerateArray(const Settings& settings);
	bool GenerateLuaTable(const Settings& settings);

  private:
	std::string m_sInFile, m_sOutFile;
};
} // namespace BinConverter