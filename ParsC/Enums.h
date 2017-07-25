#pragma once
#include <vector>
#include <string>

class Enums
{
	std::vector<std::string> enums;
public:
	Enums(const std::string& _considering);
	~Enums();

	inline const std::vector<std::string>& getEnums() const { return enums; }

private:
	void extractEnums(const std::string& buffer);
};

