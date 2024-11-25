#pragma once
#include <vector>
#include <set>
#include "Action.h"
#include "Node.h"

/*
	对应书中第三章搜索算法中提到的Problem
*/
class Problem
{
public:
	int size;
	int suffleSteps;	// 由目标状态触发，随机走的步数，类似于洗牌的作用，用于生成随机初始状态
	std::vector<int> initState;
	std::vector<int> goalState;
	std::set<Node*> nodePtrs;	// 保存搜索过程中创建的节点的指针，用于内存管理，如果在代码中使用了new Node，需要把该node的指针放到该变量中

	Problem(int size);
	Problem(int size, int suffleSteps);
	~Problem();

	std::vector<int> result(std::vector<int> state, Action action); // 对应problem.RESULT函数
	bool isGoal(std::vector<int>& state);	// 对应problem.GOAL-TEST函数
	std::vector<Action> getValidActions(std::vector<int>& state);	// 对应problem.ACTIONS函数
	bool isValidAction(std::vector<int>& state, Action action);
	bool isSolution(std::vector<Action>& solution, std::vector<int> initState);

	void updateInitState();		// 随机出一个的新的初始状态，并更新
	void printState(std::vector<int>& state);
	void printSolution(std::vector<Action>& solution);
	void freeMemory();	// 用于内存管理，释放储存在nodePtrs中指针所指向的内存
	void freeMemory(Node* node);	// 用于内存管理，在实现DLS需要调用
private:
	int getAgent(std::vector<int>& state);
};
