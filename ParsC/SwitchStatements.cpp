/*
*		File: SwitchStatements.cpp
*		Writer: Keith Logan Becker
*		Description:
*			SwitchStatements.h - ANSI C parser for switch statements
*			ctor takes ANSI C Source Code as string and extracts switch statement
*			character sequences represented in abstractions - Abstractions are
*			implemented in parent, child, sibling relationship.
*
*		Date: 07/20/2017
*		Copyright (c) Keith Logan Becker, All Rights Reserved
*		Keith Becker retains the explicit right
*		to sign over ownership at discretion.
*/

#include "SwitchStatements.h"

#include <istream>
#include <sstream>
#include <assert.h>
#ifdef _DEBUG
#include <fstream>
#include <Windows.h>
#endif //__DEBUG
/**************************************/
/* consider this */
/*if (str.find("switch") != string::npos) {
if (str.find('(') != string::npos ||
(is >> str && str.find('(') != string::npos))
;
else continue;*/
//ss->buffer += "switch ";

/**************************************/
std::istream& operator >> (std::istream& is, SwitchStatements * ss)
{
	assert(ss != nullptr);
	using namespace std;
	is.setstate(ios::goodbit);
	string str;
	bool in_strliteral = false;
	while (is >> str)
	{
#ifdef TESTING
		assert(str.size());
		if (str.find("\\\"") != string::npos)
			continue;
		size_t pos_strl = str.find("\"");
		if (pos_strl != string::npos) {
			if (str == "\"") {
				in_strliteral = !in_strliteral;
				continue;
			}
			if (str.find("\"", pos_strl + 1) != string::npos)
				continue;
			else
				in_strliteral = !in_strliteral;
			string str = "name ";
		}
		if (in_strliteral && str.find(";"))
			in_strliteral = false;
#endif //TESTING
		if (str.find("switch") != string::npos &&
			!in_strliteral) {
			ss->appendBuffer(str);
			int bracket_counter = 0;
			char c = '0';
			while ((c = is.get()) != EOF) {
				ss->appendBuffer(c);
				/* error handling */
				try {
					if (bracket_counter < 0)
						throw std::exception{ "bracket counter cannot be less than 0" };
					if (c == '}' && bracket_counter == 0)
						throw std::exception{ "error cannot meet closing bracket before opening" };
					if (c == EOF && bracket_counter != 0)
						throw std::exception{ "error cannot meet eof before all closing brackets" };
				}
				catch (std::exception _e) {
					cerr << "exception: ";
					Beep(750, 1000);
					cerr << _e.what() << endl;
					cin.get();
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
				/* end error handling */
				if (c == '{')bracket_counter++;
				if (c == '}')bracket_counter--;
				if (c == '}' && !bracket_counter) {
					ss->setOffset(is.tellg());
					assert(bracket_counter == 0);
					return is;
				}
			}
		}
	}
	is.setstate(ios::badbit);
	return is;
}

std::istream& operator >> (std::istream& is, SwitchStatements& ss)
{
	using namespace std;
	is.setstate(ios::goodbit);
	string str;
	bool in_strliteral = false;
	while (is >> str)
	{
#ifdef TESTING
		assert(str.size());
		if (str.find("\\\"") != string::npos)
			continue;
		size_t pos_strl = str.find("\"");
		if (pos_strl != string::npos) {
			if (str == "\"") {
				in_strliteral = !in_strliteral;
				continue;
			}
			if (str.find("\"", pos_strl + 1) != string::npos)
				continue;
			else
				in_strliteral = !in_strliteral;
			string str = "name ";
		}
		if (in_strliteral && str.find(";"))
			in_strliteral = false;
#endif //TESTING
		if (str.find("switch") != string::npos &&
			!in_strliteral) {
			ss.appendBuffer(str);
			int bracket_counter = 0;
			char c = '0';
			while ((c = is.get()) != EOF) {
				ss.appendBuffer(c);
				/* error handling */
				try {
					if (bracket_counter < 0)
						throw std::exception{ "bracket counter cannot be less than 0" };
					if (c == '}' && bracket_counter == 0)
						throw std::exception{ "error cannot meet closing bracket before opening" };
					if (c == EOF && bracket_counter != 0)
						throw std::exception{ "error cannot meet eof before all closing brackets" };
				}
				catch (std::exception _e) {
					cerr << "exception: ";
					Beep(750, 1000);
					cerr << _e.what() << endl;
					cin.get();
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
				/* end error handling */
				if (c == '{')bracket_counter++;
				if (c == '}')bracket_counter--;
				if (c == '}' && !bracket_counter) {
					assert(bracket_counter == 0);
					return is;
				}
			}
		}
	}
	is.setstate(ios::badbit);
	return is;
}


SwitchStatements::SwitchStatements(std::unique_ptr<std::string> _considering)
{
	using namespace std;
	stringstream ss;
	ss << *_considering;
	ss >> this;
	if (ss.good())
	{
		stringstream ss_child;
		string buf_sub = this->buffer.substr(this->buffer.find_first_of('{'));
		ss_child << buf_sub;
		SwitchStatements ss_switch;
		while (ss_child >> ss_switch)
		{
			SwitchStatements ss_switch_child(
				make_unique<string>(string{ ss_switch.buffer })
			);
			if (!ss_switch_child.buffer.empty() || 
				!ss_switch_child.getSibling().empty())
				children.push_back(ss_switch_child);
			ss_child.clear();
			ss_switch_child.clearAll();
		}
		siblings.push_back(SwitchStatements(
			make_unique<string>(string{ (*_considering).substr(offset) })
		));
	}
}


void SwitchStatements::clearAll()
{
	buffer.clear();
	children.clear();
	siblings.clear();
	offset = 0;
}

std::unique_ptr<std::string> SwitchStatements::decomment(const std::string& str)
{
	using namespace std;
	bool record = true;
	unique_ptr<string> decommented = make_unique<string>();
	bool multiline = false;
	bool single = false;
	bool single_tag = false;
	for (string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		if (!single_tag && !single && !(it + 1 >= str.end()))
		{
			if (*it == '/' && *(it + 1) == '*')
			{
				record = false;
				multiline = true;
			}
			if (!record && *it == '*' && *(it + 1) == '/')
			{
				record = true;
				multiline = false;
				it++;
				continue;	
			}
		}
		if (!single_tag && !multiline && !(it + 1 >= str.end()))
		{
			if (*it == '/' && *(it + 1) == '/')
			{
				record = false;
				single = true;
			}
			if (!record && *it == '\n')
			{
				record = true;
				single = false;
			}
		}
		if (!multiline && !single && !(it + 1 >= str.end()))
		{
			if (*it == '#' && *(it + 1) == ' ')
			{
				record = false;
				single_tag = true;
			}
			if (!record && *(it - 1) == '\n')
			{
				record = true;
				single_tag = false;
			}
		}
		if (record)
		{
			*decommented += *it;
		}
	}
	return decommented;
}

std::unique_ptr<std::string> SwitchStatements::removeStringLiterals(const std::string & str)
{
	using namespace std;
	unique_ptr<string> no_strliterals = make_unique<string>();
	bool record = true;
	for (string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		bool set_once = false;
		if (*it == '"' && record)
		{
			record = false;
			set_once = true;
		}
		if (record)
		{
			if (str.end() - it >= 5) 
			{
				if (*it == 's' &&
					*(it + 1) == 'w' &&
					*(it + 2) == 'i' &&
					*(it + 3) == 't' &&
					*(it + 4) == 'c' &&
					*(it + 5) == 'h')
				{
					int bracket_counter = 0;
#ifndef REMOVE_SWITCH_STATEMENTS
					*no_strliterals += *it;
#endif //REMOVE_SWITCH_STATEMENTS
					do
					{
						it++;
#ifndef REMOVE_SWITCH_STATEMENTS
						*no_strliterals += *it;
#endif //REMOVE_SWITCH_STATEMENTS
						if (*it == '{')
						{
							bracket_counter++;
						}
						if (*it == '}')
						{
							bracket_counter--;
						}
						try
						{
							/* error handling */
							if (bracket_counter > 0 && it + 1 == str.end())
							{
								throw exception{ "cannot reach end of file before all closing brackets" };
							}
							if (bracket_counter < 0)
							{
								throw exception{ "bracket_counter cannot be lower than 0" };
							}
							/* end error handling */
						}
						catch (const std::exception& _e)
						{
							cerr << "exception: ";
							Beep(750, 1000);
							cerr << _e.what() << endl;
							cin.get();
							cin.clear();
							cin.ignore(INT_MAX, '\n');
						}
						if (*it == '}' && bracket_counter == 0)
						{
							it++;
							break;
						}
					} while (true);
				}
			}
		}
		if (record)
			*no_strliterals += *it;
		if (!set_once &&
			*it == '"' && !record)
		{
			record = true;
		}
	}
	return no_strliterals;
}

std::vector<std::string> SwitchStatements::extractSwitchStatements(const std::string& str)
{
	using namespace std;
	vector<string> switch_statements;
	bool record = true;
	string current_switchstatement;
	for (string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		bool set_once = false;
		if (*it == '"' && record)
		{
			record = false;
			set_once = true;
		}
		if (record)
		{
			if (str.end() - it >= 5)
			{
				if (*it == 's' &&
					*(it + 1) == 'w' &&
					*(it + 2) == 'i' &&
					*(it + 3) == 't' &&
					*(it + 4) == 'c' &&
					*(it + 5) == 'h')
				{
					set_once = false;
					int bracket_counter = 0;
					current_switchstatement += *it;
					bool in_string = false;
					do
					{
						if (it + 1 == str.end())
						{
							break;
						}
						it++;
						current_switchstatement += *it;
						if (str.end() - it >= 1)
						{
							if (*it == '"' && *(it - 1) != '\'' && *(it + 1) != '\'' && *(it - 1) != '\\')
							{
								in_string = !in_string;
							}
						}
						else
						{
							if (*it == '"')
							{
								in_string = !in_string;
							}
						}
						if (str.end() - it >= 1 && !in_string)
						{
							if (*it == '{' && *(it - 1) != '\'' && *(it + 1) != '\'')
							{
								bracket_counter++;
							}
							else if (*it == '}' && *(it - 1) != '\'' && *(it + 1) != '\'')
							{
								bracket_counter--;
							}
						}
						else if (!in_string)
						{
							if (*it == '{')
							{
								bracket_counter++;
							}
							else if (*it == '}')
							{
								bracket_counter--;
							}
						}
						try
						{
							/* error handling */
							if (bracket_counter > 0 && it + 1 == str.end())
							{
								throw exception{ "cannot reach end of file before all closing brackets" };
							}
							if (bracket_counter < 0)
							{
								throw exception{ "bracket_counter cannot be lower than 0" };
							}
							/* end error handling */
						}
						catch (const std::exception& _e)
						{
							cerr << "exception: ";
							Beep(750, 1000);
							cerr << _e.what() << endl;
							cin.get();
							cin.clear();
							cin.ignore(INT_MAX, '\n');
							throw _e;
						}
						if (*it == '}' && bracket_counter == 0)
						{
							it++;
							switch_statements.push_back(current_switchstatement);
							current_switchstatement.clear();
							break;
						}
					} while (true);
				}
			}
		}
		if (!set_once &&
			*it == '"' && !record)
		{
			record = true;
		}
	}
	return switch_statements;
}


#ifdef _DEBUG

void SwitchStatements::writeDebugOutput()
{
	using namespace std;
	print();
	ofstream ofs(this->debug_outputfile, ios::app);
	assert(ofs.is_open());
	for (auto &l : children) {
		ofs << "child:" << endl;
		l.writeDebugOutput();
	}

	for (auto &l : siblings) {
		if (!l.buffer.empty()) {
			ofs << "sibling:" << endl;
			l.writeDebugOutput();
		}
	}
	ofs.close();
}

void SwitchStatements::print()
{
	using namespace std;
	ofstream ofs(debug_outputfile, std::ios::app);
	if (ofs.is_open()) {
		ofs << buffer << endl << endl << endl;
		ofs.close();
	}
}

#endif //_DEBUG

SwitchStatements::SwitchStatements()
{

}


SwitchStatements::~SwitchStatements()
{
}
