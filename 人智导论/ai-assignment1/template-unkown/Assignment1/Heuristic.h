#pragma once
#include <vector>

/*
	给A*算法提供hCost
*/
namespace heuristic
{
	struct Position
	{
		int row;
		int col;
	};

	Position getPosition(int gridSize, int value);

	int misplace(std::vector<int>& state, std::vector<int>& goalState);
	int manhattan(std::vector<int>& state, std::vector<int>& goalState);
};

