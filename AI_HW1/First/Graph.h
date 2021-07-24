#pragma once

#include <vector>
#include "Node.h"
#include "Edge.h"

using namespace std;

class Graph
{
private:
	vector<Edge*> edges;
	vector<Node*> nodes;

public:
	void addNode(Node *pn);
	void addEdge(Edge *pe);

	Node* getNode(int i) const		{ return this->nodes[i]; }
	Edge* getEdge(int i) const		{ return this->edges[i]; }
	vector<Edge*> getEdges() const	{ return this->edges; }
	vector<Node*> getNodes() const	{ return this->nodes; }
};

