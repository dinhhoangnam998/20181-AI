#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <stack>
#include <list>
#include <vector>
#include <cmath>
#include <string>
using namespace std;


typedef struct Node
{
	int x, y;
	Node* parent;
	string msg;

	int g, h2, f2, f4;
	float h1, f1, f3;
} *NodeS;



class mycomparison
{
	int mode;
public:
	mycomparison(int modeparam=0)
	{
		mode=modeparam;
	}

	bool operator() (NodeS agr1, NodeS agr2)
	{
		switch (mode)
		{
			case 0: {
				return agr1->f1 > agr2->f1;
				break;
			}

			case 1: {
				return agr1->f2 > agr2->f2;
				break;
			}

			case 2: {
				return agr1->f3 > agr2->f3;
				break;
			}

			case 3: {
				return agr1->f4 > agr2-> f4;
				break;
			}

			default: {
				cout << "invalid modaparam";
				return false;
			}
		}
	}
};

typedef priority_queue <NodeS, vector<NodeS>, mycomparison> mypq_type;

bool** allocateMaze(int height, int width);
bool** allocateEmptyMatrix(int height, int width);
void printMatrix(bool** matrix, int height, int width, string matrixName="noName");
int gx(NodeS p);
float h1x(NodeS p, NodeS goal);
int h2x(NodeS p, NodeS goal);
void caculateCost(NodeS p, NodeS goal);
NodeS makeNode(int x, int y);
NodeS makeGoalNode(int x, int y);
NodeS makeStartNode(int x, int y, NodeS goal);
void expandNodeU(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L);
void expandNodeD(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L);
void expandNodeL(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L);
void expandNodeR(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L);
void expandNode(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L);
bool checkGoal(NodeS p, NodeS goal);
NodeS solution(NodeS start, NodeS goal, NodeS reachFlag, bool** maze, bool** close, int height, int width, mypq_type& pq, list<NodeS>& L);
void trace(NodeS reachFlag, stack<NodeS>& S);
void printPath(stack<NodeS> S);
void printAction(stack<NodeS> S);
void printCost(stack<NodeS> S, int modeparam);
void printResult(stack<NodeS> S, int modeparam);
void freeMemory(list<NodeS>& L);
void AStart (bool** maze, int height, int width, int x1, int y1, int x2, int y2, int modeparam=0);
