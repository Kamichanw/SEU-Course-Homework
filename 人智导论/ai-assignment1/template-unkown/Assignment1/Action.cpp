#include "Action.h"

std::ostream& operator<<(std::ostream& os, Action action)
{
	switch (action)
	{
	case Action::LEFT: os << "LEFT";    break;
	case Action::UP: os << "UP"; break;
	case Action::RIGHT: os << "RIGHT";  break;
	case Action::DOWN: os << "DOWN";   break;
	case Action::FAILURE: os << "UNKNOW"; break;
	case Action::CUTOFF: os << "CUTOFF"; break;
	default: os.setstate(std::ios_base::failbit);
	}
	return os;
}
