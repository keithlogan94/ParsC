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
#include "Enums.h"

#ifdef _DEBUG
#include <iostream>
#endif //_DEBUG

class SwitchStatementList
{
	std::vector<SwitchStatement> switchStatements;
	const std::string debug_outputfile = "debug_output.txt";
	std::vector<std::string> enumerations;
public:
	SwitchStatementList();
	SwitchStatementList(const std::string& _considering, const Enums& _enums);
	~SwitchStatementList();
	
	//void parseBufferForEnums(const std::string& buffer);
	static std::vector<std::string> extractSwitchStatements(const std::string& str, std::vector<std::string>* _under_cases = nullptr);
	static std::unique_ptr<std::string> removeStringLiterals(const std::string& str);
	static std::unique_ptr<std::string> decomment(const std::string& str);
	inline const std::string& getDebugOutputFile() const { return debug_outputfile; }
	inline const std::vector<SwitchStatement>& getSwitchStatements() { return switchStatements; }


#ifdef _DEBUG
public: 
	void writeDebugOutput(std::ostream& os);
#endif //_DEBUG
};

