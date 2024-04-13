#pragma once
#include <string>
namespace BinConverter {
	struct Settings
	{
		std::string sTableName{ "table" };
		bool bZeroTerminated{ false }, bCreateLuaTable{ false }, bCreateArray{ true };
		bool bTableSize{ true }, bTableEnd{ false };
	};
}