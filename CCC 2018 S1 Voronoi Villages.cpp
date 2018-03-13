#include <iostream>
#include <algorithm>
#include <cstdio>;
using namespace std;

int main()
{
	cin.tie(0); cin.sync_with_stdio(0);
	int N; int a;
	int villages[100];
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> a;
		villages[i] = a;
	}
	sort(villages, villages + N);


	double neighbourhood[100];	//[i]表示第i和第i-1之间的
	for (int i = 1; i < N; i++)
		neighbourhood[i] = (double)(villages[i] + villages[i - 1]) / 2;

	double min = 10000000000000, current;
	for (int i = 1; i < N - 1; i++)
	{
		current = neighbourhood[i + 1] - neighbourhood[i];
		if (current < min)
			min = current;
	}
	printf("%.1f", min);
	return 0;
}
