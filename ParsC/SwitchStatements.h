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
#ifdef _DEBUG
#include <iostream>
#endif //_DEBUG

class SwitchStatements
{
	std::vector<SwitchStatements> children;
	std::vector<SwitchStatements> siblings;
	std::string buffer;
	size_t offset = 0;
	const std::string debug_outputfile = "debug_output.txt";
public:

	SwitchStatements();
	SwitchStatements(const std::string& _considering);
	~SwitchStatements();

	void clearAll();
	static std::unique_ptr<std::string> removeStringLiterals(const std::string& str);
	inline const std::string& getDebugOutputFile() const { return debug_outputfile; }
	inline const std::vector<SwitchStatements>& getSibling() { return siblings; }
	inline const std::vector<SwitchStatements>& getChildren() const { return children; }
	inline void appendBuffer(const std::string& _toAppend) { buffer.append(_toAppend); }
	inline void appendBuffer(const char& _toAppend) { buffer += _toAppend; }
	inline void setOffset(const size_t& _offset) { offset = _offset; }

private:
	std::unique_ptr<std::string> decomment(const std::string& str);
	std::vector<std::string> extractSwitchStatements(const std::string& str);

#ifdef _DEBUG
public:
	void writeDebugOutput();
private:
	void print();
#endif //_DEBUG
};

