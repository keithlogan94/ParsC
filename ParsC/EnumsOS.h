#ifndef ENUMSOS_H
#define ENUMSOS_H
#include <iostream>
#include "Enums.h"

std::ostream& operator<<(std::ostream& os, const Enums& _enums)
{
	for (auto _enum : _enums.getEnums()) {
		os << _enum << std::endl;
	}
	return os;
}


#endif // !ENUMSOS_H
