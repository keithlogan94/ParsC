#include "StateMachineList.h"

#include <assert.h>


StateMachineList::StateMachineList(SwitchStatementList _ss_list)
{
	using namespace std;
	vector<SwitchStatement> ss_list = 
		_ss_list.getSwitchStatements();
	for (auto s_statement : ss_list)
	{
		vector<SwitchStatement*> ptr_state_machines;
		s_statement.getStateMachines(ptr_state_machines);
		for (auto &_ss : ptr_state_machines)
		{
			StateMachine _state_machine(*_ss);
			state_machinelist.push_back(_state_machine);
		}
		/*
		if (s_statement.isPossibleStateMachine())
		{
			StateMachine _state_machine(s_statement);
			state_machinelist.push_back(_state_machine);
		}*/
	}
}

StateMachineList::~StateMachineList()
{
}

#ifdef _DEBUG
void StateMachineList::writeDebugOutput(std::ostream & os)
{
	for (auto &state_machine : state_machinelist)
	{
		state_machine.print(os);
	}
}
#endif // _DEBUG
