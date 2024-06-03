#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <concepts>

namespace BinConverter
{

template <class T>
concept Writable = requires(std::ostream& os, T obj) { os << obj; };

class LuaWriter
{
  private:
	int m_Indent, m_IndentSize;
	std::fstream m_CurrentFile;

	bool m_bValueWritten, m_bNewLine, m_bDocStarted;

  private:
	void Indent();
	void NewLine();
	void AssembleNewValue();
	void AssembleNewLine();
	std::string Quote(const std::string& str);

	template <Writable T>
	void Write(const T& value);

  public:
	/*
	 * @brief Constructor for the LuaWriter
	 * Opens or creates the filename provided
	 * @param const std::string& filename to be loaded
	 * @param int indentSize desired indent size in spaces
	 * @throws Throws exception if file is not loaded correctly
	 */
	LuaWriter(const std::string& filename, int indentSize = 4);
	~LuaWriter();

	/*
	 * @brief Checks to see if a file is open, if so closes the file and tries to
	 * open the new filestream
	 * @param Takes in a const std::string& for the file to be opened.
	 * @returns Returns true if the file was opened successfully, false otherwise.
	 */
	bool ResetFileStream(const std::string& filename);

	/*
	 * @brief Checks to see if the indent count is zero and the the
	 * document has not already been started. If that is the case, it starts
	 * the document.
	 * @returns Returns true if document started successfully, false otherwise.
	 */
	bool StartDocument();

	/*
	 * @brief Checks to see if the indent count has returned to zero and
	 * the document has been started and then writes a new line at the end of the document.
	 * @returns Returns true if successfully ends the document, false otherwise
	 */
	bool EndDocument();

	LuaWriter& CommentSeparation();
	LuaWriter& Comment(const std::string& comment);

	LuaWriter& StartTable(const std::string name, bool newLine = true, bool sameLine = false);
	LuaWriter& EndTable(bool sameLine = false);

	template <Writable TValue>
	LuaWriter& WriteValue(TValue value, bool indent = false);
	template <Writable TValue>
	LuaWriter& WriteWords(TValue value, bool newLine = false, bool indent = false);
	template <Writable TValue>
	LuaWriter& WriteUnquotedValue(TValue value, bool newLine = false);
	template <Writable TKey, Writable TValue>
	LuaWriter& WriteQuotedKeyAndValue(TKey key, TValue value, bool newLine = true);
	template <Writable TKey, Writable TValue>
	LuaWriter& WriteKeyAndValue(TKey key, TValue value, bool newLine = true);
	template <Writable TKey, Writable TValue>
	LuaWriter& WriteKeyAndQuotedValue(TKey, TValue, bool newLine = true);

	template <Writable TTable>
	LuaWriter& StartBracketedTable(TTable name, bool newLine = true, bool sameLine = false);
};

template <Writable T>
inline void LuaWriter::Write(const T& value)
{
	m_CurrentFile << value;
}

template <Writable TValue>
inline LuaWriter& LuaWriter::WriteValue(TValue value, bool indent)
{
	WriteUnquotedValue(value);

	if (indent)
		++m_Indent;

	return *this;
}

template <Writable TValue>
inline LuaWriter& LuaWriter::WriteWords(TValue value, bool newLine, bool indent)
{
	if (newLine)
		AssembleNewLine();

	if (indent)
	{
		++m_Indent;
		Indent();
		--m_Indent;
	}

	Write(value);
	m_bNewLine = false;
	m_bValueWritten = false;

	return *this;
}

template <Writable TValue>
inline LuaWriter& LuaWriter::WriteUnquotedValue(TValue value, bool newLine)
{
	AssembleNewValue();

	Write(value);
	m_bNewLine = false;
	m_bValueWritten = true;

	return *this;
}

template <Writable TKey, Writable TValue>
inline LuaWriter& LuaWriter::WriteQuotedKeyAndValue(TKey key, TValue value, bool newLine)
{
	newLine ? AssembleNewLine() : AssembleNewValue();
	Write('[');
	Write(Quote(key));
	Write("] = ");
	Write(value);
	m_bNewLine = false;
	m_bValueWritten = true;

	return *this;
}

template <Writable TKey, Writable TValue>
inline LuaWriter& LuaWriter::WriteKeyAndValue(TKey key, TValue value, bool newLine)
{
	newLine ? AssembleNewLine() : AssembleNewValue();
	if (m_bValueWritten)
		Write(' ');

	Write(key);
	Write(" = ");
	Write(value);

	m_bNewLine = false;
	m_bValueWritten = true;

	return *this;
}

template <Writable TKey, Writable TValue>
inline LuaWriter& LuaWriter::WriteKeyAndQuotedValue(TKey key, TValue value, bool newLine)
{
	newLine ? AssembleNewLine() : AssembleNewValue();

	Write(key);
	Write(" = ");
	Write(Quote(value));

	m_bNewLine = false;
	m_bValueWritten = true;

	return *this;
}

template <Writable TTable>
inline LuaWriter& LuaWriter::StartBracketedTable(TTable name, bool newLine, bool sameLine)
{
	newLine ? AssembleNewLine() : AssembleNewValue();

	Write("[");
	Write(name);
	Write("]");
	Write(" = {");
	++m_Indent;
	m_bNewLine = false;
	m_bValueWritten = false;

	return *this;
}
} // namespace BinConverter