#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <queue>
using namespace std;

map<int, set<int>> roads;
set<int> phos;  //perhaps a 2d arrary would be faster
int length[100000];
int N, M;

void buildTree()
{
    for (int i = 0; i < M; i++)
    {
        int n;
        cin >> n;
        phos.insert(n);
    }
    for (int i = 1; i < N; i++) //since in a spanning tree there are N-1 roads
    {
        int a, b;
        cin >> a >> b;
        roads[a].insert(b);
        roads[b].insert(a);
    }
}

int farNode = 0, maxDistance = 0; //the index of one of the furthest leaf, and the distance
//从任意一个phos节点开始走，dfs找最远的leaf，顺便把非phos的路删掉
bool cut(int previous, int current, int distance)
{
    if (roads.at(current).size() > 1 || *roads.at(current).begin() != previous) //if this is not a leaf
    {
        bool noPhos = true; //no subtree of this node has phos
        for (auto &next : set<int>(roads[current]))
            if (next != previous && cut(current, next, distance + 1)) //if next subtree is completely useless
                noPhos = false;

        if (noPhos) //which means all subtrees have been cut
        {
            if (phos.count(current) == 0) //useless leaf
            {
                roads.erase(current);
                roads.at(previous).erase(current);
                return false;
            }
            else
            {
                if (distance > maxDistance)
                {
                    farNode = current;
                    maxDistance = distance;
                }
                return true;
            }
        }
    }
    else
    {
        if (phos.count(current) == 0) //useless leaf
        {
            roads.erase(current);
            roads.at(previous).erase(current);
            return false;
        }
        else
        {
            if (distance > maxDistance)
            {
                farNode = current;
                maxDistance = distance;
            }
            return true;
        }
    }
    return true;
}

//dfs find the longest path in the tree
void findFar(int previous = -1, int current = farNode, int distance = 0)
{
    for (auto &next : roads[current])
        if (next != previous)
            findFar(current, next, distance+1);

    if (distance > maxDistance)
        maxDistance = distance;
}
//cout the total length of roads
int count()
{
    int totalDistance = 0;
    for (auto &i : roads)
        totalDistance += i.second.size();
    
    //every road would be count twice, so no need to *2;
    totalDistance -= maxDistance;
    return totalDistance;
}

int main()
{
    cin.tie(0);cin.sync_with_stdio(0);
    cin >> N >> M;
    buildTree();
    cut(-1, *phos.begin(), 0);
    findFar();
    cout << count();

    return 0;
}
