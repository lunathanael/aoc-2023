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

int n;


int main() {
	ll sum = 0;

	// int val = 0;
	// char c;
	// while(cin >> c && c != '$') {
	// 	if(c == ',') {
	// 		sum += val;
	// 		val = 0;
	// 	}
	// 	else {
	// 		val += c;
	// 		val = (val * 17) % 256;
	// 	}
	// }
	// cout << sum;


	string s;
	char c;
	vector<string> v;
	while(cin >> c && c != '$') {
		if(c == ',') {
			v.push_back(s);
			s = "";
		}
		else {
			s += c;
		}
	}

	for(auto & a : v) {
		cout << a << '\n';
	}

	vector<vector<pair<string, int>>> ump(256);
	for(auto & a : v) {
		int i = 0, val = 0;
		s = "";
		while(a[i] != '-' && a[i] != '=') {
			s += a[i];
			val += a[i++];
			val = (val * 17) % 256;
		}
		if(a[i] == '-') {
			auto one = find_if(ump[val].begin(), ump[val].end(), [&](const auto & z) {
				return z.first == s;
			});
			if(one != ump[val].end()) {
				ump[val].erase(one);
			}
		}
		else {
			int lens = a[i+1] - '0'; 			
			auto one = find_if(ump[val].begin(), ump[val].end(), [&](const auto & z) {
				return z.first == s;
			});
			if(one != ump[val].end()) {
				(*one).second = lens;
			}
			else {
				ump[val].push_back(make_pair(s, lens));
			}
		}
	}

	for(int j = 0; j < ump.size(); ++j) {
		for(int i = 0; i < ump[j].size(); ++i) {
			sum += (i+1) * ump[j][i].second * (j+1);
		}
	}
	cout << sum;
	return 0;
}