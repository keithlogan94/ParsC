#ifndef STATEOS_H
#define STATEOS_H
#include <iostream>
#include <vector>
#include "State.h"

std::ostream& operator<<(std::ostream& os, std::vector<State*> _s)
{
	for (auto &_state : _s)
	{
		os << _state->state << " : ";
		for (auto &_event : _state->events)
		{
			os << _event << " : ";
		}
		os << std::endl;
	}
	return os;
}


#endif // STATEOS_H
