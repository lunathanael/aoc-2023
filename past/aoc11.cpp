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

using namespace std;

#define ll long long int

ll part1() {
	ll sum = 0;
	int m, n;
	cin >> m >> n;

	vector<string> s(m);
	for(int i = 0; i < m; ++i) {
		cin >> s[i];
	}

	vector<vector<int>> v(m, vector<int>(2));
	int dist = 0;
	for(int i = 0; i < m; ++i) {
		int c = count_if(s[i].begin(), s[i].end(), [](const auto & a) {
			return a != '.';
		});
		if(c == 0) dist += 1;
		v[i][0] = c;
		v[i][1]=++dist;
	}

	vector<vector<int>> v1(n, vector<int>(2));
	dist = 0;
	for(int i = 0; i < n; ++i) {
		int c = 0;
		for(int j = 0; j < m; ++j) {
			c += s[j][i] != '.';
		}
		if(c == 0) dist += 1;
		v1[i][0] = c;
		v1[i][1]=++dist;
	}

	for(int i = 0; i < m; ++i) {
		for(int j = i + 1; j < m; ++j) {
			sum += (v[j][1] - v[i][1]) * v[i][0] * v[j][0];
		}
	}
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j) {
			sum += (v1[j][1] - v1[i][1]) * v1[i][0] * v1[j][0];
		}
	}
	return sum;
}

ll part2() {
	ll sum = 0;
	int m, n;
	cin >> m >> n;

	vector<string> s(m);
	for(int i = 0; i < m; ++i) {
		cin >> s[i];
	}

	vector<vector<int>> v(m, vector<int>(2));
	int dist = 0;
	for(int i = 0; i < m; ++i) {
		int c = count_if(s[i].begin(), s[i].end(), [](const auto & a) {
			return a != '.';
		});
		if(c == 0) dist += 1000000 - 1;
		v[i][0] = c;
		v[i][1]=++dist;
	}

	vector<vector<int>> v1(n, vector<int>(2));
	dist = 0;
	for(int i = 0; i < n; ++i) {
		int c = 0;
		for(int j = 0; j < m; ++j) {
			c += s[j][i] != '.';
		}
		if(c == 0) dist += 1000000 - 1;
		v1[i][0] = c;
		v1[i][1]=++dist;
	}

	for(int i = 0; i < m; ++i) {
		for(int j = i + 1; j < m; ++j) {
			sum += (v[j][1] - v[i][1]) * v[i][0] * v[j][0];
		}
	}
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j) {
			sum += (v1[j][1] - v1[i][1]) * v1[i][0] * v1[j][0];
		}
	}
	return sum;
}

int main() {

	cout << part2();
	return 0;
}