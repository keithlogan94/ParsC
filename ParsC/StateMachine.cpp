#include "StateMachine.h"

#include <set>

#ifdef _DEBUG
#include <iostream>
#endif //_DEBUG

StateMachine::StateMachine(SwitchStatement& _switch_statement)
{
	using namespace std;
	raw_data = _switch_statement.getBuffer();
	possible_states = _switch_statement.getMatchingEnumsCases();
	state_transitions = _switch_statement.getStateTransitions();
	for (set<string>::iterator it = possible_states.begin(); it != possible_states.end();)
	{
		bool erased = false;
		for (auto transition : state_transitions)
		{
			if (*it == transition)
			{
				it = possible_states.erase(it);
				erased = true;
				break;
			}
		}
		if (!erased)
		{
			it++;
		}
	}
	vector<SwitchStatement*> all_children;
	_switch_statement.getAllChildren(all_children);
	for (auto &child : all_children)
	{
		State state;
		if (child->isChild())
		{
			state.state = child->getUnderCase();
			auto cases_info = child->getCasesInfo();
			for (auto _case : cases_info)
			{
				state.events.push_back(_case.getLabel());
			}
		}
		states.push_back(state);
	}
}


StateMachine::~StateMachine()
{
}

void StateMachine::getAllStates(std::vector<State*>& _states)
{
	for (auto &_state : states)
	{
		_states.push_back(&_state);
	}
}

#ifdef _DEBUG

void StateMachine::print(std::ostream& os) const
{
	using namespace std;
	os << "<possiblestates>" << endl;
	for (auto state : possible_states)
	{
		os << "\t<state name='" << state << "' />" << endl;
	}
	os << "</possiblestates>" << endl << endl;

	os << "<possibletransitionevents>" << endl;
	for (auto transition : state_transitions)
	{
		os << "<\ttransition name='" << transition << "' />" << endl;
	}
	os << "</possibletransitionevents>" << endl << endl;

	for (auto _state : states)
	{
		os << "<state name='" << _state.state << "'>" << endl;
		for (auto _event : _state.events)
		{
			os << "\t<transitionevents name='" << _event << "' />" << endl;
		}
		os << "</state>" << endl;
	}
}

#endif// _DEBUG