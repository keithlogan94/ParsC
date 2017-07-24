#include "SwitchStatement.h"

#include "SwitchStatements.h"
#include <cctype>


struct CaseInfo;

void SwitchStatement::parseBufferForCases()
{
	using namespace std;
	bool _in_string = false;
	for (string::const_iterator it = buffer.begin(); it != buffer.end(); ++it)
	{
		if (*it == '"')
		{
			_in_string = !_in_string;
		}
		if (!_in_string && buffer.end() - it >= 4)
		{
			if (*it == 'c' &&
				*(it + 1) == 'a' &&
				*(it + 2) == 's' &&
				*(it + 3) == 'e' &&
				isspace(*(it + 4)))
			{
				it += 4;
				do
				{
					if (it + 1 == buffer.end())
						break;
					it++;
				} while (isspace(*it));
				string label;
				while (!isspace(*it))
				{
					label.push_back(*it);
					if (it + 1 == buffer.end())
						break;
					it++;
				}
				if (*(label.end() - 1) == ':')
					label.erase(label.end() - 1);
				CaseInfo ci;
				ci.setLabel(label);
				cases_info.push_back(ci);
			}
		}
	}
}


void SwitchStatement::checkStateMachine()
{
	for (auto _enum : enumerations)
	{
		for (auto _case : cases_info)
		{
			if (_enum == _case.getLabel())
			{
				is_statemachine = true;
			}
		}
	}
}

SwitchStatement::SwitchStatement(const std::string & switchStatement, const std::vector<std::string>& _enumerations)
{
	buffer = switchStatement;
	enumerations = _enumerations;
	parseBufferForCases();
	checkStateMachine();
	auto vec_children = SwitchStatementList::extractSwitchStatements(
		switchStatement.substr(switchStatement.find_first_of('{'))
	);
	for (auto child : vec_children)
	{
		children.push_back(SwitchStatement(child, enumerations));
		has_children = true;
	}
}

SwitchStatement::~SwitchStatement()
{
}

const CaseInfo * const SwitchStatement::searchCasesFor(const std::string & _case_label)
{
	for (CaseInfo &_case : cases_info)
	{
		CaseInfo * ptr_case = &_case;
		if (ptr_case->getLabel() == _case_label)
			return ptr_case;
	}
	return nullptr;
}

const CaseInfo * const SwitchStatement::searchCasesFor(const int & _case_value, e_case_search_type _search_type)
{
	if (_search_type == e_case_search_type::POS)
	{
		for (CaseInfo &_case : cases_info)
		{
			CaseInfo * ptr_case = &_case;
			if (ptr_case->getPos() == _case_value)
				return ptr_case;
		}
		return nullptr;
	}
	else
	{
		for (CaseInfo &_case : cases_info)
		{
			CaseInfo * ptr_case = &_case;
			if (ptr_case->getValue() == _case_value)
				return ptr_case;
		}
		return nullptr;
	}
}

const std::vector<std::string> SwitchStatement::getStateTransitions() const
{
	using namespace std;
	vector<string> state_transitions;
	for (auto child : children)
	{
		vector <string> _matching_enumscases
			= child.getMatchingEnumsCases();
		state_transitions.insert(
			state_transitions.end(),
			_matching_enumscases.begin(),
			_matching_enumscases.end()
		);
	}
	for (auto child : children)
	{
		auto transitions =
			child.getStateTransitions();
		state_transitions.insert(
			state_transitions.end(),
			transitions.begin(),
			transitions.end()
		);
	}
	return state_transitions;
}

const std::vector<std::string> SwitchStatement::getMatchingEnumsCases() const
{
	using namespace std;
	vector<string> matching_enumscases;
	for (auto _enum : enumerations)
	{
		for (auto _case : cases_info)
		{
			if (_enum == _case.getLabel())
			{
				matching_enumscases.push_back(_enum);
			}
		}
	}
	for (auto child : children)
	{
		auto _matching_enumscases 
			= child.getMatchingEnumsCases();
		matching_enumscases.insert(
			matching_enumscases.end(),
			_matching_enumscases.begin(),
			_matching_enumscases.end()
		);
	}
	return matching_enumscases;
}

const bool SwitchStatement::isPossibleStateMachine() const
{
	return !empty() && doEnumsAndCasesMatch();
}

#ifdef _DEBUG

void SwitchStatement::writeDebugOutput(std::ostream & os)
{
	using namespace std;
	os << buffer << endl << endl;
	os << "cases: " << endl;
	for (auto _enum : enumerations)
	{
		os << _enum << endl;
	}
	for (auto _case : cases_info)
	{
		os << _case.getLabel() << endl;
	}
	for (auto child : children)
	{
		child.writeDebugOutput(os);
	}
}

#endif //_DEBUG