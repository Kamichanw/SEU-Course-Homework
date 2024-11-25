#pragma once
#include "Node.h"
#include "Problem.h"
#include "Action.h"
#include "Heuristic.h"
#include <vector>
#include <set>
#include <queue>
#include <map>

namespace search
{
	Node childNode(Problem& problem, Node& parent, Action action, int cost);	// 对应CHILD-NODE函数
	std::vector<Action> getSolution(Node node);		// 对应SOLUTION函数
	bool inSet(std::set<std::vector<int>>& collection, std::vector<int>& state);
	bool inMap(std::map<std::vector<int>, Node*>& map, std::vector<int>& state);
	// 把oldNode的数据替换为newNode中的数据，oldNode需要为frontier中的元素
	void updateNode(std::priority_queue<Node*, std::vector<Node*>, Node::cmp>& frontier, Node* oldNode, Node* newNode);
	// breadth first search 算法
	std::vector<Action> bfs(Problem& problem);
	// depth limit search 算法
	std::vector<Action> recursiveDLS(Node& node, Problem& problem, int limit);
	std::vector<Action> dls(Problem& problem, int limit);
	std::vector<Action> dlsWrapper(Problem& problem);
	// a* 算法
	typedef int(*heuristicFunc)(std::vector<int>& state, std::vector<int>& goalState);
	std::vector<Action> aStar(Problem& problem, heuristicFunc heuristicFunc);
	std::vector<Action> aStarMisplace(Problem& problem);
	std::vector<Action> aStarManhattan(Problem& problem);
};

