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
#include "data_type.h"
using namespace std;


extern vector <coordinate> path;   
extern vector <coordinate> visitHistory; 

bool** allocateMaze(int height, int width)
bool** allocateEmptyMatrix(int height, int width)
void printMatrix(bool** matrix, int height, int width)

typedef struct Node
{
    int x, y;
    Node* parent;
    string msg;

    int g;
    float h1;
    int h2;
    float f;
} *NodeS;

struct myComparator {
    bool operator() (NodeS arg1, NodeS arg2) {
        return arg1->f > arg2->f;
    }
};
typedef priority_queue<NodeS, vector<NodeS>, myComparator> mypq_type;
int gx(NodeS p)
float h1x(NodeS p, NodeS goal)
int h2x(NodeS p, NodeS goal)
void caculateCost(NodeS p, NodeS goal, int alpha = 1, int beta = 2, int mode = 1 )
NodeS makeNode(int x, int y)
NodeS makeGoalNode(int x, int y)
NodeS makeStartNode(int x, int y, NodeS goal, int alpha = 1, int beta = 2, int mode = 1 )
void expandNodeU(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L, int alpha = 1, int beta = 2, int mode = 1 )
void expandNodeD(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L, int alpha = 1, int beta = 2, int mode = 1 )
void expandNodeL(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L, int alpha = 1, int beta = 2, int mode = 1 )
void expandNodeR(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L, int alpha = 1, int beta = 2, int mode = 1 )
void expandNode(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L, int alpha = 1, int beta = 2, int mode = 1 )
bool checkGoal(NodeS p, NodeS goal)
NodeS solution(NodeS start, NodeS goal, NodeS reachFlag, bool** maze, bool** close, int height, int width, mypq_type& pq, list<NodeS>& L, int alpha = 1, int beta = 2, int mode = 1 )
void trace(NodeS reachFlag, stack<NodeS>& S)
void printPath(stack<NodeS> S)
void printAction(stack<NodeS> S)
void printCost(stack<NodeS> S)
void printResult(stack<NodeS> S)
void translate4Path(stack<NodeS> S)
void translate4visitHistory(list<NodeS>& L)
void freeMemory(list<NodeS>& L)
void AStart (bool** maze, int height, int width, int x1, int y1, int x2, int y2, int alpha = 1, int beta = 2, int mode = 1 )
