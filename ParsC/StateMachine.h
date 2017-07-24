#pragma once
#include "SwitchStatement.h"
#include <vector>
#include <string>

class StateMachine
{
	std::vector <std::string> possible_states;
	std::vector <std::string> state_transitions;
	std::string raw_data;
public:
	StateMachine(const SwitchStatement& _switch_statement);
	~StateMachine();

#ifdef _DEBUG
	void print(std::ostream& os) const;
#endif
};

