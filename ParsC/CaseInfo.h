#pragma once
#include <string>
class CaseInfo
{
	std::string label;
	int value = 0;
	int pos = 0;
public:
	CaseInfo();
	CaseInfo(std::string _label, int _value, int _pos)
		: label{ _label }, value{ _value }, pos{ _pos } {}
	~CaseInfo();

	inline const std::string& getLabel() const { return label; }
	inline int getValue() const { return value; }
	inline int getPos() const { return pos; }
	inline void setLabel(const std::string& _label) { label = _label; }
	inline void setValue(const int& _value) { value = _value; }
	inline void setPos(const int& _pos) { pos = _pos; }
};

