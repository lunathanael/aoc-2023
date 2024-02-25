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

using namespace std;

#define ll long long int

int lines = 1000;

int dfs(string &s, vector<int> &v, int i, int j) {
	if(j == v.size()) {
		while(i < s.size() && s[i++] != '#');
		return i == s.size();
	}
	if(i == s.size()) return 0;


	if(s[i] == '?') {
		int one = dfs(s, v, i+1, j);


		for(int a = 0; a < v[j]; ++a) {
			if(i == s.size() || s[i++] == '.') return one;
		}
		if((i == s.size() || s[i++] == '#')) return one;

		return dfs(s, v, i, j+1) + one;
	}

	if (s[i] == '.') return dfs(s, v, i+1, j);


	for(int a = 0; a < v[j]; ++a) {
		if(i == s.size() || s[i++] == '.') return 0;
	}
	if((i == s.size() || s[i++] == '#')) return 0;
	return dfs(s, v, i, j+1);
}

ll dfs2(string &s, vector<int> &v, int i, int j, vector<vector<ll>> & dp) {
	if(j == v.size()) {
		while(i < s.size() && s[i++] != '#');
		return i == s.size();
	}
	if(i == s.size()) return 0;
	if(dp[i][j] != -1) return dp[i][j];
	int oi = i, oj = j;


	if(s[i] == '?') {
		ll one = dfs2(s, v, i+1, j,dp);


		for(int a = 0; a < v[j]; ++a) {
			if(i == s.size() || s[i++] == '.') return dp[oi][oj]=one;
		}
		if((i == s.size() || s[i++] == '#')) return dp[oi][oj]=one;

		return dp[oi][oj] = (dfs2(s, v, i, j+1,dp) + one);
	}

	if (s[i] == '.') return dp[oi][oj] = dfs(s, v, i+1, j);


	for(int a = 0; a < v[j]; ++a) {
		if(i == s.size() || s[i++] == '.') return dp[oi][oj]=0;
	}
	if((i == s.size() || s[i++] == '#')) return dp[oi][oj]=0;
	return dp[oi][oj]=dfs2(s, v, i, j+1,dp);
}

int main() {
	cout << "Parsing...\n";
	string s[lines];
	string s2[lines];
	string r;
	vector<vector<int>> v(lines);
	vector<vector<int>> v2(lines);
	for(int i = 0; i < lines; ++i) {
		cin >> s[i];
		for (int a = 0; a < 5; ++a) {
        	s2[i].insert(s2[i].end(), s[i].begin(), s[i].end());
    	}
		s[i].push_back('.');
		s2[i].push_back('.');
		cin >> r;


		int num = 0;
		for(char & c : r) {
			if(c == ',') {
				v[i].push_back(num);
				num = 0;
			}
			else {
				num = num * 10 + (c - '0');
			}
		}
		v[i].push_back(num);
		for (int a = 0; a < 5; ++a) {
        	v2[i].insert(v2[i].end(), v[i].begin(), v[i].end());
    	}
	}

	cout << "Calculating...\n";
	ll sum = 0, sum2 = 0;
	for(int i = 0; i < lines; ++i) {
		sum += dfs(s[i], v[i], 0, 0);

		vector<vector<ll>> dp(s2[i].size(), vector<ll>(v2[i].size(), -1));
		sum2 += dfs2(s2[i], v2[i], 0, 0, dp);

		cout << i << '\n';
	}
	cout << "Part 1: " << sum << ", Part 2: " << sum2;
	
	return 0;
}