//CCC 2017 Senior S3
#include <vector>
#include <array>
#include <iostream>

using namespace std;

const int maxn = 2000 + 10;
int N;
int L[maxn] = {}; //the number of board of every length
int F[maxn * 2] = {};

void cnt()
{
	for (int n = 1; n <= 2000; n++)
	{
		if (L[n])
		{
			if (L[n] > 1)
			{
				F[n * 2] += L[n] / 2;
			}
			for (int s = n+1; s <= 2000; s++)
			{
				if (L[s])
					F[n + s] += min(L[n], L[s]);
			}
		}	
	}
}

int nmax = 1, maxl = 0;
void search()
{
	
	for (int i = 1; i <= 4000; i++)
	{
		if (F[i] > maxl)
		{
			maxl = F[i];
			nmax = 1;
		}
		else if (F[i] == maxl)
		{
			nmax++;
		}
	}
	
}


int main()
{
	std::cin.sync_with_stdio(0);
	std::cin.tie(0);
	cin >> N;
	int i;
	while (N--)
	{
		cin >> i;
		L[i]++;
	}
	cnt();
	search();
	cout << maxl << " " << nmax;


	
    return 0;
}

