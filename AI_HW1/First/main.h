#pragma once

#include "GLUT.h"
#include "Node.h"
#include "graph.h"

#include <vector>
#include <queue>
#include <math.h>
#include <time.h>
#include <iostream>

// Consts
const int MSZ = 100;
const int W = 600, H = 600; // Window's width and height
const int WINDOW_POSX = 450, WINDOW_POSY = 140; // Start position of the window when entering to the app
const int NUM_EDGES = 3000, NUM_NODES = 1000;

// Some members
bool start_bfs = false;

Graph graph;
vector<Node*> graysFromStart; // The current unchecked nodes, starting from the start node
vector<Node*> graysFromTarget; // The current unchecked nodes, starting from the target node

// Prototypes
void idle();
void displayGraph();
void menu(int choice);
void init();

void createGraph();
void displayGraph();

double distance(int node1, int node2);
void setPath(Node* node);
Edge* isOverlap(const vector<Node*>& graysFromStart, const vector<Node*>& graysFromTarget);

void drawNode(int node1_idx, int node2_idx);
void drawEdge(const Edge& pe);
void drawGraph();

vector<Node*> BFSIteration(vector<Node*> grays);
void BidirectionalBFS();




