#include "LuaTableWriter.hpp"
#include <Logger/Logger.h>

constexpr char SEPARATOR = ',';

namespace BinConverter
{

void LuaWriter::Indent()
{
	// Create the indent based on the desired size
	std::string indent(m_IndentSize, ' ');
	for (int i = 0; i < m_Indent; i++)
	{
		Write(indent);
	}
}

void LuaWriter::NewLine()
{
	if (m_bNewLine)
		return;

	Write('\n');
	Indent();
}

void LuaWriter::AssembleNewValue()
{
	if (!m_bValueWritten)
		NewLine();
	else
	{
		Write(SEPARATOR);
		Write(' ');
	}
}

void LuaWriter::AssembleNewLine()
{
	if (m_bValueWritten)
	{
		Write(SEPARATOR);
		m_bValueWritten = false;
	}

	NewLine();
}

std::string LuaWriter::Quote(const std::string& str)
{
	return std::string();
}

LuaWriter::LuaWriter(const std::string& filename, int indentSize)
	: m_CurrentFile{}
	, m_Indent{0}
	, m_IndentSize{indentSize}
	, m_bValueWritten{false}
	, m_bNewLine{false}
	, m_bDocStarted{false}
{
	m_CurrentFile.open(filename, std::ios::out | std::ios::trunc);
	ASSERT(m_CurrentFile.is_open() && "File was not opened correctly!");

	// If the file was not opened, throw error
	if (!m_CurrentFile.is_open())
		throw std::runtime_error(std::string("Failed to open: ") + filename);
}

LuaWriter::~LuaWriter()
{
	if (m_CurrentFile.is_open())
		m_CurrentFile.close();
}

bool LuaWriter::ResetFileStream(const std::string& filename)
{
	if (m_CurrentFile.is_open())
	{
		m_CurrentFile.close();
		m_bNewLine = false;
		m_bValueWritten = false;
		m_bDocStarted = false;
	}

	m_CurrentFile.open(filename);

	return m_CurrentFile.is_open();
}

bool LuaWriter::StartDocument()
{
	ASSERT(m_Indent == 0 && "Indent count should be zero when starting a document!");
	ASSERT(!m_bDocStarted && "Document has already been started, did you forget to call EndDocument?");

	if (m_Indent != 0 || m_bDocStarted)
	{
		ERROR("Indent count is not 0 or the document has already been started!");
		return false;
	}

	m_bDocStarted = true;

	return true;
}

bool LuaWriter::EndDocument()
{
	ASSERT(m_Indent == 0);
	m_bValueWritten = false; // Ensure incase we want to start a new document

	// We always want to leave an extra line on the bottom of the file
	Write('\n');
	return true;
}

LuaWriter& LuaWriter::CommentSeparation()
{
	Write("----------------------------------------------------------");
	Write('\n');

	return *this;
}

LuaWriter& LuaWriter::Comment(const std::string& comment)
{
	// Start the comment Lua comment -- or --[[ block comment ]]
	Write("-- " + comment);
	// Write a new line
	Write('\n');

	return *this;
}

LuaWriter& LuaWriter::StartTable(const std::string name, bool newLine, bool sameLine)
{
	newLine ? AssembleNewLine() : AssembleNewValue();

	Write(name);
	Write(" = {");

	++m_Indent;
	m_bNewLine = false;
	m_bValueWritten = false;

	return *this;
}

LuaWriter& LuaWriter::EndTable(bool sameLine)
{
	--m_Indent;

	if (!sameLine)
		AssembleNewLine();

	if (m_bValueWritten && !sameLine)
		NewLine();

	Write('}');
	m_bNewLine = false;
	m_bValueWritten = true;

	return *this;
}
} // namespace BinConverter