#include "Search.h"
#include <ranges>
namespace rng = std::ranges;
namespace search
{
	Node childNode(Problem& problem, Node& parent, Action action, int stepCost)
	{
		return Node(&parent, action, parent.cost + stepCost, problem.result(parent.state, action));
	}

	std::vector<Action> getSolution(Node node)
	{
		std::vector<Action> result;
		while (node.parent != NULL)
		{
			result.insert(result.begin(), node.action);
			node = *node.parent;
		}

		return result;
	}

	bool inSet(std::set<std::vector<int>>& collection, std::vector<int>& state)
	{
		return collection.find(state) != collection.end();
	}

	bool inMap(std::map<std::vector<int>, Node*>& map, std::vector<int>& state)
	{
		return map.find(state) != map.end();
	}

	void updateNode(std::priority_queue<Node*, std::vector<Node*>, Node::cmp>& frontier, Node* sameStateNode, Node* child)
	{
		sameStateNode->action = child->action;
		sameStateNode->cost = child->cost;
		sameStateNode->parent = child->parent;
		std::vector<Node*> nodes;
		while (!frontier.empty())
		{
			nodes.push_back(frontier.top());
			frontier.pop();
		}
		for (Node* node : nodes)
		{
			frontier.push(node);
		}
	}

	/*function BREADTH-FIRST-SEARCH(problem) returns a solution node or failure
		node←NODE(problem.INITIAL)
		if problem.IS-GOAL(node.STATE) then return node
		frontier←a FIFO queue, with node as an element
		reached← {problem.INITIAL}
		while not IS-EMPTY(frontier) do
		node←POP(frontier)
		for each child in EXPAND(problem, node) do
		s←child.STATE
		if problem.IS-GOAL(s) then return child
		if s is not in reached then
		add s to reached
		add child to frontier
		return failure
		function UNIFORM-COST-SEARCH(problem) returns a solution node, or failure
		return BEST-FIRST-SEARCH(problem, PATH-COST)*/

		// Reference: Figure 3.11 Breadth-first search on a graph.
	std::vector<Action> bfs(Problem& problem)
	{
		Node* initNode = new Node(NULL, Action::FAILURE, 0, problem.initState);
		problem.nodePtrs.insert(initNode);

		if (problem.isGoal(initNode->state)) return std::vector<Action>();

		std::queue<Node*> frontier;
		frontier.push(initNode);
		std::set<std::vector<int>> frontierSet;
		frontierSet.insert(initNode->state);
		std::set<std::vector<int>> explored;

		while (!frontier.empty())
		{
			Node* current = frontier.front();

			frontier.pop();
			frontierSet.erase(current->state);
			explored.insert(current->state);

			for (Action action : problem.getValidActions(current->state))
			{
				Node* child = new Node(childNode(problem, *current, action, 1));
				problem.nodePtrs.insert(child);
				if (!inSet(frontierSet, child->state) && !inSet(explored, child->state))
				{
					if (problem.isGoal(child->state)) return getSolution(*child);
					frontier.push(child);
					frontierSet.insert(child->state);
				}
			}
		}

		return { Action::FAILURE };
	}

	std::vector<Action> recursiveDLS(Node& node, Problem& problem, int limit)
	{
		/*
		* Algorithm:
			function RECURSIVE-DLS(node, problem, limit ) returns a solution, or failure/cutoff
				if problem.GOAL-TEST(node.STATE) then return SOLUTION(node)
				else if limit = 0 then return cutoff
				else
					cutoff occurred?←false
					for each action in problem.ACTIONS(node.STATE) do
					child ←CHILD-NODE(problem, node, action)
					result ←RECURSIVE-DLS(child , problem, limit − 1)
					if result = cutoff then cutoff occurred?←true
					else if result != failure then return result
					if cutoff occurred? then return cutoff else return failure

		* Reference:
		* Figure 3.17 A recursive implementation of depth-limited tree search.
		*
		* Note:
		* 需要使用problem.freeMemory(nodePtr)管理内存
		*/
		if (problem.isGoal(node.state)) return getSolution(node);
		else if (limit == 0) return { Action::CUTOFF };
		else {
			bool cutoff_occurred = false;
			for (auto action : problem.getValidActions(node.state)) {
				auto* child = new Node(childNode(problem, node, action, 1));
				problem.nodePtrs.insert(child);
				auto result = recursiveDLS(*child, problem, limit - 1);
				if (result[0] == Action::CUTOFF)
					cutoff_occurred = true;
				else if (result[0] != Action::FAILURE)
					return result;
				std::cout << problem.nodePtrs.size() << "\n";
				problem.freeMemory(child);
			}
			if (cutoff_occurred)
				return { Action::CUTOFF };
			else
				return { Action::FAILURE };
		}
	}

