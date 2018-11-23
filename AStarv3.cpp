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
{
    srand(time(NULL));
    bool** temp;
    temp = new bool*[height];
    for(int i = 0; i < height; i++)
        temp[i] = new bool[width];

    for( int i = 0; i <= height - 1; i++)
        for(int j = 0; j <= width-1; j++)
           temp[i][j]= rand()%2;

    return temp;

}


bool** allocateEmptyMatrix(int height, int width)
{
    bool** temp;
    temp = new bool*[height];
    for(int i = 0; i < height; i++)
        temp[i] = new bool[width];

    for( int i = 0; i <= height - 1; i++)
        for(int j = 0; j <= width-1; j++)
            temp[i][j]= 0;

    return temp;

}

void printMatrix(bool** matrix, int height, int width)
{
    for( int i = 0; i < height; i++)
    {
        for( int j = 0; j < width; j++)
        {
            printf("%5d",matrix[i][j]);
        }

        cout << endl;
    }
}


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
{
    if(p == NULL)
    {
        cout << "can't caculate gx because NodeS p == null";
        return 0;
    }
    else
    {
        NodeS parent = p->parent;
        if(parent == NULL)
            return 0;
        else
            return parent->g + 1;
    }
}

float h1x(NodeS p, NodeS goal)
{
    return sqrt( (p->x - goal->x)*(p->x - goal->x) + (p->y - goal->y)*(p->y - goal->y) );
}


int h2x(NodeS p, NodeS goal)
{
    return ( abs(p->x - goal->x) + abs(p->y - goal->y) );
}

void caculateCost(NodeS p, NodeS goal, int alpha = 1, int beta = 2, int mode = 1 )
{
    p->g = gx(p);
    p->h1 = h1x(p, goal);
    p->h2 = h2x(p, goal);

    if(mode == 1)
    {
        p->f = alpha*(p->g) + beta*(p->h1);
    }
    else if(mode == 2)
    {
        p->f = alpha*(p->g) + beta*(p->h2);
    }
}

NodeS makeNode(int x, int y)
{
    NodeS temp = new Node;
    temp->x = x;
    temp->y = y;
    temp->parent = NULL;
    temp->msg = "";

    temp->g = 0;
    temp->h1 = 0.0;
    temp->h2 = 0;
    temp->f = 0.0;

    return temp;
}

NodeS makeGoalNode(int x, int y)
{
    NodeS goal = makeNode(x, y);
    goal->msg = "Goal";
    return goal;

}

NodeS makeStartNode(int x, int y, NodeS goal, int alpha = 1, int beta = 2, int mode = 1 )
{
    NodeS start = makeNode(x, y);
    start->parent = NULL;
    start->msg = "Start";

    caculateCost(start, goal, alpha, beta, mode);

    return start;
}


void expandNodeU(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L, int alpha = 1, int beta = 2, int mode = 1 )
{
    if( p->x == 0 || maze[p->x - 1][p->y] == 1 || close[p->x -1][p->y] == true )
        return;

    NodeS newNode = makeNode(p->x - 1, p->y);
    newNode->parent = p;
    newNode->msg = "U";

    caculateCost(newNode, goal, alpha, beta, mode);

    pq.push(newNode);
    L.push_back(newNode);

}


void expandNodeD(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L, int alpha = 1, int beta = 2, int mode = 1 )
{
    if( p->x == height - 1 || maze[p->x + 1][p->y] == 1 || close[p->x + 1][p->y] == true )
        return;

    NodeS newNode = makeNode(p->x + 1, p->y);
    newNode->parent = p;
    newNode->msg = "D";

    caculateCost(newNode, goal, alpha, beta, mode);

    pq.push(newNode);
    L.push_back(newNode);

}


void expandNodeL(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L, int alpha = 1, int beta = 2, int mode = 1 )
{
    if( p->y == 0 || maze[p->x][p->y - 1] == 1 || close[p->x][p-> y - 1] == true )
        return;

    NodeS newNode = makeNode(p->x, p->y - 1);
    newNode->parent = p;
    newNode->msg = "L";

    caculateCost(newNode, goal, alpha, beta, mode);

    pq.push(newNode);
    L.push_back(newNode);

}


void expandNodeR(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L, int alpha = 1, int beta = 2, int mode = 1 )
{
    if( p->y == width - 1 || maze[p->x][p->y + 1] == 1 || close[p->x][p->y + 1] == true )
        return;

    NodeS newNode = makeNode(p->x, p->y + 1);
    newNode->parent = p;
    newNode->msg = "R";

    caculateCost(newNode, goal, alpha, beta, mode);

    pq.push(newNode);
    L.push_back(newNode);

}


