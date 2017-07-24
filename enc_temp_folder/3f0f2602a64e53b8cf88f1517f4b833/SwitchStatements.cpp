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
#include <Windows.h>
#endif //__DEBUG



SwitchStatementList::SwitchStatementList(const std::string& _considering)
{
	using namespace std;
	vector<string> vec_ss = 
		extractSwitchStatements(*decomment(_considering));
	parseBufferForEnums(_considering);
	for (auto ss : vec_ss)
	{
		switchStatements.push_back(SwitchStatement(ss, enumerations));
	}
}


std::unique_ptr<std::string> SwitchStatementList::decomment(const std::string& str)
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

std::unique_ptr<std::string> SwitchStatementList::removeStringLiterals(const std::string & str)
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


void SwitchStatementList::parseBufferForEnums(const std::string& buffer)
{
	using namespace std;
	bool _in_string = false;
	bool _in_tag = false;
	for (string::const_iterator it = buffer.begin(); it != buffer.end(); ++it)
	{
		if (it != buffer.begin())
		{
			if (*it == ' ' && *(it - 1) == '#')
			{
				do
				{
					if (it + 1 == buffer.end())
					{
						break;
					}
					it++;
				} while (*it != '\n');
			}
		}
		if (*it == '"')
		{
			_in_string = !_in_string;
		}
		if (!_in_string && buffer.end() - it >= 5)
		{
			if (*it == 's' &&
				*(it + 1) == 'w' &&
				*(it + 2) == 'i' &&
				*(it + 3) == 't' &&
				*(it + 4) == 'c' &&
				*(it + 5) == 'h')
			{
				it += 5;
				int bracket_counter = 0;
				while (true)
				{
					it++;
					if (buffer.end() - it >= 1)
					{
						if (*it == '{' && *(it - 1) != '\'' && *(it + 1) != '\'')
						{
							bracket_counter++;
						}
						if (*it == '}' && *(it - 1) != '\'' && *(it + 1) != '\'')
						{
							bracket_counter--;
						}
					}
					else
					{
						if (*it == '{')
						{
							bracket_counter++;
						}
						if (*it == '}')
						{
							bracket_counter--;
						}
					}
					if (bracket_counter == 0 && *it == '}')
					{
						break;
					}
				}
			}
		}
		if (!_in_string && buffer.end() - it >= 5)
		{
			if (isspace(*it) &&
				*(it + 1) == 'e' &&
				*(it + 2) == 'n' &&
				*(it + 3) == 'u' &&
				*(it + 4) == 'm' &&
				isspace(*(it + 5)))
			{
				vector<string> _enumerations;
				it += 5;
				bool is_enum_object = false;
				bool eof = false;
				do
				{
					if (it + 1 == buffer.end())
					{
						eof = true;
						break;
					}
					it++;
					if (isalpha(*it))
						is_enum_object = true;
				} while (*it != '{');
				if (eof)
				{
					break;
				}
				int bracket_counter = 0;
				string _enum;
				do
				{
					if (*it == '\0' || it + 1 == buffer.end())
					{
						break;
					}
					if (*(it - 1) == '/' && *it == '*')
					{
						do
						{
							if (it + 1 == buffer.end())
							{
								break;
							}
							it++;
							if (*it == '/' && *(it - 1) == '*')
							{
								break;
							}
						} while (true);
					}
					if (*it == '{')
					{
						bracket_counter++;
					}
					if (*it == '}')
					{
						bracket_counter--;
						if (bracket_counter == 0)
						{
							do
							{
								if (it + 1 == buffer.end())
								{
									enumerations.insert(
										enumerations.end(),
										_enumerations.begin(),
										_enumerations.end()
									);
									break;
								}
								it++;
								if (*(it - 1) == '/' && *it == '*')
								{
									do
									{
										if (it + 1 == buffer.end())
										{
											break;
										}
										it++;
										if (*it == '/' && *(it - 1) == '*')
										{
											break;
										}
									} while (true);
								}
								if (is_enum_object && *it == ';')
								{
									enumerations.insert(
										enumerations.end(),
										_enumerations.begin(),
										_enumerations.end()
									);
								}
								else if (!is_enum_object)
								{
									enumerations.insert(
										enumerations.end(),
										_enumerations.begin(),
										_enumerations.end()
									);
									break;
								}
							} while (isspace(*it));
						}
					}
					if (isalpha(*it) || *it == '_')
					{
						_enum.push_back(*it);
					}
					if (isspace(*it) || *it == ',')
					{
						if (!_enum.empty())
						{
							_enumerations.push_back(_enum);
							_enum.clear();
						}
					}
					it++;
					if (*it == ';' && bracket_counter != 0)
					{
						bracket_counter = 0;
					}
					if (buffer.end() - it >= 4)
					{
						if (isspace(*it) &&
							*(it + 1) == 'f' &&
							*(it + 2) == 'o' &&
							*(it + 3) == 'r' &&
							isspace(*(it + 4)))
						{
							bracket_counter = 0;
						}
					}
					if (buffer.end() - it >= 3)
					{
						if (isspace(*it) &&
							*(it + 1) == 'i'  &&
							*(it + 2) == 'f' &&
							isspace(*it))
						{
							bracket_counter = 0;
						}
					}
				} while (bracket_counter != 0);
			}
		}
	}
}

std::vector<std::string> SwitchStatementList::extractSwitchStatements(const std::string& str)
{
	using namespace std;
	vector<string> switch_statements;
	bool record = true;
	string current_switchstatement;
	size_t at = 0;
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

void SwitchStatementList::writeDebugOutput(std::ostream& os)
{
	using namespace std;
	for (auto &l : switchStatements) {
		l.writeDebugOutput(os);
	}
}

#endif //_DEBUG

SwitchStatementList::SwitchStatementList()
{

}


SwitchStatementList::~SwitchStatementList()
{
}
