#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <numeric>
#include <queue>
#include <sstream>
#include <queue>
#include <functional>
#include <sstream>
#include<cassert>
#include <cmath>
#include <chrono>
#include<cstring>

using namespace std;

#define ll long long int

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        if (hash1 != hash2) {
            return hash1 ^ hash2;              
        }
          return hash1;
    }
};

int nodes = 0;
 
/* check for path from s to t in
  residual graph. fills parent to store path */
int bfs(vector<vector<int>> & rGraph, int s, int t, vector<int> & parent)
{
    vector<bool> visited(nodes, false);
 
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
 
        for (int v=0; v<nodes; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    return (visited[t] == true);
}
 
// find all reachable nodes from s
void dfs(vector<vector<int>> & rGraph, int s, vector<bool> & visited)
{
    visited[s] = true;
    for (int i = 0; i < nodes; i++)
       if (rGraph[s][i] && !visited[i])
           dfs(rGraph, i, visited);
}
 
vector<vector<int>> minCut(vector<vector<int>> & graph, int s, int t)
{
    int u, v;
 
    vector<vector<int>> rGraph = graph;
 
    vector<int> parent(nodes);
 
    // while there is a path from source to sink
    while (bfs(rGraph, s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
    }
 
    // Flow is maximum now, find vertices reachable from s
    vector<bool> visited(nodes, false);
    dfs(rGraph, s, visited);
    vector<vector<int>> edge_count;
    for (int i = 0; i < nodes; i++)
      for (int j = 0; j < nodes; j++)
         if (visited[i] && !visited[j] && graph[i][j])
         	edge_count.push_back({i, j});
    return edge_count;
}

int main() {
	vector<string> vs;
	string line;
	while(getline(cin, line))
		vs.push_back(line);

	nodes = 0;
	unordered_map<string, int> id;
	for(string & s : vs) {
		string key = s.substr(0, 3);
		if(id.find(key) == id.end()) {
			id[key] = nodes++;
		}


		string curr;
		for(int i = 5; i < s.size(); ++i) {
			if(i % 4 != 0)
				curr.push_back(s[i]);
			if(i % 4 == 3) {
				if(id.find(curr) == id.end()) {
					id[curr] = nodes++;
				}
				curr = "";
			}
		}
	}

	vector<vector<int>> graph(nodes, vector<int>(nodes, 0));

	for(string & s : vs) {
		string key = s.substr(0, 3);


		string curr;
		for(int i = 5; i < s.size(); ++i) {
			if(i % 4 != 0)
				curr.push_back(s[i]);
			if(i % 4 == 3) {
				graph[id[curr]][id[key]] = 1;
				graph[id[key]][id[curr]] = 1;
				curr = "";
			}
		}
	}

	vector<vector<int>> cut;
	int s, t;
	for(s = 1; s < nodes; ++s) {
		cut = minCut(graph, s, 0);
		if(cut.size() == 3)
			break;
	}
	cout << "S: " << s << ", T: " << t << '\n';
	cout << "Cuts:\n";
	for(int i = 0; i < 3; ++i) {
		cout << cut[i][0] << '-' << cut[i][1] << '\n';
	}
	cout << '\n';

	// modify graph
	for(int i = 0; i < 3; ++i) {
		graph[cut[i][0]][cut[i][1]] = 0;
		graph[cut[i][1]][cut[i][0]] = 0;
	}

	vector<bool> vis_from_s(nodes, false);
	dfs(graph, s, vis_from_s);
	int n1 = accumulate(vis_from_s.begin(), vis_from_s.end(), 0);
	int n2 = nodes - n1;
	int prod = n1 * n2;
	cout << "p1: " << prod << '\n';


	return 0;
}