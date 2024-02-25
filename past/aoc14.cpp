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

void fun(vector<string> & v, vector<int>& dir) {
	if(dir[0] == 0) {
		
		if(dir[1] == -1) {	
			vector<int> l(v[0].size(), 0);	
			for(int i = 0; i < v.size(); ++i) {
				for(int j = 0; j < v[0].size(); ++j) {
					if(v[i][j] == '#') {
						l[j] = i + 1;
					}
					if(v[i][j] == 'O') {
						v[i][j] = '.';
						v[l[j]++][j] = 'O';
					}
				}
			}

		}
		else {
			vector<int> l(v[0].size(), v.size()-1);
			for(int i = v.size() - 1; i >=0; --i) {
				for(int j = 0; j < v[0].size(); ++j) {
					if(v[i][j] == '#') {
						l[j] = i - 1;
					}
					if(v[i][j] == 'O') {
						v[i][j] = '.';
						v[l[j]--][j] = 'O';
					}
				}
			}
		}
	}
	else {
		if(dir[0] == -1) {		
			vector<int> l(v.size(), 0);
			for(int j = 0; j < v[0].size(); ++j) {
				for(int i = 0; i < v.size(); ++i) {
					if(v[i][j] == '#') {
						l[i] = j + 1;
					}
					if(v[i][j] == 'O') {
						v[i][j] = '.';
						v[i][l[i]++] = 'O';
					}
				}
			}

		}
		else {
			vector<int> l(v.size(), v[0].size()-1);
			for(int j = v[0].size()-1; j >=0; --j) {
				for(int i = 0; i < v.size(); ++i) {
					if(v[i][j] == '#') {
						l[i] = j - 1;
					}
					if(v[i][j] == 'O') {
						v[i][j] = '.';
						v[i][l[i]--] = 'O';
					}
				}
			}
		}
	}
}

int calc(vector<string> & v) {
	vector<int> g(v[0].size(), v.size());
	int sum = 0;
	for(int i = 0; i < v.size(); ++i) {
        sum += (v.size() - i) * count(v[i].begin(), v[i].end(), 'O');
	}
	return sum;
}

string str(vector<string> & s) {
	string a;
	for(auto & v : s) {
		a += v;
	}
	return a;
}


int main() {
	ll sum = 0;

	string line;
	vector<string> v;
	vector<vector<int>> dir = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
	while(getline(cin, line)) {
		v.push_back(line);
	}
	fun(v, dir[0]);
	cout << calc(v) << '\n';

	
	unordered_map<string, vector<int>> ump;
	for(int i = 1; i <= 1000000000; ++i) {

		fun(v, dir[0]);
		fun(v, dir[1]);
		fun(v, dir[2]);
		fun(v, dir[3]);

    	string x = str(v);
	    if(ump.find(x) != ump.end()) {
	    	int cyc = i - ump[x][0];
	    	for(auto & p : ump) {
	    		if(p.second[0] >= ump[x][0] && p.second[0] % cyc == 1000000000 % cyc) {
	    			cout << p.second[1] << '\n';
	    		}
	    	}
	    	break;
	    }
	    ump[x] = {i, calc(v)};

	}

	







	return 0;
}