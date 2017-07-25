#pragma once
#include "StateMachine.h"
#include "SwitchStatements.h"
#include "State.h"
#include <vector>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


class StateMachineList
{
	std::vector<StateMachine> state_machinelist;
	std::vector<State*> state_list;
public:
	StateMachineList(SwitchStatementList _ss_list);
	~StateMachineList();

	inline std::vector<State*> getStateList() { return state_list; }
#ifdef _DEBUG
	void writeDebugOutput(std::ostream& os);
#endif // _DEBUG

};

