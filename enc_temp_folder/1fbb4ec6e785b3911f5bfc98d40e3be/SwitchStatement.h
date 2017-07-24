#pragma once
#include <vector>
#include <set>
#include <string>
#include "CaseInfo.h"

#ifdef _DEBUG
#include <iostream>
#endif //_DEBUG

class SwitchStatement
{
	std::vector<SwitchStatement> children;
	std::vector<std::string> enumerations;
	std::vector<CaseInfo> cases_info;
	std::string buffer;
	bool is_statemachine = false;
	bool has_children = false;
private:
	inline void appendToCases(const CaseInfo& _case) { cases_info.push_back(_case); }
	void parseBufferForCases();
	void checkStateMachine();
	inline bool doEnumsAndCasesMatch() const { return is_statemachine; }
	inline const bool empty() const { return buffer.empty(); }
	inline void clear() { children.clear(); buffer.clear(); }
	inline const bool hasChildren() const { return has_children; }
public:
	SwitchStatement(const std::string& switchStatement, const std::vector<std::string>& _enumerations);
	~SwitchStatement();

	const CaseInfo * const searchCasesFor(const std::string& _case_label);
	static enum class e_case_search_type { VALUE, POS };
	const CaseInfo * const searchCasesFor(const int& _case_pos, e_case_search_type _search_type);
	void getStateMachines(std::vector<SwitchStatement*>& ptr_state_machine);

	const std::set<std::string> getStateTransitions() const;
	const std::set<std::string> getMatchingEnumsCases() const;
	const bool isPossibleStateMachine() const;
	inline const std::vector<CaseInfo>& getCasesInfo() const { return cases_info; }
	inline const std::vector<SwitchStatement>& getChildren() const { return children; }
	inline const std::string& getBuffer() const { return buffer; }
	inline void appendBuffer(const std::string& _toAppend) { buffer.append(_toAppend); }
	inline void appendBuffer(const char& _toAppend) { buffer += _toAppend; }
	
#ifdef _DEBUG
	void writeDebugOutput(std::ostream& os);
#endif //_DEBUG
};

