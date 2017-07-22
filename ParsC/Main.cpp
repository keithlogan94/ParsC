
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
	cout << "searching dir for files" << endl;
	for (auto f : dir)
	{
		stringstream ss;
		ss << f;
		if (ss.str().find('.h') != string::npos ||
			ss.str().find('.c') != string::npos)
			files.push_back(ss.str());
	}
	cout << "loading files" << endl;
	FileLinker fl(files);
	cout << "scanning files for switch statments...";
	SwitchStatements ss(fl.getData());
	cout << "scanning done" << endl;
	remove(ss.getDebugOutputFile().c_str());
	cout << "writing debug output...";
	ss.writeDebugOutput();
	cout << "done" << endl;
	cout << "opening debug output" << endl;
	system((string("notepad ") + ss.getDebugOutputFile()).c_str());

	return 0;
}