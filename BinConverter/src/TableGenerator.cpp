#include "TableGenerator.hpp"
#include <filesystem>
#include <fstream>
#include <Logger.h>
#include <format>

namespace fs = std::filesystem;

namespace BinConverter {

    TableGenerator::TableGenerator(const std::string& sInFile, const std::string& sOutFile)
        : m_sInFile{ sInFile }, m_sOutFile{ sOutFile }
    {

    }

    bool TableGenerator::GenerateArray(const std::string& sArrayName, bool bZeroTerminate, bool bSizeVariable, bool bDecimal, bool bEndVariable)
    {
        fs::path inPath{ m_sInFile };
        if (!fs::exists(inPath))
        {
            ERROR("Failed to Generate Array: [{}] -- Does Not Exist!", m_sInFile);
            return false;
        }

        std::fstream inStream{ m_sInFile, std::ios::in | std::ios::binary };
        if (!inStream.is_open())
        {
            ERROR("Failed to generate array: Failed to open: [{}]", m_sInFile);
            return false;
        }

        std::fstream outStream{ m_sOutFile, std::ios::out | std::ios::trunc };
        
		int byte;
		size_t total{ 0ull };
		size_t rowCount{ 0ull };

		outStream << std::format("// start {}\n", sArrayName);
		outStream << std::format("unsigned char {}[] = ", sArrayName);
		outStream << "{\n";

		while (!inStream.eof())
		{
			byte = inStream.get();

			if (inStream.eof())
				break;

			if (total != 0ull)
			{
				outStream << ", ";
				++rowCount;
			}

			// Keep rows of 30
			if (rowCount >= 30)
			{
				outStream << "\n";
				rowCount = 0;
			}

			outStream << std::format("{:#04x}", byte);
			++total;
		}

		if (bZeroTerminate)
		{
			// If not the first, print a comma
			if (total != 0U) outStream << ", ";
			outStream << bDecimal ? "0" : "0x00";
			++total;
		}

		outStream << "};\n";

		if (total > 0U && bEndVariable)
			outStream << std::format("unsigned char* {}_end = {} + {};\n", sArrayName, sArrayName, total - 1ull);

		if (bSizeVariable)
			outStream << std::format("unsigned int {}_size = {};\n", sArrayName, total);

		outStream << std::format("// end {}\n", sArrayName);

		outStream.close();
		inStream.close();
        return true;
    }

    bool TableGenerator::GenerateLuaTable()
    {
        return false;
    }

}