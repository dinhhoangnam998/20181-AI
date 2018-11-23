#include <stdio.h>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

bool** allocateMaze(int height, int width)
{
	bool** temp;
    temp = new bool*[height];
    for(int i = 0; i < height; i++)
        temp[i] = new bool[width];

    for( int i = 0; i <= height - 1; i++)
        for(int j = 0; j <= width-1; j++)
      // ??    temp[i][j]= 0;

    return temp;

}


bool** allocateEmptyMatrix(int height, int width)
{
	bool** temp;
    temp = new bool*[height];
    for(int i = 0; i < m; i++)
        temp[i] = new bool[width];

    for( int i = 0; i <= height - 1; i++)
        for(int j = 0; j <= width-1; j++)
            temp[i][j]= 0;

    return temp;

}


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
		}
	}
}

typedef priority_queue <NodeS, vector<NodeS>, mycomparison> mypq_type;


int gx(NodeS p)
{
	if(p == NULL)
		return 0;
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

void caculateCost(NodeS p, NodeS goal)
{
	p->g = gx(p);
	p->h1 = h1x(p, goal);
	p->h2 = h2x(p, goal);
	
	p->f1 = p->h1;
	p->f2 = p->h2;
	p->f3 = p->g + p->h1;
	p->f4 = p->g + p->h2;
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
	temp->f1 = 0.0;
	temp->f2 = 0;
	temp->f3 = 0.0;
	temp->f4 = 0;

	return temp;
}

NodeS makeGoalNode(int x, int y)
{
	NodeS goal = makeNode(x, y);
	goal->msg = "Goal";
	return goal;

}

NodeS makeStartNode(int x, int y, NodeS goal)
{
	NodeS start = makeNode(x, y);
	start->parent = NULL;
	start->msg = "Start:";
	
	caculateCost(start, goal);

	return start;
}


void expandNodeU(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L)
{
	if( p->x == 0 || maze[p->x - 1][p->y] == 1 || close[p->x -1][p->y] == true )
		return;

	NodeS newNode = makeNode(p->x - 1, p->y);
	newNode->parent = p;
	newNode->msg = "U";

	caculateCost(newNode, goal);

	pq.push(newNode);
	L.push(newNode);

}


void expandNodeD(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L)
{
	if( p->x == height - 1 || a[p->x + 1][p->y] == 1 || close[p->x + 1][p->y] == true )
		return;

	NodeS newNode = makeNode(p->x + 1, p->y);
	newNode->parent = p;
	newNode->msg = "D";

	caculateCost(newNode, goal);

	pq.push(newNode);
	L.push(newNode);

}


void expandNodeL(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L)
{
	if( p->y == 0 || maze[p->x][p->y - 1] == 1 || close[p->x][p-> y - 1] == true )
		return;

	NodeS newNode = makeNode(p->x, p->y - 1);
	newNode->parent = p;
	newNode->msg = "L";

	caculateCost(newNode, goal);

	pq.push(newNode);
	L.push(newNode);

}


void expandNodeR(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L)
{
	if( p->y == width - 1 || maze[p->x][p->y + 1] == 1 || close[p->x][p->y + 1] == true )
		return;

	NodeS newNode = makeNode(p->x, p->y + 1);
	newNode->parent = p;
	newNode->msg = "R";

	caculateCost(newNode, goal);

	pq.push(newNode);
	L.push(newNode);

}


void expandNode(NodeS p, bool** maze, bool** close, int height, int width, NodeS goal, mypq_type& pq, list<NodeS>& L)
{
	expandNodeU(p, maze, close, height, width, goal, pq, L);
	expandNodeR(p, maze, close, height, width, goal, pq, L);
	expandNodeD(p, maze, close, height, width, goal, pq, L);
	expandNodeL(p, maze, close, height, width, goal, pq, L);
}

bool checkGoal(NodeS p, NodeS goal)
{
	return ( p->x == goal->x && p->y == goal->y );
}

NodeS solution(NodeS start, NodeS goal, NodeS reachFlag, bool** maze, bool** close, int height, int width, mypq_type& pq, list<NodeS>& L)
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
			expandNode(cur, maze, close, height, width, goal, pq, L);
		}
	}

	return NULL;
}

void trace(NodeS reachFlag)
{
	if( reachFlag == NULL )
	{
		cout << "\nfailure";
	}

	else
	{
		stack<NodeS> S;
		NodeS it = reachFlag;

		while( it != NULL )
		{
			S.push(it);
			it = it->parent;
		}

		while ( !S.empty() )
		{
			NodeS it = S.top(); S.pop();
			cout << "<" << it->x << "," << it->y << "> --> ";
		}
		cout << "(y)!";
	}
}

void AStart (bool** maze, int height, int width, int x1, int y1, int x2, int y2, int mode=0)
{
	NodeS goal = makeGoalNode(x2, y2);
	NodeS start = makeStartNode(x1, y1, goal);
	NodeS reachFlag = NULL;

	mypq_type pq(mycomparison(mode));
	list<NodeS> L;

	bool** close = allocateEmptyMatrix(height, width);

	reach = solution(start, goal, reachFlag, maze, close, height, width, pq, L);
	trace(reach);
}

int main()
{
	cout << "hello world!";
	return 0;
}