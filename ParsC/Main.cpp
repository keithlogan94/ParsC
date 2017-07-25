
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

#ifdef TESTING
	FileData file("testlib\\_0test.c");
	string target_str = file.data();
	SwitchStatementList ssl(target_str);
	StateMachineList sml(ssl);
	sml.writeDebugOutput(cout);
	//FileLinker fl(files);
	//vector <string> switch_statementsfound;
	//size_t index = 0;
	//while ((index = fl.getData().find("switch", index)) != string::npos)
	//{
	//	switch_statementsfound.push_back(fl.getData().substr(index, 300));
	//	index += 6;
	//}
	//cout << switch_statementsfound.size() << 
	//	" accurance(s) of the 'switch' keyword found:" << endl;
	//for (auto switch_statement : switch_statementsfound)
	//{
	//	cout << switch_statement << endl << endl;
	//}
#endif // TESTING

#ifndef TESTING
	/*FileData file("testlib\\_0test.c");
	SwitchStatementList ssl(file.data());
	StateMachineList sml(ssl);
	sml.writeDebugOutput(cout);*/
	cout << "loading files...";
	for (auto file : files)
	{
		cout << "searching " << file << endl;
		FileData _file(file.c_str());
		SwitchStatementList ssl(_file.data());
		StateMachineList sml(ssl);
		/*ofstream ofs("debug_output.xml", ios::app);
		sml.writeDebugOutput(ofs);
		ofs.close();*/
	}
	system("notepad debug_output.xml");
	
#endif // !TESTING


	PAUSE_CONSOLE
	return 0;
}