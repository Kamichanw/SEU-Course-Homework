#include "Node.h"
#include <iostream>

Node::Node(Node* parent, Action action, int cost, std::vector<int> state)
{
	this->parent = parent;
	this->action = action;
	this->cost = cost;
	this->state = state;
}

Node::Node()
{
	this->parent = NULL;
	this->action = Action::FAILURE;
	this->cost = -1;
	this->state = std::vector<int>();
}

Node::~Node()
{
}

bool Node::cmp::operator()(Node* a, Node* b) const
{
	return a->cost > b->cost;
}
