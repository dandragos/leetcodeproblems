#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_NODES = 500;
const int INF = 0xffffff;

int capacity[MAX_NODES][MAX_NODES];
int flow[MAX_NODES][MAX_NODES];
vector<int> graph[MAX_NODES];
int parent[MAX_NODES];
bool visited[MAX_NODES];
int nodeCount, maxFlow, minCapacity;

int indegree[MAX_NODES];
int outdegree[MAX_NODES];

queue<int> bfsQueue;
int N_DEST;

ifstream fin("harta.in");
ofstream fout("harta.out");


bool bfs()
{
    bfsQueue.push(1);
    memset(visited, false, sizeof(visited));
    visited[1] = true;

    while (!bfsQueue.empty())
    {
        int current = bfsQueue.front();
        bfsQueue.pop();

        if (current == N_DEST)
            continue;

        for (int i = 0; i < graph[current].size(); ++i)
        {
            int neighbor = graph[current][i];
            if (capacity[current][neighbor] == flow[current][neighbor] || visited[neighbor])
                continue;

            visited[neighbor] = true;
            bfsQueue.push(neighbor);
            parent[neighbor] = current;
        }
    }
    return visited[N_DEST];
}

void solve()
{
    fin >> nodeCount;
    N_DEST = nodeCount * 2 + 2;

    for (int i = 1; i <= nodeCount; ++i)
    {
	    fin>>outdegree[i]>>indegree[i];
    }

    for (int i = 1; i <= nodeCount; ++i)
    {
        capacity[1][i + 1] = outdegree[i];
        graph[1].push_back(i + 1);
        graph[i + 1].push_back(1);

        capacity[1+ nodeCount + i][N_DEST] = indegree[i];
    	graph[i + 1 + nodeCount].push_back(N_DEST);
        graph[N_DEST].push_back(i + 1 + nodeCount);

    }

    for (int i = 1; i <= nodeCount; ++i)
    {
        for (int j = i + 1; j <= nodeCount; ++j)
        {
            capacity[i + 1][j + nodeCount + 1] = 1;
            graph[i + 1].push_back(j + nodeCount + 1);
            graph[j + nodeCount + 1].push_back(i + 1);
            capacity[j + 1][i + nodeCount + 1] = 1;
            graph[j + 1].push_back(i + nodeCount + 1);
            graph[i + nodeCount + 1].push_back(j + 1);
        }
    }

    maxFlow = 0;
    bfs();

    while (bfs())
    {
        for (int i = 0; i < graph[N_DEST ].size(); ++i)
        {
            int current = graph[N_DEST ][i];
            if (capacity[current][N_DEST ] == flow[current][N_DEST ] || !visited[current])
                continue;

            minCapacity = INF;
            parent[N_DEST ] = current;
            for (int i = N_DEST ; i != 1; i = parent[i])
                minCapacity = min(minCapacity, capacity[parent[i]][i] - flow[parent[i]][i]);

            if (minCapacity == 0)
                continue;

            for (int i = N_DEST ; i != 1; i = parent[i])
            {
                flow[parent[i]][i] += minCapacity;
                flow[i][parent[i]] -= minCapacity;
            }
            maxFlow += minCapacity;
        }
    }

    vector<pair<int, int>> resultEdges;
    for (int i = 1; i <= nodeCount; ++i)
    {
        for (int j = 1; j <= nodeCount; ++j)
        {
            if (i != j && flow[i + 1][j + nodeCount + 1] == 1)
            {
                resultEdges.push_back({ i, j });
            }
        }
    }

    fout << resultEdges.size() << "\n";
    for (auto edge : resultEdges)
    {
        fout << edge.first << " " << edge.second << "\n";
    }
}

int main()
{
    

    solve();

    fin.close();
    fout.close();

    return 0;
}