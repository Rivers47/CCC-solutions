//#define TEST
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstring>
#define maxn 100

using namespace std;
int N, M;
char grid[maxn][maxn];
int steps[maxn][maxn];

/*
分析：Camera可以往四个方向看无限远，但不能穿墙
思路：
一个数组用来放地图，
另一个用来放步数，（初始全0，非通道或传送带标-1
先把所有Camera周围标-1
走的时候传送带标成-1，走进传送带时设置一个标志变量，
如果走到空格子了把标志变量设为否，如果再次走到走过的传送带时仍然为真的话，就是死循环
走完后对比地图输出所有数
*/

void ini()
{
	for (int i = 0; i < N; i++)
		memset(steps[i], 0, M);
}
#ifdef TEST
void print(int c)
{
	if (c)
		for (int i = 0; i < N; i++)
		{
			for (int k = 0; k < M; k++)
			{
				if (steps[i][k] == -1)
					cout << " x";
				else
					printf("%2d", steps[i][k]);
			}
			cout << '\n';
		}
	else
		for (int i = 0; i < N; i++)
		{
			for (int k = 0; k < M; k++)
			{
				cout << grid[i][k];
			}
			cout << '\n';
		}
	cout << '\n';
}
#endif
void markCamera(int i, int k)//上下左右四个循环
{

	for (int k1 = k + 1; ; k1++)
	{
		if (grid[i][k1] == '.')
			steps[i][k1] = -1;
		else if (grid[i][k1] == 'W')
			break;
		else	//其他的(S,C,UDLR)都可以穿过
			continue;
	}
	for (int k1 = k - 1; ; k1--)
	{
		if (grid[i][k1] == '.')
		{
			steps[i][k1] = -1;
		}
		else if (grid[i][k1] == 'W')
			break;
		else	//其他的(S,C,UDLR)都可以穿
			continue;
	}
	for (int i1 = i + 1; ; i1++)
	{
		if (grid[i1][k] == '.')
		{
			steps[i1][k] = -1;
		}
		else if (grid[i1][k] == 'W')
			break;
		else	//其他的(S,C,UDLR)都可以穿过
			continue;
	}
	for (int i1 = i - 1; ; i1--)
	{
		if (grid[i1][k] == '.')
		{
			steps[i1][k] = -1;
		}
		else if (grid[i1][k] == 'W')
			break;
		else	//其他的(S,C,UDLR)都可以穿过
			continue;
	}
}

void clearCamera(int x, int y)
{
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < M; k++)
		{
			if (grid[i][k] == 'C')
				markCamera(i, k);
		}
	}

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

bool stuck = false;
void go1(int x, int y, int step);
void go(int x, int y, int step)	//递归走格子
{
	
	char tgrid = grid[x][y];
	if (tgrid == '.')
	{
		if (steps[x][y] == 0 || steps[x][y] > step)	//如果应该走
		{
			stuck = false;
			steps[x][y] = step;
			go1(x, y, step + 1);
		}
		stuck = false;
		return;
	}
	else
	{
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
//第一次call的时候step=1
void go1(int x, int y, int step)
{
	go(x, y - 1, step);
	go(x, y + 1, step);
	go(x - 1, y, step);
	go(x + 1, y, step);
}


int main()
{
	cin.tie(0); cin.sync_with_stdio(0);
	cin >> N >> M;
	ini();	//mark steps to all 0
	char a;
	int x, y;	//the position of S
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < M; k++)
		{
			cin >> a;
			if (a == 'S')
			{
				x = i;
				y = k;
			}
			grid[i][k] = a;
			if (a == 'W' || a == 'C')
				steps[i][k] = -1;
		}
	}
	clearCamera(x, y);
#ifdef TEST
	print(0);
	print(1);
#endif
	if (steps[x][y] == -1)	//if it's already under a camera...
	{
		for (int i = 1; i < N - 1; i++)
			for (int k = 1; k < M - 1; k++)
				if (grid[i][k] == '.')
					cout << -1 << "\n";
		return 0;
	}
	steps[x][y] = -1;
	go1(x, y, 1);

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
