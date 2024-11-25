#pragma once
#include <iostream>

enum class Action
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	FAILURE,
	CUTOFF
};

extern std::ostream& operator<<(std::ostream& os, Action action);