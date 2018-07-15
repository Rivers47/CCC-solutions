//#define TEST
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define maxn 100

using namespace std;
int N, M;
char grid[maxn][maxn];
int steps[maxn][maxn];


#ifdef TEST

void print(int c)
{
	if (c)
		for (int i = 0; i < N; i++)
		{
			for (int k = 0; k < M; k++)
				//if (steps[i][k] == 0)
				//	cout << " x";
			//	else
					printf("%2d", steps[i][k]);
			cout << '\n';
		}
	else
		for (int i = 0; i < N; i++)
		{
			for (int k = 0; k < M; k++)
				cout << grid[i][k];
			cout << '\n';
		}
	cout << '\n';
}
#endif
void markCamera(int i, int k)//four loops for the four directions
{
	for (int k1 = k + 1; ; k1++)
		if (grid[i][k1] == '.')
			steps[i][k1] = 0;
		else if (grid[i][k1] == 'W')
			break;	//The other ones(S,C,UDLR)can all be seen through

	for (int k1 = k - 1; ; k1--)
		if (grid[i][k1] == '.')
			steps[i][k1] = 0;
		else if (grid[i][k1] == 'W')
			break;

	for (int i1 = i + 1; ; i1++)
		if (grid[i1][k] == '.')
			steps[i1][k] = 0;
		else if (grid[i1][k] == 'W')
			break;

	for (int i1 = i - 1; ; i1--)
		if (grid[i1][k] == '.')
			steps[i1][k] = 0;
		else if (grid[i1][k] == 'W')
			break;
}

void clearCamera(int x, int y)
{
	for (int i = 0; i < N; i++)
		for (int k = 0; k < M; k++)
			if (grid[i][k] == 'C')
				markCamera(i, k);

	//a special case when S is already under a camera
	for (int i = x, k = y + 1;; k++)
		if (grid[i][k] == 'C')
		{
			steps[x][y] = 0;
			return;
		}
		else if (grid[i][k] == 'W')
			break;

	for (int i = x, k = y - 1;; k--)
		if (grid[i][k] == 'C')
		{
			steps[x][y] = 0;
			return;
		}
		else if (grid[i][k] == 'W')
			break;

	for (int i = x + 1, k = y;; i++)
		if (grid[i][k] == 'C')
		{
			steps[x][y] = 0;
			return;
		}
		else if (grid[i][k] == 'W')
			break;

	for (int i = x - 1, k = y;; i--)
		if (grid[i][k] == 'C')
		{
			steps[x][y] = 0;
			return;
		}
		else if (grid[i][k] == 'W')
			break;
}

struct node
{
	int x, y;
	node(int x = 0, int y = 0, char type = 0) :x(x),y(y) {}
};
bool operator ==(const node& a, const node& b)
{
	return a.x == b.x && a.y == b.y;
}

//dir is marked 0-4 to represent the for directions
node walk(const node& u, int dir)
{
	switch (dir)
	{
	case 0:
		return node(u.x - 1, u.y); break;
	case 1:
		return node(u.x , u.y + 1); break;
	case 2:
		return node(u.x + 1, u.y); break;
	case 3:
		return node(u.x, u.y - 1); break;
	default: break;
	}
}

//enter a belt, return true if it lands in a new cell
bool walkThroughBelt(node& u)
{
	node v = u;
	for (;;)
	{
		switch (grid[v.x][v.y])
		{
		case 'U': v.x--; break;
		case 'R': v.y++; break;
		case 'D': v.x++; break;
		case 'L': v.y--; break;
		default: return false;
		}

		if (grid[v.x][v.y] == '.')
		{
			if (steps[v.x][v.y] >= 0)
				return false;
			else { u = v; return true; }
		}
		else if (steps[v.x][v.y] < 0)
		{
			steps[v.x][v.y] = 0;
			continue;
		}
		else
			return false;
	}
}

//BFS
void go(int x, int y)
{
	queue <node> Q;
	node u(x, y);
	steps[x][y] = 0;
	Q.push(u);

	while (!Q.empty())
	{
		u = Q.front(); Q.pop();
		for (int i = 0; i < 4; i++)
		{
			node v = walk(u, i);
			if (grid[v.x][v.y] == 'W' || grid[v.x][v.y] == 'C')
				continue;
			else
			{
				if (grid[v.x][v.y] == '.')
				{
					if(steps[v.x][v.y] < 0)
					{
						steps[v.x][v.y] = steps[u.x][u.y] + 1;
						Q.push(v);
					}
				}
				else if (walkThroughBelt(v))
				{
					steps[v.x][v.y] = steps[u.x][u.y] + 1;
					Q.push(v);;
				}
			}
		}
	}
}


int main()
{
	cin.tie(0); cin.sync_with_stdio(0);
	cin >> N >> M;

	//mark steps to all -1
	for (int i = 0; i < N; i++)
	{
		memset(steps[i], -1, sizeof(steps[i]));
	}

	char a;
	int x, y;	//the position of S
	for (int i = 0; i < N; i++)
		for (int k = 0; k < M; k++)
		{
			cin >> a;
			if (a == 'S') { x = i; y = k; }
			grid[i][k] = a;
			if (a == 'W' || a == 'C')	//mark all the walls and cameras to 0
				steps[i][k] = 0;
		}

	//clear all the places under cameras
	clearCamera(x, y);
#ifdef TEST
	print(0);
	print(1);
#endif
	if (steps[x][y] == 0)	//if S is already under a camera...
	{
		for (int i = 1; i < N - 1; i++)
			for (int k = 1; k < M - 1; k++)
				if (grid[i][k] == '.')
					cout << -1 << "\n";
		return 0;
	}

	go(x, y);

	//output result
	N--; M--;
	for (int i = 1; i < N; i++)
		for (int k = 1; k < M; k++)
			if (grid[i][k] == '.')
				if (steps[i][k])
					cout << steps[i][k] << "\n";
				else
					cout << -1 << "\n";

#ifdef TEST
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < M; k++)
			if (grid[i][k] != '.')
				printf("%2c", grid[i][k]);
			else if (steps[i][k] <= 0)
				cout << " X";
			else
				printf("%2d", steps[i][k]);
		cout << "\n";
	}
	cout << "\n\n\n";

	//append the right answer to the input file to generate a correct map
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < M; k++)
			if (grid[i][k] != '.')
				printf("%2c", grid[i][k]);
			else
			{
				int x;
				cin >> x;
				if (x != -1)
					printf("%2d", x);
				else
					cout << " X";
			}
		cout << "\n";
	}
#endif
	return 0;
}
