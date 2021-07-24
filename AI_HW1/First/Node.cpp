#include "Node.h"

#include <stdio.h>

Node::Node(int row, int column, int type)
{
	this->row = row;
	this->column = column;
	this->type = type;
	this->parent = nullptr;
}

void Node::setParent(Node* p)					{ this->parent = p; }
void Node::setType( int value)					{ this->type = value; }
void Node::setRow(int line)						{ this->row = line; }
void Node::setColumn(int col)					{ this->column = col; }
void Node::addAdjacentEdgeToVector(Edge* pe)	{ this->adjacentEdges.push_back(pe); }