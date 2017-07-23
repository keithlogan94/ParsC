#pragma once
#include <vector>
#include <string>
#include <fstream>
class SwitchStatement
{
	std::vector<SwitchStatement> children;
	std::string buffer;
public:
	SwitchStatement(const std::string& switchStatement);
	~SwitchStatement();

	inline const std::vector<SwitchStatement>& getChildren() const { return children; }
	inline const std::string& getBuffer() const { return buffer; }
	inline void appendBuffer(const std::string& _toAppend) { buffer.append(_toAppend); }
	inline void appendBuffer(const char& _toAppend) { buffer += _toAppend; }

#ifdef _DEBUG
public:
	void writeDebugOutput(std::ostream& ofs);
#endif //_DEBUG
};

