//#define TEST
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstring>
#define maxn 100
#define goAll(x,y,step) go(x, y - 1, step);go(x, y + 1, step);go(x - 1, y, step);go(x + 1, y, step);
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
				if (steps[i][k] == -1)
					cout << " x";
				else
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
			steps[i][k1] = -1;
		else if (grid[i][k1] == 'W')
			break;
		else	//The other ones(S,C,UDLR)can all be seen through
			continue;
	for (int k1 = k - 1; ; k1--)
		if (grid[i][k1] == '.')
			steps[i][k1] = -1;
		else if (grid[i][k1] == 'W')
			break;
		else
			continue;
	for (int i1 = i + 1; ; i1++)
		if (grid[i1][k] == '.')
			steps[i1][k] = -1;
		else if (grid[i1][k] == 'W')
			break;
		else
			continue;
	for (int i1 = i - 1; ; i1--)
		if (grid[i1][k] == '.')
			steps[i1][k] = -1;
		else if (grid[i1][k] == 'W')
			break;
		else
			continue;
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
			steps[x][y] = -1;
			return;
		}
		else if (grid[i][k] == 'W')
			break;
		else
			continue;
	for (int i = x, k = y - 1;; k--)
		if (grid[i][k] == 'C')
		{
			steps[x][y] = -1;
			return;
		}
		else if (grid[i][k] == 'W')
			break;
		else
			continue;
	for (int i = x + 1, k = y;; i++)
		if (grid[i][k] == 'C')
		{
			steps[x][y] = -1;
			return;
		}
		else if (grid[i][k] == 'W')
			break;
		else
			continue;
	for (int i = x - 1, k = y;; i--)
		if (grid[i][k] == 'C')
		{
			steps[x][y] = -1;
			return;
		}
		else if (grid[i][k] == 'W')
			break;
		else
			continue;
}


/*
Recursively go through the whole grid
*/
bool stuck = false;
void go(int x, int y, int step)
{
	char tgrid = grid[x][y];
	if (tgrid == '.')
	{
		stuck = false;
		//if current step is less than the marked step, or this cell hasn't been asscessed
		if (steps[x][y] > step || steps[x][y] == 0)
		{	
			steps[x][y] = step;
			goAll(x, y, step + 1);
		}
		return;
	}
	else	
	{
		//W and C always go here because they are all -1
		if (stuck && steps[x][y] <= step && steps[x][y] != 0)
		{
			stuck = false;
			return;
		}
		
		stuck = true;	
		steps[x][y] = step;
		switch (tgrid)
		{
		case 'U':
			go(x - 1, y, step);
			break;
		case 'D':
			go(x + 1, y, step);
			break;
		case 'L':
			go(x, y - 1, step);
			break;
		case 'R':
			go(x, y + 1, step);
			break;
		default: break;
		}
	}
	return;
}


int main()
{
	cin.tie(0); cin.sync_with_stdio(0);
	cin >> N >> M;

	//mark steps to all 0
	for (int i = 0; i < N; i++)
		memset(steps[i], 0, M);

	char a;
	int x, y;	//the position of S
	for (int i = 0; i < N; i++)
		for (int k = 0; k < M; k++)
		{
			cin >> a;
			if (a == 'S') { x = i; y = k; }
			grid[i][k] = a;
			if (a == 'W' || a == 'C')	//mark all the walls and cameras to -1
				steps[i][k] = -1;
		}

	//clear all the places under cameras
	clearCamera(x, y);
#ifdef TEST
	print(0);
	print(1);
#endif
	if (steps[x][y] == -1)	//if S is already under a camera...
	{
		for (int i = 1; i < N - 1; i++)
			for (int k = 1; k < M - 1; k++)
				if (grid[i][k] == '.')
					cout << -1 << "\n";
		return 0;
	}
	steps[x][y] = -1;
	goAll(x, y, 1);

	for (int i = 1; i < N - 1; i++)
		for (int k = 1; k < M - 1; k++)
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
