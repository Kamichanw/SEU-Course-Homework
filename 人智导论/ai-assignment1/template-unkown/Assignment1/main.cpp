#include <ctime>
#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include "Problem.h"
#include <format>
#include "Search.h"
#include "Action.h"
using namespace std;
typedef std::vector<Action>(*searchFunc)(Problem& problem);

void printStats(std::vector<std::pair<int, float>>& statistics)
{
	std::cout << "length, seconds" << '\n';
	for (auto& pair : statistics)
	{
		std::cout << pair.first << ", " << pair.second << '\n';
	}
}
float total = 0.0;

void doExperiment(int iteration, int problemSize, int suffleSteps, searchFunc searchFunc)
{
	std::vector<std::pair<int, float>> statistics;
	fstream fs("manhattan.csv", ios::trunc | ios::out);
	fs << "solution size,time use(s),space use" << endl;
	for (int i = 0; i < iteration; i++)
	{
		Problem problem(problemSize, suffleSteps);
		problem.printState(problem.initState);

		clock_t t = clock();
		std::vector<Action> solution = searchFunc(problem);
		t = clock() - t;
		total += ((float)t) / CLOCKS_PER_SEC;
		std::pair<int, float> stats(solution.size(), ((float)t) / CLOCKS_PER_SEC);
		statistics.push_back(stats);
		printf("Searching tooks %f seconds.\n", stats.second);
		problem.printSolution(solution);

		problem.updateInitState();
		if (solution.size() && solution[0] != Action::FAILURE)
			fs << format("{},{},{}\n", solution.size(), ((float)t) / CLOCKS_PER_SEC, problem.nodePtrs.size());
	}

	printStats(statistics);
}

void testSearchFunction(searchFunc searchFunc)
{
	int iteration = 1;
	int size = 3;
	int suffleSteps = 30;

	for (int i = 1; i <= iteration; i++)
	{
		Problem problem(size, suffleSteps);
		std::vector<Action> solution = searchFunc(problem);
		if (solution == std::vector<Action>({ Action::CUTOFF }))
		{
			std::cout << "Iteration " << i << ": CUTOFF\n";
		}
		else
		{
			std::cout << "Iteration " << i << ": ";
			std::cout << problem.isSolution(solution, problem.initState) << std::endl;
		}
		problem.updateInitState();
	}
}


int main()
{
	std::srand((unsigned int)std::time(NULL)); // Generate a random seed

	doExperiment(50, 3, 30, (searchFunc)search::aStarManhattan);
	// 以下函数用于测试搜索函数结果的正确性
	//testSearchFunction((searchFunc)search::bfs);
	//testSearchFunction((searchFunc)search::dlsWrapper);
	//testSearchFunction((searchFunc)search::aStarMisplace);
	//testSearchFunction((searchFunc)search::aStarManhattan);
	std::cout << std::endl << total;
}