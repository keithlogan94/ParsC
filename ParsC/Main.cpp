
#include "FileLinker.h"
#include "SwitchStatements.h"
#include "StateMachineList.h"
#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>
#ifdef _DEBUG
#include <Windows.h>
#endif //_DEBUG

#define PAUSE_CONSOLE \
	cin.get(); \
	cin.clear(); \
	cin.ignore(INT_MAX, '\n');

using namespace std;

int main(void)
{
	//SEARCH FOR FILES
	vector<string> files;
	namespace fs = std::experimental::filesystem;
	auto dir = fs::directory_iterator("testlib");
	for (auto f : dir)
	{
		stringstream ss;
		ss << f;
		if (ss.str().find('.h') != string::npos ||
			ss.str().find('.c') != string::npos)
			files.push_back(ss.str());
	}
	cout << files.size() << " file(s) found." << endl;
	//OUTPUT POSSIBLE STATE MACHINES
	cout << "loading files...";
	FileLinker fl(files);
	cout << "done" << endl;
	cout << "scanning for switch statements...";
	SwitchStatementList ss_list(fl.getData());
	cout << "done" << endl;
	cout << "finding all state machines...";
	StateMachineList machine_list(ss_list);
	cout << "done" << endl;
#ifdef _DEBUG
	cout << "outputting results...";
	machine_list.writeDebugOutput(cout);
	cout << "done" << endl;
#endif // _DEBUG


	PAUSE_CONSOLE
	return 0;
}