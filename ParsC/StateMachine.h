#pragma once
#include "SwitchStatement.h"
#include "State.h"
#include <vector>
#include <string>

class StateMachine
{
	std::set <std::string> possible_states;
	std::set <std::string> state_transitions;
	std::string raw_data;
	std::vector<State> states;
public:
	StateMachine(SwitchStatement& _switch_statement);
	~StateMachine();

#ifdef _DEBUG
	void print(std::ostream& os) const;
#endif
};

