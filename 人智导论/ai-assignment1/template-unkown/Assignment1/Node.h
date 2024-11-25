#pragma once
#include <vector>
#include "Action.h"

/*
	��Ӧ����ͼ3.10���������ݽṹ��
*/
class Node
{
public:
	Node(Node* parent, Action action, int cost, std::vector<int> state);
	Node();
	~Node();

	Node* parent;
	Action action;
	int cost;
	std::vector<int> state;

	struct cmp
	{
		bool operator() (Node* a, Node* b) const;
	};
};

