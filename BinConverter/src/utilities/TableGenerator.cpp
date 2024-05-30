#include "TableGenerator.hpp"
#include <filesystem>
#include <fstream>
#include <Logger/Logger.h>
#include <format>
#include "LuaTableWriter.hpp"

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

		if (sArrayName.empty())
		{
			ERROR("Failed to generate array: Array Name is empty");
			return false;
		}

		if (std::isdigit(sArrayName[0]))
		{
			ERROR("Failed to generate array: Array name cannot start with a number!");
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

	bool TableGenerator::GenerateLuaTable(const std::string& sTableName, bool bZeroTerminate, bool bSizeVariable, bool bDecimal, bool bEndVariable)
	{
		fs::path inPath{ m_sInFile };
		if (!fs::exists(inPath))
		{
			ERROR("Failed to Generate Lua Table: [{}] -- File Does Not Exist!", m_sInFile);
			return false;
		}

		if (sTableName.empty())
		{
			ERROR("Failed to generate Lua Table: Table Name is empty");
			return false;
		}

		if (std::isdigit(sTableName[0]))
		{
			ERROR("Failed to generate Lua Table: Table name cannot start with a number!");
			return false;
		}


		std::fstream inStream{ m_sInFile, std::ios::in | std::ios::binary };
		if (!inStream.is_open())
		{
			ERROR("Failed to generate Lua Table: Failed to open: [{}]", m_sInFile);
			return false;
		}

		
		int byte;
		unsigned int i = 0U;
		unsigned int count = 0U;

		try
		{
			LuaWriter luaWriter{ m_sOutFile };
			if (!luaWriter.StartDocument())
			{
				inStream.close();
				ERROR("Failed to start Lua Document!");
				return false;
			}

			luaWriter.CommentSeparation()
				.Comment(std::format("Start table {}", sTableName))
				.CommentSeparation();

			luaWriter.StartTable(sTableName)
				.WriteKeyAndQuotedValue("asset_name", inPath.stem().string())
				.WriteKeyAndQuotedValue("asset_extension", inPath.extension().string())
				.StartTable("data");

			while (!inStream.eof())
			{
				byte = inStream.get();

				if (inStream.eof())
					break;

				// Keep rows of 20
				if (count >= 20)
				{
					luaWriter.WriteWords(",");
					count = 0;
				}

				luaWriter.WriteValue(std::format("{:#04x}", byte));
				++count;
				++i;
			}

			luaWriter.EndTable();
			if (bEndVariable)
				luaWriter.WriteKeyAndValue("data_end", i - 1ull);
			if (bSizeVariable)
				luaWriter.WriteKeyAndValue("data_size", i);

			luaWriter.EndTable();

			if (!luaWriter.EndDocument())
			{
				ERROR("Failed to successfully End Lua document");
			}
		}
		catch (const std::exception& ex)
		{
			inStream.close();
			ERROR("Failed to write [{}] at path [{}] to asset file!", inPath.stem().string(), m_sInFile);
			return false;
		}

		inStream.close();

		return true;
	}
}