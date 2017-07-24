#include "StateMachine.h"

#ifdef _DEBUG
#include <iostream>
#endif //_DEBUG

StateMachine::StateMachine(const SwitchStatement& _switch_statement)
{
	raw_data = _switch_statement.getBuffer();
	possible_states = _switch_statement.getMatchingEnumsCases();
	state_transitions = _switch_statement.getStateTransitions();
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