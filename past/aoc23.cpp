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

vector<vector<int>> dirs = {
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0}
};

unordered_map<char, int> down = {
	{'>', 0},
	{'<', 1},
	{'v', 2},
	{'^', 3} 
};

bool is_valid(vector<string> & vs, int &i, int & j) {
	if (i < 0 || j < 0 || i >= vs.size() || j >= vs[0].size() || vs[i][j] == '#')
		return false;
	return true;
}

int bfs(vector<string> & vs, unordered_set<pair<int, int>, hash_pair> & vis, int i, int j, bool p2) {
	int mx = 0;
	vis.insert({i, j});
	for(int d = 0; d < dirs.size(); ++d) {
		if(!p2 && vs[i][j] != '.' && d != down[vs[i][j]])
			continue;
		vector<int> & dir = dirs[d];
		int r = i + dir[0];
		int c = j + dir[1];
		if(vis.find({r, c}) != vis.end())
			continue;
		if(!is_valid(vs, r, c))
			continue;
		mx = max(mx, bfs(vs, vis, r, c, p2));
	}
	vis.erase(vis.find({i, j}));
	return mx + 1;
}


struct TreeNode {
	int dist;
	int row;
	int col;
	vector<TreeNode*> child;
	TreeNode(int r, int c, int d) {
		dist = d;
		row = r;
		col = c;
	}
};

TreeNode * find_next(vector<string> & vs, unordered_set<pair<int, int>, hash_pair> &vis, int i, int j) {
	int dist = 1;
	vector<int> direction;
	int count;
	while(1) {
		vis.insert({i, j});
		count = 0;
		for(int d = 0; d < dirs.size(); ++d) {
			vector<int> & dir = dirs[d];
			int r = i + dir[0];
			int c = j + dir[1];
			if(vis.find({r, c}) != vis.end() || !is_valid(vs, r, c))
				continue;
			++count;
			direction = dir; 
		}
		if(count != 1) {
			TreeNode * ret = new TreeNode(i, j, dist);
			return ret;
		}
		i += direction[0];
		j += direction[1];
		++dist;
	}
	return nullptr;
}

TreeNode * find_next_bfs(vector<string> & vs, unordered_set<pair<int, int>, hash_pair> &vis, int i, int j) {
	int dist = 1;
	vector<int> direction;
	int count;
	while(1) {
		vis.insert({i, j});
		count = 0;
		for(int d = 0; d < dirs.size(); ++d) {
			vector<int> & dir = dirs[d];
			int r = i + dir[0];
			int c = j + dir[1];
			if(vis.find({r, c}) != vis.end() || !is_valid(vs, r, c))
				continue;
			++count;
			direction = dir; 
		}
		if(count != 1) {
			TreeNode * ret = new TreeNode(i, j, dist);
			return ret;
		}
		i += direction[0];
		j += direction[1];
		++dist;
	}
	return nullptr;
}


int bfs_mod(vector<string> & vs, unordered_set<pair<int, int>, hash_pair> vis, int i, int j) {
	vis.insert({i, j});
	int mx = 0;
	for(int d = 0; d < dirs.size(); ++d) {
		vector<int> & dir = dirs[d];
		int r = i + dir[0];
		int c = j + dir[1];
		if(vis.find({r, c}) != vis.end())
			continue;
		if(!is_valid(vs, r, c))
			continue;

		TreeNode * next = find_next_bfs(vs, vis, r, c);

		//cout << next->row << ' ' << next->col << ' ' << next->dist << '\n';
		mx = max(mx, bfs_mod(vs, vis, next->row, next->col) + next->dist);
	}
	return mx;
}

