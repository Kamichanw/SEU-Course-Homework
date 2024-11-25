#include "Problem.h"

Problem::Problem(int size)
{
	this->size = size;
	this->suffleSteps = -1;

	for (int i = 0; i < size * size; i++)
	{
		this->goalState.push_back(i);
	}
}

Problem::Problem(int size, int suffleSteps)
{
	this->size = size;
	this->suffleSteps = suffleSteps;

	for (int i = 0; i < size * size; i++)
	{
		this->goalState.push_back(i);
	}

	std::vector<int> state = this->goalState;
	for (int i = 0; i < suffleSteps; i++)
	{
		std::vector<Action> actions = getValidActions(state);
		state = result(state, actions[rand() % actions.size()]);
	}
	this->initState = state;
}

Problem::~Problem()
{
	freeMemory();
}

std::vector<int> Problem::result(std::vector<int> state, Action action)
{
	if (!isValidAction(state, action)) return state;

	int agentIdx = getAgent(state);

	switch (action)
	{
	case Action::LEFT:
		state[agentIdx] = state[agentIdx - 1];
		state[agentIdx - 1] = 0;
		break;
	case Action::UP:
		state[agentIdx] = state[agentIdx - this->size];
		state[agentIdx - this->size] = 0;
		break;
	case Action::RIGHT:
		state[agentIdx] = state[agentIdx + 1];
		state[agentIdx + 1] = 0;
		break;
	case Action::DOWN:
		state[agentIdx] = state[agentIdx + this->size];
		state[agentIdx + this->size] = 0;
		break;
	}

	return state;
}

bool Problem::isGoal(std::vector<int>& state)
{
	return state == this->goalState;
}

std::vector<Action> Problem::getValidActions(std::vector<int>& state)
{
	std::vector<Action> result;
	int agentIdx = getAgent(state);
	if (agentIdx % this->size != 0) result.push_back(Action::LEFT);
	if (agentIdx >= this->size) result.push_back(Action::UP);
	if (agentIdx % this->size != this->size - 1) result.push_back(Action::RIGHT);
	if (agentIdx < this->size * (this->size - 1)) result.push_back(Action::DOWN);
	return result;
}

bool Problem::isValidAction(std::vector<int>& state, Action action)
{
	std::vector<Action> validActions = getValidActions(state);

	for (Action a : validActions)
	{
		if (a == action) return true;
	}

	return false;
}

bool Problem::isSolution(std::vector<Action>& solution, std::vector<int> initState)
{
	std::vector<int> state = initState;
	for (Action action : solution)
	{
		state = result(state, action);
	}
	if (isGoal(state)) return true;

	return false;
}

void Problem::updateInitState()
{
	std::vector<int> state = this->goalState;
	for (int i = 0; i < this->suffleSteps; i++)
	{
		std::vector<Action> actions = getValidActions(state);
		state = result(state, actions[rand() % actions.size()]);
	}
	this->initState = state;
}

void Problem::printState(std::vector<int>& state)
{
	std::cout << "Current State: \n";
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			std::cout << state[i * this->size + j] << " ";
		}
		std::cout << '\n';
	}
}

void Problem::printSolution(std::vector<Action>& solution)
{
	if (solution.size() == 0)
	{
		std::cout << "The init state is same as the goal state.\n";
		return;
	}

	if (solution[0] == Action::FAILURE)
	{
		std::cout << "No Valid Solution\n";
		return;
	}

	std::cout << "Solution Found\n";
	std::cout << "Action Sequence Length: " << solution.size() << '\n';
	std::cout << "Actions: ";
	for (Action action : solution)
	{
		std::cout << action << " ";
	}
	std::cout << '\n';
}

void Problem::freeMemory()
{
	for (Node* nodePtr : this->nodePtrs)
	{
		delete nodePtr;
	}
	this->nodePtrs.clear();
}

void Problem::freeMemory(Node* node)
{
	if (nodePtrs.find(node) != nodePtrs.end())
	{
		this->nodePtrs.erase(node);
		delete node;
	}
}


int Problem::getAgent(std::vector<int>& state)
{
	for (unsigned int i = 0; i < state.size(); i++)
	{
		if (state[i] == 0) return i;
	}

	return -1;
}