#pragma once

#include <vector>
#include "Edge.h"

using namespace std;

class Node
{
public:
	/* Types:
		SPACE = 0;
		WALL = 1;
		START = 2;
		TARGET = 3;
		BLACK = 4; // Visited
		GRAY = 5; // Casing (shape scope) = The unvisited current test nodes
		PATH = 6; // Shortest path from start node to target node
	*/
	enum Type { SPACE, WALL, START, TARGET, BLACK, GRAY, PATH };
	Node(int row, int column, int type);

	void setRow(int line);
	void setColumn(int col);
	void setType(int value);
	void setParent(Node* p);
	void addAdjacentEdgeToVector(Edge* pe);

	int getRow() const						{ return this->row; }
	int getColumn() const					{ return this->column; }
	int getType() const						{ return this->type; }
	Node* getParent() const					{ return this->parent; }
	vector<Edge*> getAdjacentEdges() const	{ return this->adjacentEdges; }

private:
	int row;
	int column;
	int type;
	Node* parent;
	vector<Edge*> adjacentEdges;

	friend class main;
};

