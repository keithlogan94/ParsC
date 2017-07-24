#include "StateMachine.h"

#include <set>

#ifdef _DEBUG
#include <iostream>
#endif //_DEBUG

StateMachine::StateMachine(const SwitchStatement& _switch_statement)
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
}


StateMachine::~StateMachine()
{
}

#ifdef _DEBUG

void StateMachine::print(std::ostream& os) const
{
	using namespace std;
	os << "possible states: " << endl;
	for (auto state : possible_states)
	{
		os << state << " : ";
	}
	os << endl;
	os << "possible state transitions:" << endl;
	for (auto transition : state_transitions)
	{
		os << transition << " : ";
	}
	os << endl << endl;
}

#endif// _DEBUG