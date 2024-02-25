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

using namespace std;

#define ll long long int

unordered_map<char, vector<int>> dirs = {{'R', {0, 1}}, {'L', {0, -1}}, {'U', {-1,0}}, {'D', {1,0}}};

template <class T>
vector<vector<T>> gridify(vector<char> & dir, vector<T>& dist) {
	vector<vector<T>> grid;
	grid.push_back({0,0});
	T r = 0, c = 0;
	T prem = 0;
	for(int i = 0; i < dir.size(); ++i) {
		prem += dist[i];
		r += dirs[dir[i]][0] * dist[i];
		c += dirs[dir[i]][1] * dist[i];
		grid.push_back({r, c});
	}
	grid.push_back({prem});
	return grid;
}


void part1() {
	vector<string> vs;
	string line;
	while(getline(cin, line)) {
		vs.push_back(line);
	}

	vector<char> dir;
	vector<int> dist;
	for(string & s : vs) {
		dir.push_back(s[0]);
		int i = 2, num = 0;
		while(s[i] != ' ') {
			num = num * 10 + s[i] - '0';
			++i;
		}
		dist.push_back(num);
	}

	vector<vector<int>> grid = gridify(dir, dist);
	int prem = grid.back()[0];
	grid.pop_back();
	reverse(grid.begin(), grid.end());

	int a2 = 0;
	for(int i = 0; i < grid.size()-1; ++i) {
		a2 += (grid[i][1]+ grid[i+1][1]) * (grid[i][0] - grid[i+1][0]);
	}
	int area = a2/2 + prem/2 + 1;
	cout << prem << ' ';

	cout << area;
}

void part2() {
	vector<string> vs;
	string line;
	while(getline(cin, line)) {
		vs.push_back(line);
	}

	vector<char> dir;
	vector<long long> dist;
	for(string & s : vs) {
		string h = s.substr(s.size() - 7, 5);
		char d = s[s.size()-2];
		if(d == '0') {
			d = 'R';
		}
		if(d == '1') {
			d = 'D';
		}
		if(d == '2') {
			d = 'L';
		}
		if(d == '3') {
			d = 'U';
		}
		dir.push_back(d);
		stringstream ss;
		ss << hex << h;
		long long num;
		ss >> num;
		dist.push_back(num);
	}

	vector<vector<long long>> grid = gridify(dir, dist);
	long long prem = grid.back()[0];
	grid.pop_back();
	reverse(grid.begin(), grid.end());

	long long a2 = 0;
	for(int i = 0; i < grid.size()-1; ++i) {
		a2 += (grid[i][1]+ grid[i+1][1]) * (grid[i][0] - grid[i+1][0]);
	}
	long long area = a2/2 + prem/2 + 1;

	cout << area;
}


int main() {
	part2();
	

	return 0;
}