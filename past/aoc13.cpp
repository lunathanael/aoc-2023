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

bool checkr(vector<string> &s, int r) {
	for(int i = 0; i <= r; ++i) {
		if(r + i+1 >= s.size() || r-i < 0) break;
		if(s[r+i+1] != s[r-i]) return false;
	}
	return true;
}

bool neq(string & a, string & b) {
	bool diff = 0;
	for(int i = 0; i < a.size(); ++i) {
		if(a[i] != b[i]) {
			if(diff) return 0;
			diff = 1;
		}
	}
	return true;
}

bool checks(vector<string> &s, int r) {
	bool diff = 0;
	for(int i = 0; i <= r; ++i) {
		if(r + i+1 >= s.size() || r-i < 0) break;
		if(s[r+i+1] != s[r-i]) {
			if(neq(s[r+i+1], s[r-i])) {
				if(diff) return false;
				diff = 1;
			}
			else{
				return false;
			}
		}
	}
	return diff;
}

int main() {
	ll sum = 0, sum2 = 0;

	string line;
	while(line != "e") {
		vector<string> s;
		while(getline(cin, line) && line != "" && line != "e") {
			s.push_back(line);
		}



		ll a = 0, b = 0;
		for(int i = 0; i < s.size() - 1; ++i) {
			if(checkr(s, i)) {
				a = 100 * (i+1);
				break;
			}
		}
		if(a == 0) {
			vector<string> st;
			for(int i = 0; i < s[0].size(); ++i) {
				st.push_back("");
				for(int j = 0; j < s.size(); ++j) {
					st[i].push_back(s[j][i]);
				}
			}

			for(int i = 0; i < st.size() - 1; ++i) {
				if(checkr(st, i)) {
					a = i + 1;
					break;
				}
			}

			// p2
			for(int i = 0; i < s.size() - 1; ++i) {
				if(checks(s, i)) {
					b = 100 * (i+1);
					break;
				}
			}
			if(b==0) {
				for(int i = 0; i < st.size() - 1; ++i) {
					if(i+1 == a) continue;
					if(checks(st, i)) {
						b = i + 1;
						break;
					}
				}
			}
		}
		else {
			for(int i = 0; i < s.size() - 1; ++i) {
				if((i+1) * 100 == a) continue;
				if(checks(s, i)) {
					b = 100 * (i+1);
					break;
				}
			}
			if(b==0) {
				vector<string> st;
				for(int i = 0; i < s[0].size(); ++i) {
					st.push_back("");
					for(int j = 0; j < s.size(); ++j) {
						st[i].push_back(s[j][i]);
					}
				}

				for(int i = 0; i < st.size() - 1; ++i) {
					if(checks(st, i)) {
						b = i + 1;
						break;
					}
				}
			}
		}
		sum += a;
		sum2 += b;
	}
	cout << sum << ' ' << sum2 << '\n';


	return 0;
}