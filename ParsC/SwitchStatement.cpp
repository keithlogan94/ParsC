#include "SwitchStatement.h"

#include "SwitchStatements.h"



SwitchStatement::SwitchStatement(const std::string & switchStatement)
{
	buffer = switchStatement;
	auto vec_children = SwitchStatements::extractSwitchStatements(
		switchStatement.substr(switchStatement.find_first_of('{'))
	);
	for (auto child : vec_children)
	{
		children.push_back(SwitchStatement(child));
	}
}

SwitchStatement::~SwitchStatement()
{
}

void SwitchStatement::writeDebugOutput(std::ofstream & ofs)
{
	using namespace std;
	ofs << buffer << endl << endl;
	for (auto child : children)
	{
		child.writeDebugOutput(ofs);
	}
}
