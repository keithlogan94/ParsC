#include "SwitchStatement.h"

#include "SwitchStatements.h"
#include <cctype>
#include <set>


struct CaseInfo;

void SwitchStatement::parseBufferForCases()
{
	using namespace std;
	bool _in_string = false;
	for (string::const_iterator it = buffer.begin() + 1; it != buffer.end(); ++it)
	{
		if (*it == '"')
		{
			_in_string = !_in_string;
		}
		if (!_in_string && buffer.end() - it >= 5)
		{
			if (*it == 's' &&
				*(it + 1) == 'w' &&
				*(it + 2) == 'i' &&
				*(it + 3) == 't' &&
				*(it + 4) == 'c' &&
				*(it + 5) == 'h')
			{
				it += 5;
				int bracket_counter = 0;
				while (true)
				{
					it++;
					if (buffer.end() - it >= 1)
					{
						if (*it == '{' && *(it - 1) != '\'' && *(it + 1) != '\'')
						{
							bracket_counter++;
						}
						if (*it == '}' && *(it - 1) != '\'' && *(it + 1) != '\'')
						{
							bracket_counter--;
						}
					}
					else
					{
						if (*it == '{')
						{
							bracket_counter++;
						}
						if (*it == '}')
						{
							bracket_counter--;
						}
					}
					if (bracket_counter == 0 && *it == '}')
					{
						break;
					}
				}
			}
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

void SwitchStatement::getStateMachines(std::vector<SwitchStatement*>& ptr_state_machine)
{
	if (isPossibleStateMachine())
	{
		ptr_state_machine.push_back(this);
	}
	for (SwitchStatement &child : children)
	{
		child.getStateMachines(ptr_state_machine);
	}
	return;
}

const std::set<std::string> SwitchStatement::getStateTransitions() const
{
	using namespace std;
	set<string> state_transitions;
	for (auto child : children)
	{
		set <string> _matching_enumscases
			= child.getMatchingEnumsCases();
		for (auto item : _matching_enumscases)
		{
			state_transitions.insert(item);
		}
		/*state_transitions.insert(
			state_transitions.end(),
			_matching_enumscases.begin(),
			_matching_enumscases.end()
		);*/
	}
	for (auto child : children)
	{
		auto transitions =
			child.getStateTransitions();
		for (auto item : transitions)
		{
			state_transitions.insert(item);
		}
		/*state_transitions.insert(
			state_transitions.end(),
			transitions.begin(),
			transitions.end()
		);*/
	}
	return state_transitions;
}

const std::set<std::string> SwitchStatement::getMatchingEnumsCases() const
{
	using namespace std;
	set<string> matching_enumscases;
	for (auto _enum : enumerations)
	{
		for (auto _case : cases_info)
		{
			if (_enum == _case.getLabel())
			{
				matching_enumscases.insert(_enum);
			}
		}
	}
	for (auto child : children)
	{
		set<string> _matching_enumscases 
			= child.getMatchingEnumsCases();
		for (auto item : _matching_enumscases)
		{
			matching_enumscases.insert(item);
		}
	}
	return matching_enumscases;
}

const bool SwitchStatement::isPossibleStateMachine() const
{
	return !empty() && hasChildren() && doEnumsAndCasesMatch();
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