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


bool collide(vector<vector<int>> & b1, vector<vector<int>> & b2) {
	    // If one square is to the left of the other
    if (b1[1][0] < b2[0][0] || b1[0][0] > b2[1][0])
        return false;

    // If one square is above the other
    if (b1[1][1] < b2[0][1] || b1[0][1] > b2[1][1])
        return false;

    return true; // Squares overlap
}

int fall(vector<vector<vector<int>>> &bricks) {
	int fallen = 0;
	for(int i = 0; i < bricks.size(); ++i) {
		vector<vector<int>> & brick = bricks[i];
		int y = 1;
		for(int j = 0; j < i; ++j) {
			if(collide(brick, bricks[j])) {
				y = max(y,bricks[j][1][2] + 1);
			}
		}
		if(y < brick[0][2]) {
			++fallen;
			int dist = brick[0][2] - y;
			brick[0][2] -= dist;
			brick[1][2] -= dist;
		}
	}
	return fallen;
}

bool supported_by(vector<vector<int>> & a, vector<vector<int>> & b) {
	// is a supported by b
	return collide(a, b) && (b[1][2] + 1 == a[0][2]);
}

void bfs(vector<vector<int>> &adj, vector<bool> & gone, int & idx) {
	gone[idx] = 1;
	// find target branches
	for(int i = 0; i < adj.size(); ++i) {
		if(gone[i])
			continue;
		if(adj[idx][i] == 1) {
			bool supported = false;
			// find supports
			for(int j = 0; j < adj.size(); ++j) {
				if(adj[i][j] == -1 && gone[j] == 0) {
					supported = true;
					break;
				}
			}
			if(supported == false) {
				bfs(adj, gone, i);
			}
		}
	}
}

bool all_gone(vector<int> & supports, vector<bool> & gone) {
	for(int & i : supports) {
		if(gone[i] == false) 
			return false;
	}
	return true;
}

void bfs_helper(vector<vector<int>> &parents, vector<vector<int>> & children, vector<bool> & gone, int & idx) {
	gone[idx] = 1;
	for(int & child : children[idx]) {
		if(gone[child] == false && all_gone(parents[child], gone)) {
			bfs_helper(parents, children, gone, child);
		}
	}
}

int new_bfs(vector<vector<int>> &parents, vector<vector<int>>&children, int & idx) {
	vector<bool> gone(parents.size(), false);
	bfs_helper(parents, children, gone, idx);
	return count(gone.begin(), gone.end(), true) - 1; // remove original
}


int main() {
	auto start = std::chrono::steady_clock::now( );
	vector<string> vs;
	string line;
	while(getline(cin, line)) {
		vs.push_back(line);
	}

	vector<vector<vector<int>>> bricks;
	for(string & s : vs) {
		s.push_back(',');
		vector<int> v;
		int n = 0, i = 0;
		while(i < s.size()) {
			if(s[i] == ',' || s[i] == '~') {
				v.push_back(n);
				n = 0;
			}
			else {
				n = n * 10 + (s[i] - '0');
			}
			++i;
		}
		bricks.push_back({{v[0], v[1], v[2]}, {v[3], v[4], v[5]}});
	}

	sort(bricks.begin(), bricks.end(), [](const auto & a, const auto & b) {
		return a[0][2] < b[0][2];
	});

	fall(bricks);

	cout << "Finished falling, begin search!\n";

	// tree
	int n = bricks.size();
	vector<vector<int>> parents(n, vector<int>());
	vector<vector<int>> children(n, vector<int>());
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			if(i == j) 
				continue;
			if(supported_by(bricks[j], bricks[i])) {
				parents[j].push_back(i);
				children[i].push_back(j);
			}
		}
	}
	int can = 0;
	ll p2 = 0;
	for(int i = 0; i < bricks.size(); ++i) {
		int fallen = new_bfs(parents, children, i);

		if(fallen == 0) {
			++can;
		}
		p2 += fallen;
	}
	cout << can << '\n';
	cout << p2 << '\n';


	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ) - start );
	cout << "\nFinished in " << elapsed.count() << "ms" << '\n'; 
	return 0;
}