#include "StateMachineList.h"



StateMachineList::StateMachineList(SwitchStatementList _ss_list)
{
	using namespace std;
	vector<SwitchStatement> ss_list = 
		_ss_list.getSwitchStatements();
	for (auto s_statement : ss_list)
	{
		if (s_statement.isPossibleStateMachine())
		{
			StateMachine _state_machine(s_statement);
			state_machinelist.push_back(_state_machine);
		}
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

