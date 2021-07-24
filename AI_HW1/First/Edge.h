#pragma once

class Edge
{
public:
	Edge(int node1, int node2);

	int getNode1() const		{ return this->node1; }
	int getNode2() const		{ return this->node2; }

private:
	int node1;
	int node2;
};

