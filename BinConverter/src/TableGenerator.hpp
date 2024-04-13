#pragma once
#include <string>

namespace BinConverter {
	class TableGenerator
	{
	public:
		TableGenerator(const std::string& sInFile, const std::string& sOutFile);

		bool GenerateArray(const std::string& sArrayName, bool bZeroTerminate = false, bool bSizeVariable = true, 
			bool bDecimal = false, bool bEndVariable = false);

		bool GenerateLuaTable();

	private:
		std::string m_sInFile, m_sOutFile;
		
	};
}