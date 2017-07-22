/*
*		File: SwitchStatements.h
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

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "SwitchStatement.h"

#ifdef _DEBUG
#include <iostream>
#endif //_DEBUG

class SwitchStatements
{
	std::vector<SwitchStatement> switchStatements;
	const std::string debug_outputfile = "debug_output.txt";
public:
	SwitchStatements();
	SwitchStatements(const std::string& _considering);
	~SwitchStatements();
	
	static std::vector<std::string> extractSwitchStatements(const std::string& str);
	static std::unique_ptr<std::string> removeStringLiterals(const std::string& str);
	static std::unique_ptr<std::string> decomment(const std::string& str);
	inline const std::string& getDebugOutputFile() const { return debug_outputfile; }
	inline const std::vector<SwitchStatement>& getSwitchStatements() { return switchStatements; }

#ifdef _DEBUG
public: 
	void writeDebugOutput();
#endif //_DEBUG
};

