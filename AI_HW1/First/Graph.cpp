#include "Graph.h"

void Graph::addNode(Node *pn)
{
	this->nodes.push_back(pn);
}

void Graph::addEdge(Edge *pe)
{
	this->edges.push_back(pe);
}
