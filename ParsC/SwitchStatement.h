#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "CaseInfo.h"

class SwitchStatement
{
	std::vector<SwitchStatement> children;
	std::string buffer;
	std::vector<CaseInfo> cases_info;
	bool is_statemachine = false;
private:
	inline void appendToCases(const CaseInfo& _case) { cases_info.push_back(_case); }
	void parseBufferForCases();
	void checkStateMachine();
public:
	SwitchStatement(const std::string& switchStatement);
	~SwitchStatement();

	const CaseInfo * const searchCasesFor(const std::string& _case_label);
	static enum class e_case_search_type { VALUE, POS };
	const CaseInfo * const searchCasesFor(const int& _case_pos, e_case_search_type _search_type);

	inline bool isStateMachine() const { return is_statemachine; }
	inline const std::vector<CaseInfo>& getCasesInfo() const { return cases_info; }
	inline void clear() { children.clear(); buffer.clear(); }
	inline const bool empty() const { return buffer.empty(); }
	inline const bool hasChildren() const { return !children.empty(); }
	inline const std::vector<SwitchStatement>& getChildren() const { return children; }
	inline const std::string& getBuffer() const { return buffer; }
	inline void appendBuffer(const std::string& _toAppend) { buffer.append(_toAppend); }
	inline void appendBuffer(const char& _toAppend) { buffer += _toAppend; }

#ifdef _DEBUG
public:
	void writeDebugOutput(std::ostream& ofs);
#endif //_DEBUG
};

