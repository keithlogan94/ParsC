#include <SwitchStatements.h>
#include <FileData.h>
#include <FileLinker.h>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <memory>
#include <Windows.h>
using namespace std;

#define NORMAL_TEST

#ifndef NORMAL_TEST
#define FIND_THIS
#endif //ifndef NORMAL_TEST

int main() {
#ifdef FIND_THIS
	namespace fs = std::experimental::filesystem;
	auto dir = fs::directory_iterator("testlib");
	vector<string> files;
	for (auto f : dir)
	{
		stringstream ss;
		ss << f;
		if (ss.str().find(".h") == string::npos ||
			ss.str().find(".c") == string::npos)
			files.push_back(ss.str());
	}
	string find_this = "switch on' redist support (direct numeric entry remaining";

	for (auto f : files)
	{
		FileData file(f.c_str());
		size_t pos = file.data().find(find_this);
		if (pos != string::npos)
		{
			cout << "found data:" << endl;
			Beep(750, 1000);
			const size_t back_up = 300;
			cout << file.data().substr(pos - back_up, back_up + find_this.size());
			cin.get();
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}

#endif //FIND_THIS
#ifdef NORMAL_TEST
	namespace fs = std::experimental::filesystem;
	auto dir = fs::directory_iterator("testlib");
	vector<string> files;
	cout << "searching files...";
	for (auto f : dir)
	{
		stringstream ss;
		ss << f;
		files.push_back(ss.str());
	}
	cout << "done" << endl;

	cout << "loading files...";
	FileLinker fl(files);
	cout << "done" << endl;
	cout << "decommenting c source code...";
	unique_ptr<string> source_uncommented = SwitchStatementList::decomment(fl.getData());
	cout << "done" << endl;
	cout << "extracting switch statements..." << endl;
	vector<string> switch_statements = 
		SwitchStatementList::extractSwitchStatements(*source_uncommented);
	cout << "done" << endl;
	cout << "outputting data...";
	for (string ss : switch_statements)
	{
		cout << "switch statement: " << endl;
		cout << ss << endl << endl << endl;
	}
	cout << "done" << endl;

	cin.get();
	cin.clear();
	cin.ignore(INT_MAX, '\n');
#endif //NORMAL_TEST
	return 0;
}