	std::vector<Action> dls(Problem& problem, int limit)
	{
		Node initNode(NULL, Action::FAILURE, 0, problem.initState);
		return recursiveDLS(initNode, problem, limit);
	}

	std::vector<Action> dlsWrapper(Problem& problem)
	{
		return dls(problem, 10);
	}

	std::vector<Action> aStar(Problem& problem, heuristicFunc heuristicFunc)
	{
		/*
		* Algorithm:
			function HEURISTIC-SEARCH(problem) returns a solution, or failure
				node ←a node with STATE = problem.INITIAL-STATE, PATH-COST = 0
				frontier ←a priority queue ordered by PATH-COST, with node as the only element
				explored ←an empty set
				loop do
					if EMPTY?( frontier) then return failure
					node←POP( frontier ) // chooses the lowest-cost node in frontier
					if problem.GOAL - TEST(node.STATE) then return SOLUTION(node)
					add node.STATE to explored
					for each action in problem.ACTIONS(node.STATE) do
						child ←CHILD - NODE(problem, node, action)
						child.cost += heuristicFunc(child.state, problem.goalState)
						if child.STATE is not in explored or frontier then
							frontier ←INSERT(child, frontier)
						else if child.STATE is in frontier with higher PATH - COST then
							replace that frontier node with child

		* Note:
		* The above algorithm is identical to the UNIFORM-COST-SEARCH described in Figure 3.14 except that we update the cost according to an heuristic function.
		* You should use a priority queue to maintain the frontier.
			std::priority_queue<Node*, std::vector<Node*>, Node::cmp> frontier;
		* You may need a map whose key is a state and value is a pointer to node to efficiently find whether a child.STATE is not in frontier or in frontier with higher path cost.
			std::map<std::vector<int>, Node*> stateNodePtrMap;
		*
		* Reference:
		* Figure 3.14 Uniform-cost search on a graph.
		*/
		static auto get_container = []<class Adapter>(Adapter & a)->typename Adapter::container_type& {
			struct hack : Adapter {
				static typename Adapter::container_type& get(Adapter& a) { return a.* & hack::c; }
			};
			return hack::get(a);
		};

		Node* initNode = new Node(NULL, Action::FAILURE, 0, problem.initState);
		problem.nodePtrs.insert(initNode);

		std::priority_queue<Node*, std::vector<Node*>, Node::cmp> frontier;
		auto& underlying = get_container(frontier);
		std::map<std::vector<int>, Node*> stateNodePtrMap;
		frontier.push(initNode);
		stateNodePtrMap[initNode->state] = initNode;
		std::set<std::vector<int>> explored;

		while (true)
		{
			if (frontier.empty()) return { Action::FAILURE };
			Node* node = frontier.top();
			frontier.pop();
			stateNodePtrMap.erase(node->state);
			if (problem.isGoal(node->state)) return getSolution(*node);
			explored.insert(node->state);

			for (Action action : problem.getValidActions(node->state))
			{
				Node* child = new Node(childNode(problem, *node, action, 1));
				problem.nodePtrs.insert(child);
				child->cost += heuristicFunc(child->state, problem.goalState);

				auto res = stateNodePtrMap.find(child->state);
				if (res == stateNodePtrMap.end() && !inSet(explored, child->state)) {
					frontier.push(child);
					stateNodePtrMap[child->state] = child;
				}
				else if (res != stateNodePtrMap.end() && child->cost > res->second->cost) {
					*res->second = *child;
					stateNodePtrMap.erase(res);
					stateNodePtrMap[child->state] = child;
					rng::make_heap(underlying, Node::cmp());
				}
			}
		}

		return { Action::FAILURE };
	}
	std::vector<Action> aStarMisplace(Problem& problem)
	{
		return aStar(problem, heuristic::misplace);
	}
	std::vector<Action> aStarManhattan(Problem& problem)
	{
		return aStar(problem, heuristic::manhattan);
	}
}
