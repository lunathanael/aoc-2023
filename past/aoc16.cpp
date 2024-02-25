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

using namespace std;

#define ll long long int

unordered_map<string, string> ump = {
	{".u", "u"},{".d", "d"},{".r", "r"},{".l", "l"},
	{"/u", "r"},{"/d", "l"},{"/r", "u"},{"/l", "d"},
	{"\\u", "l"},{"\\d", "r"},{"\\r", "d"},{"\\l", "u"},
	{"-u", "lr"},{"-d", "lr"},{"-r", "r"},{"-l", "l"},
	{"|u", "u"},{"|d", "d"},{"|r", "ud"},{"|l", "ud"},
};

unordered_map<char, vector<int>> dirs = {
	{'l', {0, -1}}, {'r', {0, 1}}, {'u', {-1,0}}, {'d', {1, 0}}
};

int m, n;


void recursion(int r, int c, char dir, vector<string> & vs, vector<vector<string>> &ust) {
	if (r >= m || c >= n || r < 0 || c < 0) return;
	if (find(ust[r][c].begin(), ust[r][c].end(), dir) != ust[r][c].end()) {
		return;
	}
	ust[r][c].push_back(dir);
	string mir = string(1,vs[r][c]) + dir;
	for(char & ch : ump[mir]) {
		recursion(r + dirs[ch][0], c + dirs[ch][1], ch, vs, ust);
	}
}

int part1(int r, int c, char dir, vector<string>&vs) {
	vector<vector<string>> ust(m, vector<string>(n));
	recursion(r, c, dir, vs, ust);
	return accumulate(ust.begin(), ust.end(), 0, [](const auto & a, const auto & b) {
		return a + accumulate(b.begin(), b.end(), 0, [](const auto & x, const auto & y) {
			return x + !(y.empty());
		});
	});
}


int main() {

	vector<string> vs;
	string line;
	while(getline(cin, line)) {
		vs.push_back(line);
	}

	m = vs.size();
	n = vs[0].size();
	cout << part1(0, 0, 'r', vs) << '\n';

	int mx = 0;
	for(int i = 0; i < n; ++i) {
		mx = max(mx, max(part1(0, i, 'd', vs), part1(m-1, i, 'u', vs)));
	}
	for(int i = 0; i < m; ++i) {
		mx = max(mx, max(part1(i, 0, 'r', vs), part1(i, n-1, 'l', vs)));
	}
	cout << mx;
	return 0;
}