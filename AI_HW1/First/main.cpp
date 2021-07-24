#include "main.h"

using namespace std;

void init()
{
	srand(time(0)); // Initialize a pseudo randomizer
	glClearColor(1, 1, 1, 1); // Set background color
	createGraph(); // Set-up the graph
	glOrtho(-1, 1, -1, 1, -1, 1); // Define main axes
}

double distance(int node1, int node2)
{
	double x1, x2, y1, y2;

	x1 = graph.getNode(node1)->getColumn();
	x2 = graph.getNode(node2)->getColumn();

	y1 = graph.getNode(node1)->getRow();
	y2 = graph.getNode(node2)->getRow();

	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void createGraph()
{
	int nodei, nodej, k;
	Edge* pe1, * pe2;
	Node *pn;
	double current_distance;

	// Add random Nodes
	for (k = 0; k < NUM_NODES; k++)
	{
		pn = new Node(rand() % MSZ, rand() % MSZ, Node::Type::SPACE); // Node(int row, int column, int type)
		graph.addNode(pn);
	}

	// add random Edges
	for (k = 0; k < NUM_EDGES; k++)
	{
		do 
		{
			nodei = rand() % NUM_NODES;
			nodej = rand() % NUM_NODES;
			current_distance = distance(nodei, nodej);
		} while (current_distance > 7); // Rand values until the distance between the nodes is less than 7
		
		// Add edges to graph
		pe1 = new Edge(nodei, nodej); // nodei --> nodej
		graph.addEdge(pe1);
		pe2 = new Edge(nodej, nodei); // nodej --> nodei
		graph.addEdge(pe2);

		// Add edges to the edge vectors corresnponding with the current nodes
		graph.getNode(nodei)->addAdjacentEdgeToVector(pe1);
		graph.getNode(nodej)->addAdjacentEdgeToVector(pe2);
	}
	
	// Set the start and target nodes
	graph.getNode(0)->setType(Node::Type::START);
	graph.getNode(graph.getNodes().size() - 1)->setType(Node::Type::TARGET);
}

void drawNode(int node1_idx, int node2_idx)
{
	double size, x, y;

	size = 2.0 / MSZ; // 2.0 is the logical width and height of the window
	x = node2_idx * size - 1;
	y = node1_idx * size - 1;

	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x + size, y);
	glVertex2d(x + size, y + size);
	glVertex2d(x, y + size);

	glEnd();
}

void drawEdge(const Edge& pe)
{
	double x1, y1, x2, y2, size;

	size = 2.0 / MSZ;

	x1 = graph.getNode(pe.getNode1())->getColumn() * size - 1 + size / 2;
	y1 = graph.getNode(pe.getNode1())->getRow() * size - 1 + size / 2;
	x2 = graph.getNode(pe.getNode2())->getColumn() * size - 1 + size / 2;
	y2 = graph.getNode(pe.getNode2())->getRow() * size - 1 + size / 2;

	glColor3d(0, 0, 0); // Black line

	// Draw the line
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
}

void drawGraph()
{
	int i;

	for (i = 0; i < NUM_NODES; i++)
	{
		switch (graph.getNode(i)->getType())
		{
		case Node::Type::SPACE:
			glColor3d(0, 0, 0); // White
			break;
		case Node::Type::WALL:
			glColor3d(0, 0, 0); // Black
			break;
		case Node::Type::START:
			glColor3d(0.7, 0, 0); // Dark red
			break;
		case Node::Type::TARGET:
			glColor3d(0.7, 0, 0); // Dark red
			break;
		case Node::Type::GRAY:
			glColor3d(0, 0.9, 1); // Light blue
			break;
		case Node::Type::BLACK:
			glColor3d(0, 0.9, 1); // Light blue
			break;
		case Node::Type::PATH:
			glColor3d(1, 0.5, 0); // Light red
			break;
		}

		// Draw node
		drawNode(graph.getNode(i)->getRow(), graph.getNode(i)->getColumn());

		// Draw corresponding edges
		for (Edge* edge : graph.getNode(i)->getAdjacentEdges())
			drawEdge(*edge);
	}
}

