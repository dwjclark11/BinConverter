#include "TableGenerator.hpp"
#include <filesystem>
#include <fstream>
#include <Logger/Logger.h>
#include <format>
#include "LuaTableWriter.hpp"
#include "Settings.hpp"

namespace fs = std::filesystem;

namespace BinConverter
{

TableGenerator::TableGenerator(const std::string& sInFile, const std::string& sOutFile)
	: m_sInFile{sInFile}
	, m_sOutFile{sOutFile}
{
}

bool TableGenerator::GenerateArray(const Settings& settings)
{
	fs::path inPath{m_sInFile};
	if (!fs::exists(inPath))
	{
		ERROR("Failed to Generate Array: [{}] -- Does Not Exist!", m_sInFile);
		return false;
	}

	if (settings.sTableName.empty())
	{
		ERROR("Failed to generate array: Array Name is empty");
		return false;
	}

	if (std::isdigit(settings.sTableName[ 0 ]))
	{
		ERROR("Failed to generate array: Array name cannot start with a number!");
		return false;
	}

	std::fstream inStream{m_sInFile, std::ios::in | std::ios::binary};
	if (!inStream.is_open())
	{
		ERROR("Failed to generate array: Failed to open: [{}]", m_sInFile);
		return false;
	}

	std::fstream outStream{m_sOutFile, std::ios::out | std::ios::trunc};

	int byte;
	size_t total{0ull};
	size_t rowCount{0ull};

	outStream << std::format("// start {}\n", settings.sTableName);
	outStream << std::format("unsigned char {}[] = ", settings.sTableName);
	outStream << "{\n";

	while (!inStream.eof())
	{
		byte = inStream.get();

		if (inStream.eof())
			break;

		if (total != 0ull)
		{
			outStream << (settings.bTightlyPack ? "," : ", ");
			++rowCount;
		}

		if (rowCount >= settings.numEntriesPerRow)
		{
			outStream << "\n";
			rowCount = 0;
		}

		outStream << std::format("{:#04x}", byte);
		++total;
	}

	if (settings.bZeroTerminated)
	{
		// If not the first, print a comma
		if (total != 0U)
			outStream << ", ";
		outStream << settings.bDecimal ? "0" : "0x00";
		++total;
	}

	outStream << "};\n";

	if (total > 0U && settings.bTableEnd)
		outStream << std::format(
			"unsigned char* {}_end = {} + {};\n", settings.sTableName, settings.sTableName, total - 1ull);

	if (settings.bTableSize)
		outStream << std::format("unsigned int {}_size = {};\n", settings.sTableName, total);

	outStream << std::format("// end {}\n", settings.sTableName);

	outStream.close();
	inStream.close();

	return true;
}

bool TableGenerator::GenerateLuaTable(const Settings& settings)
{
	fs::path inPath{m_sInFile};
	if (!fs::exists(inPath))
	{
		ERROR("Failed to Generate Lua Table: [{}] -- File Does Not Exist!", m_sInFile);
		return false;
	}

	if (settings.sTableName.empty())
	{
		ERROR("Failed to generate Lua Table: Table Name is empty");
		return false;
	}

	if (std::isdigit(settings.sTableName[ 0 ]))
	{
		ERROR("Failed to generate Lua Table: Table name cannot start with a number!");
		return false;
	}

	std::fstream inStream{m_sInFile, std::ios::in | std::ios::binary};
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
		LuaWriter luaWriter{m_sOutFile};
		if (!luaWriter.StartDocument())
		{
			inStream.close();
			ERROR("Failed to start Lua Document!");
			return false;
		}

		luaWriter.CommentSeparation().Comment(std::format("Start table {}", settings.sTableName)).CommentSeparation();

		luaWriter.StartTable(settings.sTableName)
			.WriteKeyAndQuotedValue("asset_name", inPath.stem().string())
			.WriteKeyAndQuotedValue("asset_extension", inPath.extension().string())
			.StartTable("data");

		while (!inStream.eof())
		{
			byte = inStream.get();

			if (inStream.eof())
				break;

			if (count >= settings.numEntriesPerRow)
			{
				settings.bTightlyPack ? luaWriter.WriteWords(",") : luaWriter.WriteWords(", ");
				count = 0;
			}

			luaWriter.WriteValue(std::format("{:#04x}", byte));
			++count;
			++i;
		}

		luaWriter.EndTable();
		if (settings.bTableEnd)
			luaWriter.WriteKeyAndValue("data_end", i - 1ull);
		if (settings.bTableSize)
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
} // namespace BinConverter