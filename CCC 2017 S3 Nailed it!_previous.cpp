#include <iostream>
#include <algorithm>
#define itl 2000
using namespace std;


//the length of every board is the index
int board[2000 + 10];
//the length of every board combination is the index
int combLeng[4000 + 10];
int N;


void construct()
{
	for (int k = 1; k <= itl; k++)
	{
		combLeng[k * 2] += board[k] / 2;
		for (int i = k + 1; i <= itl; i++)
		{
			if (!board[i])
				continue;
			combLeng[i+k] += (board[i] < board[k]) ? board[i] : board[k];
		}
	}
}

void max(int& n, int& index)
{
	int maxl = 0;
	n = 1;
	int i = 1;	//i is the comb length
	for (; i <= 4000; i++)
	{
		if (combLeng[i] > maxl)
		{
			maxl = combLeng[i];
			n = 1;
			index = i;		
		}
		else if (combLeng[i] == maxl)
			n++;
	}
}

int main()
{
	cin.tie(0); cin.sync_with_stdio(0);

	cin >> N;
	while (N--)
	{
		int length;
		cin >> length;
		board[length]++;
	}
	construct();
	int n, l;
	max(n, l);
	cout << combLeng[l] << " " << n;

	return 0;
}