void setPath(Node* node)
{
	// Sets PATH node types to all nodes from the given node to either the start node or the target one.
	
	while (node->getType() != Node::Type::START && node->getType() != Node::Type::TARGET)
	{
		node->setType(Node::Type::PATH);
		node = node->getParent();
	}
}

vector<Node*> BFSIteration(vector<Node*> grays)
{
	// Makes a BFS iteration according to the given gray colored nodes
	// and returns the new vector of gray nodes to check

	Node *current, *neighbor;

	if (grays.empty()) // There is no way from start node to target node as there is no nodes in the vector of the gray nodes
	{
		cout << "There is no path from start node to target node, please refresh the window and try again." << endl;
		start_bfs = false;
	}
	else
	{
		// Pop the current node from the vector of the gray nodes
		current = grays[0];
		grays.erase(grays.begin());

		// Check wether the current node is the target one or not 
		if(current->getType() == Node::Type::GRAY) // If yet unvisited
			current->setType(Node::Type::BLACK); // BLACK = visited

		// Go to the neighbor nodes by the adjacent edges and color them with GRAY,
		// as they are the next nodes to check
		for (Edge* edge : current->getAdjacentEdges())
		{
			neighbor = graph.getNode(edge->getNode2());
			if (neighbor->getType() == Node::Type::SPACE)
			{
				neighbor->setType(Node::Type::GRAY);
				neighbor->setParent(current);
				grays.push_back(neighbor);
			}
		}
	}

	return grays;
}

Edge* isOverlap(const vector<Node*>& graysFromStart, const vector<Node*>& graysFromTarget)
{
	// Checks if there is any overlap between the current nodes detected by the BFS algorithm from both sides start and target nodes
	// If found --> returns the overlapping edge, else returns nullptr 

	int nodeIndex_fromStart, nodeIndex_fromTarget;

	for (Node* gray_fromStart : graysFromStart)
	{
		for(Edge* edge_fromStart : gray_fromStart->getAdjacentEdges())
		{
			nodeIndex_fromStart = edge_fromStart->getNode1();
			for (Node* gray_fromTarget : graysFromTarget)
			{
				for (Edge* edge_fromTarget : gray_fromTarget->getAdjacentEdges())
				{
					nodeIndex_fromTarget = edge_fromTarget->getNode2();
					if (nodeIndex_fromStart == nodeIndex_fromTarget)
						return edge_fromTarget;
				}
			}
		}
	}

	return nullptr;
}

void BidirectionalBFS()
{
	Edge* overlappingEdge = isOverlap(graysFromStart, graysFromTarget);

	if(overlappingEdge)
	{
		setPath(graph.getNode(overlappingEdge->getNode1()));
		setPath(graph.getNode(overlappingEdge->getNode2()));
		cout << "A path was found by the algorithm, colored with light red" << endl;
		start_bfs = false;
	}
	else
	{
		graysFromTarget = BFSIteration(graysFromTarget);
		graysFromStart = BFSIteration(graysFromStart);
	}
}

void idle()
{
	if (start_bfs)
		BidirectionalBFS();

	glutPostRedisplay(); // Displaying
}

void displayGraph()
{
	glClear(GL_COLOR_BUFFER_BIT); // Cleaning frame buffer
	drawGraph();
	glutSwapBuffers(); // Showing the data from the frame buffer
}

void menu(int choice)
{
	switch (choice) 
	{
	case 1: // BidirectionalBFS
		start_bfs = true;
		graysFromStart.push_back(graph.getNode(0));
		graysFromTarget.push_back(graph.getNode(graph.getNodes().size() - 1));
		break;
	default:
		exit(1);
	}
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(WINDOW_POSX, WINDOW_POSY);
	glutCreateWindow("Exe1_BFS_Eylon");

	glutDisplayFunc(displayGraph); // displayGraph is the refreshing function for this program
	glutIdleFunc(idle); // idle is the function to call when nothing happens

	glutCreateMenu(menu);
	glutAddMenuEntry("Bidirectional BFS Search", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();

	glutMainLoop();
}