void expandNode(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L, int alpha = 1, int beta = 2, int mode = 1 )
{
    expandNodeU(p, maze, close, height, width, goal, pq, L, alpha, beta, mode);
    expandNodeR(p, maze, close, height, width, goal, pq, L, alpha, beta, mode);
    expandNodeD(p, maze, close, height, width, goal, pq, L, alpha, beta, mode);
    expandNodeL(p, maze, close, height, width, goal, pq, L, alpha, beta, mode);
}

bool checkGoal(NodeS p, NodeS goal)
{
    return ( p->x == goal->x && p->y == goal->y );
}

NodeS solution(NodeS start, NodeS goal, NodeS reachFlag, bool** maze, bool** close, int height, int width, mypq_type& pq, list<NodeS>& L, int alpha = 1, int beta = 2, int mode = 1 )
{
    pq.push(start);

    while( !pq.empty() )
    {
        NodeS cur = pq.top();
        pq.pop();

        close[cur->x][cur->y] = true;

        if( checkGoal(cur, goal) )
        {
            reachFlag = cur;
            return reachFlag;
        }

        else
        {
            expandNode(cur, maze, close, height, width, goal, pq, L, alpha, beta, mode);
        }
    }

    return NULL;
}


void trace(NodeS reachFlag, stack<NodeS>& S)
{
    if( reachFlag == NULL)
        return;
    else
    {
        NodeS it = reachFlag;
        while( it != NULL)
        {
            S.push(it);
            it = it->parent;
        }
    }
}

void printPath(stack<NodeS> S)
{
    if (S.empty()) 
    return;
    
    cout << "\n\n\n*********************Solution:********************* \n";
        cout << "Start:";
        while ( !S.empty() )
        {
            NodeS it = S.top(); S.pop();
            cout << "<" << it->x << "," << it->y << "> --> ";
        }
        cout << "\b\b\b\b\b:Goal!\n";

}

void printAction(stack<NodeS> S)
{
    if (S.empty()) 
        return;
    
    cout << "Start:";
    S.pop();
        
    while( !S.empty() )
    {
    
        NodeS it = S.top(); S.pop();

        cout << "       " << it->msg << "  ";
    }
    cout << endl;
}

void printCost(stack<NodeS> S)
{
    if(S.empty())
        return;
    else
    {
        cout << "Cost: ";

        while (!S.empty())
        {
            NodeS it = S.top(); S.pop();
            printf(" %3.2f     ", it->f);
        }
    }
}

void printResult(stack<NodeS> S)
{
    if( S.empty() )
    {
        cout << "failure";
        return;
    }
    else
    {
        printPath(S);
        printAction(S);
        printCost(S);

    }
}


void translate4Path(stack<NodeS> S)
{
	if( S.empty() )
		return;
	
	path.clear();

	coordinate temp;
	NodeS it;

	while( !S.empty() )
	{
		it = S.top(); S.pop();
		temp.first = it->x;
		temp.second = it->y;
		path.push_back(temp);
	}
	

}

void translate4visitHistory(list<NodeS>& L)
{
	visitHistory.clear();
	
	NodeS n;
	coordinate c;
	list<NodeS>::iterator it;
	
	for(it = L.begin(); it != L.end(); ++it)
	{
		n = *it;
		c.first = n->x;
		c.second = n->y;
		visitHistory.push_back(c);
	}
}


void freeMemory(list<NodeS>& L)
{
    list<NodeS>::iterator it;
    for(it = L.begin(); it != L.end(); it++)
    {
        delete *it;
    }

    //free array and matrix///
}

void AStart (bool** maze, int height, int width, int x1, int y1, int x2, int y2, int alpha = 1, int beta = 2, int mode = 1 )
{

    NodeS goal = makeGoalNode(x2, y2);
    NodeS start = makeStartNode(x1, y1, goal, alpha, beta, mode);
    NodeS reachFlag = NULL;

    mypq_type pq;
    list<NodeS> L;
    stack<NodeS> S;

    bool** close = allocateEmptyMatrix(height, width);

    reachFlag = solution(start, goal, reachFlag, maze, close, height, width, pq, L, alpha, beta, mode);
    trace(reachFlag, S);
    printResult(S);
    translate4Path(S);
    translate4visitHistory(L);
    freeMemory(L);
}

int main()
{

    int height = 10, width = 10;
    int x1 = 0, y1 = 0, x2 = 2, y2 = 2;
    int mode = 2;
    bool** maze = allocateMaze(height, width);
    bool** mazeempty= allocateEmptyMatrix(height, width);
    printMatrix(maze, height, width);
    
    AStart(mazeempty, height, width, x1, y1, x2, y2, 1, 5, 1);
    cout << "\nhello world!";
    return 0;
}


