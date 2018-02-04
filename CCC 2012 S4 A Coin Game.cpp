//#define NDEBUG
#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

typedef unsigned int uint;
int n;
struct configuration
{
	//every four bits is a coin, every int can represent at most 8 coins
	vector<unsigned int> s;

	configuration(const configuration& x)
	{
		s = x.s;
	}
	configuration() { }

	//返回一个新的config,把t位上的硬币移到d位上，硬币的值在参数里给出
	configuration move(int t, int d, uint value) const
	{
		configuration c = *this;
		c.s[t] >>= 4;
		c.s[d] <<= 4;
		c.s[d] += value;
		return c;
	}
	bool operator == (const configuration& a)
	{
		return s == a.s；
	}
	bool operator < (const configuration& a) const
	{
		return s < a.s;
	}
};

uint getTop(const uint& stack);
void print(configuration c)
{
	bool zero = true;
	cout << "[";
	for (int i = 0; i < n; i++)
	{
		while (true)
		{
			int k = getTop(c.s[i]);
			if (k) zero = false;
			if (!k && zero) { cout << k; break; }
			else if (!k) break;
			c.s[i] >>= 4;
			cout << k;

		}
		cout << ",";
	}
	cout << "] ";
}

int generateSub(const configuration& root);
set<configuration> occured;
queue<configuration> q;
configuration dest;
int bfs(configuration& root)
{
	q.push(root);
	int number = 1, depth = 0, nextnumber = 0;

	while (!q.empty())
	{
		configuration c = q.front(); q.pop(); number--;
#ifdef NDEBUG 
		print(c);
#endif
		if (c == dest) { return depth; }
		nextnumber += generateSub(c);	//往队列里添加当前组合的可能分支
		if (number == 0)
		{
			depth++; number = nextnumber; nextnumber = 0;
#ifdef NDEBUG 
			cout << "\n" << depth;
#endif
		}
	}
	return -1;
}

//低位数在上面
uint getTop(const uint& stack)
{
	return stack & 15; //取得最后四个bits
}

//检查set里有没有c，如果没有就放进set和queue里，返回结果
int add(configuration& c)
{
	if (occured.insert(c).second)
	{
		q.push(c);
		return 1;
	}
	return 0;
}

//生成root的所有不重复的子结点，返回子结点的数量
int generateSub(const configuration& root)
{
	configuration c;
	int number = 0;
	uint i1 = getTop(root.s[0]);
	uint i2 = getTop(root.s[1]);
	if (i1 && ((i1 < i2) || i2 == 0))
	{
		c = root.move(0, 1, i1);
		number += add(c);
	}
	i1 = getTop(root.s[n - 1]);
	i2 = getTop(root.s[n - 2]);
	if (i1 && ((i1 < i2) || i2 == 0))
	{
		c = root.move(n - 1, n - 2, i1);
		number += add(c);
	}


	for (int i = 1; i < n - 1; i++)
	{
		uint current = getTop(root.s[i]);
		uint previous = getTop(root.s[i - 1]);
		uint next = getTop(root.s[i + 1]);

		if (current)
		{
			if (current < previous || previous == 0)
			{
				c = root.move(i, i - 1, current);
				number += add(c);
			}
			if (current < next || next == 0)
			{
				c = root.move(i, i + 1, current);
				number += add(c);
			}
		}
		if (next == 0)
			i++;
	}
	return number;
}



int main()
{
	cin.tie(0); cin.sync_with_stdio(0);
	while (cin >> n && n)
	{
		occured.clear();
		q = {};
		dest.s.clear();

		for (int i = 1; i <= n; i++)
			dest.s.push_back(i);

		uint p; configuration root;
		for (int i = 0; i < n; i++)
		{
			cin >> p;
			root.s.push_back(p);
		}
		
		n = bfs(root);
		if (n >= 0)
			cout << n << "\n";
		else
			cout << "IMPOSSIBLE\n";
	}
	return 0;
}
