
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
	for (auto file_name : files)
	{
		FileData file(file_name.c_str());
		cout << "searching " << file_name << " for switch statements:" << endl << endl << endl;
		SwitchStatements switch_ss(file.data());
		switch_ss.writeDebugOutput(cout);
		cout << endl << endl;
	}
	return 0;
}