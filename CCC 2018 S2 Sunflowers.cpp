#define NDEBUG
#include <cassert>
#include <iostream>
using namespace std;

int N;
int table[101][101];
void rotateOut(int angle)
{
	switch (angle)
	{
	case 0:
		for (int i = 1; i <= N; i++)
		{
			for (int k = 1; k <= N; k++)
				cout << table[i][k] << " ";
			cout << "\n";
		}
		break;
	case 1:
		for (int i = 1; i <= N; i++)
		{
			for (int k = N; k >= 1; k--)
				cout << table[k][i] << " ";
			cout << "\n";
		}
		break;
	case 2:
		for (int i = N; i >= 1; i--)
		{
			for (int k = 1; k <= N; k++)
				cout << table[k][i] << " ";
			cout << "\n";
		}
		break;
	case 3:
		for (int i = N; i >= 1; i--)
		{
			for (int k = N; k >= 1; k--)
				cout << table[i][k] << " ";
			cout << "\n";
		}
		break;
	default:
		break;
	}
}

int main()
{
	cin.tie(0); cin.sync_with_stdio(0);

	cin >> N;
	int a;
	for (int i = 1; i <= N; i++)
		for (int k = 1; k <= N; k++)
		{
			cin >> a;
			table[i][k] = a;
		}

	int angle;
	int corners[4] = { table[1][1],table[N][1],table[1][N],table[N][N] };
	int first = 10000000000;

	for (int i = 0; i < 4; i++)
		if (first > corners[i])
		{
			first = corners[i];
			angle = i;
		}

	rotateOut(angle);
	return 0;
}
