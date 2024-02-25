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

using namespace std;

#define ll long long int

//							r       d       l        u
vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
//r rr rrr d dd ddd l ll lll u uu uuu

int m, n;

bool verify(int r, int c) {
	return r >= 0 && r < m && c >= 0 && c < n;
}

struct hashFunction 
{ 
  size_t operator()(const pair<int ,  
                    int> &x) const
  { 
    const auto hash1 = hash<int>{}(x.first);
    const auto hash2 = hash<int>{}(x.second);
    return hash1 ^ (hash2 << 1);  
  } 
}; 

auto comp = [](const std::vector<int>& a, const std::vector<int>& b) {
    return a[0] > b[0]; // This will create a min-heap based on the first element
};


int solve(vector<string> &vs, bool part2) {
	int min_dist = part2 ? 4 : 1;
	int max_dist = part2 ? 10 : 3;
	unordered_set<pair<int, int>, hashFunction> seen;
	unordered_map<pair<int, int>, int, hashFunction> costs;
	priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> pq(comp);
	pq.push({0, 0, 0, -1});

	while(!pq.empty()) {
		vector<int> ele = pq.top();
		pq.pop();
		int cost = ele[0], r = ele[1], c = ele[2], dd = ele[3];
		int ord = r * n + c;
		if(r == m-1 && c == n-1)
			return cost;
		if(seen.find({ord, dd}) != seen.end())
			continue;

		seen.insert({ord, dd});

		for (int i = 0; i < 4; ++i) {
			int cost_inc = 0;
			if(i == dd || (i%2) == (dd%2))
				continue;
			for (int j = 1; j <= max_dist; ++j) {
				int nr = r + dirs[i][0]*j;
				int nc = c + dirs[i][1]*j;
				if(verify(nr, nc)) {
					cost_inc += (vs[nr][nc] - '0');
					if(j < min_dist)
						continue;
					int new_cost = cost + cost_inc;
					if(costs.find({nr*n + nc, i}) != costs.end() && costs[{nr*n+nc, i}] <= new_cost) {
						continue;
					}
					costs[{nr*n+nc, i}] = new_cost;
					pq.push({new_cost, nr, nc, i});

				}
			}

		}
	}
	return -1;
}



int main() {

	vector<string> vs;
	string line;
	while(getline(cin, line)) {
		vs.push_back(line);
	}

	m = vs.size();
	n = vs[0].size();

	cout << solve(vs, false) << ' ' << solve(vs, true);


	return 0;
}