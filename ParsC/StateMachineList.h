#pragma once
#include "StateMachine.h"
#include "SwitchStatements.h"
#include <vector>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


class StateMachineList
{
	std::vector<StateMachine> state_machinelist;
public:
	StateMachineList(SwitchStatementList _ss_list);
	~StateMachineList();

#ifdef _DEBUG
	void writeDebugOutput(std::ostream& os);
#endif // _DEBUG

};