TreeNode * construct_node(vector<string> & vs, int r, int c) {
	TreeNode * start = new TreeNode(r, c, 0);
	queue<TreeNode*> q;
	q.push(start);

	unordered_set<pair<int, int>, hash_pair> vis;
	vis.insert({r, c});
	while(!q.empty()) {
		TreeNode* curr = q.front();
		q.pop();

		int i = curr->row;
		int j = curr->col;
		for(int d = 0; d < dirs.size(); ++d) {
			vector<int> & dir = dirs[d];
			int r = i + dir[0];
			int c = j + dir[1];
			if(vis.find({r, c}) != vis.end() || !is_valid(vs, r, c))
				continue;

			TreeNode * next = find_next(vs, vis, r, c);
			curr->child.push_back(next);
			q.push(next);
		}
	}
	return start;
}

int bfs2(vector<vector<pair<int, int>>> & adj, vector<bool> & vis, int root) {
	int mx = 0;
	for(auto & a : adj[root]) {
		if(vis[a.first]) 
			continue;
		vis[a.first] = 1;
		mx = max(mx, bfs2(adj, vis, a.first) + a.second);
		vis[a.first] = 0;
	}
	return mx;
}

int coord_to_idx(vector<string> & vs, int & i, int & j) {
	return (i * vs[0].size() + j);
}

void merge_three(vector<vector<pair<int, int>>> & adj, int f, int m, int s) {
	int dist = adj[m][0].second + adj[m][1].second;
	adj[m].clear();
	adj[f].erase(find_if(adj[f].begin(), adj[f].end(), [&](const auto & a) {
		return a.first == m;
	}));
	adj[s].erase(find_if(adj[s].begin(), adj[s].end(), [&](const auto & a) {
		return a.first == m;
	}));
	adj[f].push_back({s, dist});
	adj[s].push_back({f, dist});
}

bool condense(vector<vector<pair<int, int>>> & adj) {
	bool found = false;
	for(int i = 0; i < adj.size(); ++i) {
		if(adj[i].size() == 2) {
			found = 1;
			merge_three(adj, adj[i][0].first, i, adj[i][1].first);
		}
	}

	return found;
}

int main() {
	vector<string> vs;
	string line;
	while(getline(cin, line)) {
		vs.push_back(line);
	}

	unordered_set<pair<int, int>, hash_pair> vis;
	cout << "part 1: " << bfs(vs, vis, 0, 1, false) - 1 << '\n'; //dont count origin

	//cout << bfs_mod(vs, vis, 0, 1);
	int m = vs.size(), n = vs[0].size();
	int tot = m * n;
	vector<vector<pair<int, int>>> adj(tot);
	auto construct_adj = [&]() {
		queue<pair<int, int>> q;
		q.push({0, 1});
		unordered_set<pair<int, int>, hash_pair> visited;

		while(!q.empty()) {
			int r = q.front().first;
			int c = q.front().second;
			q.pop();

			if(visited.find({r, c}) != visited.end())
				continue;
			visited.insert({r, c});
			for(int d = 0; d < dirs.size(); ++d) {
				vector<int> & dir = dirs[d];
				int i = r + dir[0];
				int j = c + dir[1];
				if(!is_valid(vs, i, j))
					continue;
				int c1 = coord_to_idx(vs, r, c);
				int c2 = coord_to_idx(vs, i, j);
				adj[c1].push_back({c2, 1});
				q.push({i, j});
			}
		}
		return;
	};

	construct_adj();

	// for(int i = 0; i < tot; ++i) {
	// 	if(i % n == 0) {
	// 		cout << '\n';
	// 	}
	// 	cout << adj[i].size() << ' ';

	// }

	// cout << "\n\n";
	cout << "Nodes pre-condense: " << count_if(adj.begin(), adj.end(), [](const auto & a) {
		return !a.empty();
	}) << '\n';

	while(condense(adj));

	// 	for(int i = 0; i < tot; ++i) {
	// 	if(i % n == 0) {
	// 		cout << '\n';
	// 	}
	// 	cout << adj[i].size() << ' ';
	// }
	// cout << "\n\n";

	cout << "Nodes post-consdense: " << count_if(adj.begin(), adj.end(), [](const auto & a) {
		return !a.empty();
	}) << '\n';

	vector<bool> vis2(tot, false);
	cout << "part 2: " << bfs2(adj, vis2, 1);

	return 0;
}