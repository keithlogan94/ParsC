
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
#ifdef _DEBUG
	cout << "searching dir for files" << endl;
#endif //_DEBUG
	for (auto f : dir)
	{
		stringstream ss;
		ss << f;
		if (ss.str().find('.h') != string::npos ||
			ss.str().find('.c') != string::npos)
			files.push_back(ss.str());
	}
#ifdef _DEBUG
	cout << "loading files" << endl;
#endif //_DEBUG
	FileLinker fl(files);
#ifdef _DEBUG
	cout << "scanning files for switch statments...";
#endif //_DEBUG
	SwitchStatements ss(SwitchStatements::decomment(fl.getData()));
#ifdef _DEBUG
	cout << "scanning done" << endl;
#endif //_DEBUG
#ifdef _DEBUG
	remove(ss.getDebugOutputFile().c_str());
	cout << "writing debug output...";
	ss.writeDebugOutput();
	cout << "done" << endl;
	cout << "opening debug output" << endl;
	system((string("notepad ") + ss.getDebugOutputFile()).c_str());
#endif //_DEBUG

	return 0;
}