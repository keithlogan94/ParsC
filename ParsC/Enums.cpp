#include "Enums.h"



Enums::Enums(const std::string& _considering)
{
	extractEnums(_considering);
}


Enums::~Enums()
{
}

void Enums::extractEnums(const std::string & buffer)
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
									enums.insert(
										enums.end(),
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
									enums.insert(
										enums.end(),
										_enumerations.begin(),
										_enumerations.end()
									);
								}
								else if (!is_enum_object)
								{
									enums.insert(
										enums.end(),
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
