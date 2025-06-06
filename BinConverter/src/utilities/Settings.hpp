#pragma once
#include <string>
namespace BinConverter
{
struct Settings
{
	std::string sTableName{ "table" };
	bool bZeroTerminated{ false };
	bool bCreateLuaTable{ false };
	bool bCreateArray{ true };
	bool bTableSize{ true };
	bool bTableEnd{ false };
	bool bTightlyPack{ false };
	bool bDecimal{false};
	int numEntriesPerRow{ 20 };
};
} // namespace BinConverter
