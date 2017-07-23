
#include "FileLinker.h"
#include "SwitchStatements.h"
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
	for (auto file_name : files)
	{
		if (file_name == "testlib\stream.c")
		{
			cout << "found file" << endl;
		}
		FileData file(file_name.c_str());
		cout << "searching " << file_name << " for switch statements:" << endl << endl << endl;
		SwitchStatementList switch_ss(file.data());
		switch_ss.writeDebugOutput(cout);
		/*vector<SwitchStatement> _ss = switch_ss.getSwitchStatements();
		for (SwitchStatement switch_statement : _ss)
		{
			if (switch_statement.isStateMachine())
			{
				cout << "possible statemachine: " << endl;
				cout << switch_statement.getBuffer() << endl << endl << endl;
			}
		}*/
	}
	PAUSE_CONSOLE
	return 0;
}