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

#define least 200000000000000
#define most 400000000000000

/*
3 eq for each:

stable uk:x,y,z,bx, by, bz : 6
1 uk for each 3:

x + x_0 * t_1 = a_0 + b_0 * t_1,
y + y_0 * t_1 = a_1 + b_1 * t_1,
z + z_0 * t_1 = a_2 + b_2 * t_1,

x + x_0 * t_2 = c_0 + d_0 * t_2,
y + y_0 * t_2 = c_1 + d_1 * t_2,
z + z_0 * t_2 = c_2 + d_2 * t_2,

x + x_0 * t_3 = e_0 + f_0 * t_3,
y + y_0 * t_3 = e_1 + f_1 * t_3,
z + z_0 * t_3 = e_2 + f_2 * t_3,



9eq, 9uk
*/


bool inside(vector<vector<ll>> & h1, vector<vector<ll>> & h2) {
	ll a = h1[0][0], b = h1[1][0], c = h2[0][0], d = h2[1][0];
	ll e = h1[0][1], f = h1[1][1], g = h2[0][1], h = h2[1][1];
	double det = b * h - d * f;

	if(abs(det) < 1e-9)
		return false;

	double t1 = (-(a * h) + c * h + d * e - d * g) / det;
	double t2 = (-(a*f) + b * e - b * g + c * f) / det;
    if(t1 < 0 || t2 < 0)
    	return false;

    double x = a + b * t1;
    double y = e + f * t1;
    return x >= least && x <= most && y >= least && y <= most;
}


ll p2_test(vector<vector<vector<ll>>> & hailstone) {
	vector<vector<double>> intersects;
	double mm = 1e14;
	for(int i = 0; i < hailstone.size(); ++i) {
		for(int j = i+1; j < hailstone.size(); ++j) {
			auto & h1 = hailstone[i];
			auto & h2 = hailstone[j];
			ll a = h1[0][0], b = h1[1][0], c = h2[0][0], d = h2[1][0];
			ll e = h1[0][1], f = h1[1][1], g = h2[0][1], h = h2[1][1];
			ll I = h1[0][2], J = h1[1][2], K = h2[0][2], L = h2[1][2];
			double det = b * h - d * f;

			if(abs(det) < 1e-10)
				continue;

			double t1 = (-(a * h) + c * h + d * e - d * g) / det;
			double t2 = (-(a*f) + b * e - b * g + c * f) / det;

		    double x = a + b * t1;
		    double y = e + f * t1;
		    double z1 = I + J * t1;
		    double z2 = K + L * t2;
		    mm = min(mm, abs(z1-z2));
		    if(abs(z1-z2) < 1e-9) {
		    	intersects.push_back({x,y,z1});
		    }
		    if(intersects.size() > 1) {
		    	return 100ll;
		    }
		}
	}
	cout << mm << '\n';

	return intersects.size();
}

void p2_manual(vector<vector<vector<ll>>> & hailstone) {
	for(int i = 0; i < hailstone.size(); ++i) {
		auto & h = hailstone[i];
		cout << h[0][0] << ' ' << h[1][0] << '\n';
		cout << h[0][1] << ' ' << h[1][1] << '\n';
		cout << h[0][2] << ' ' << h[1][2] << '\n';
		// cout << "x_0 + x_1*t_" << i << " = " << h[0][0] << " + " << h[1][0] << " * t_" << i << ", ";
		// cout << "y_0 + y_1*t_" << i << " = " << h[0][1] << " + " << h[1][1] << " * t_" << i << ", ";
		// cout << "z_0 + z_1*t_" << i << " = " << h[0][2] << " + " << h[1][2] << " * t_" << i << ", ";
	}
}

int main() {
	vector<vector<vector<long long>>> hailstone;
	string line;
	while(getline(cin, line)) {
		hailstone.push_back(vector<vector<ll>>(2, vector<ll>(3)));
		int i = 0;
		for(int j = 0; j < 3; ++j) {
			ll num = 0;
			while(1) {
				if(line[i] == ',' || line[i] == ' ') {
					hailstone.back()[0][j] = num;
					i+=2;
					break;
				}
				else {
					num = num * 10 + (line[i] - '0');
				}
				++i;
			}
		}
		++i; //skip space;
		line.push_back(',');
		for(int j = 0; j < 3; ++j) {
			bool neg = false;
			ll num = 0;
			if(line[i] == '-') {
				neg = true;
				++i;
			}
			while(1) {

				if(line[i] == ',' || line[i] == ' ') {
					if(neg) num = -num;
					hailstone.back()[1][j] = num;
					i+=2;
					break;

				}
				else {
					num = num * 10 + (line[i] - '0');
				}

				++i;
			}
		}
	}
	ll p1 = 0;
	for(int i = 0; i < hailstone.size(); ++i) {
		for(int j = i+1; j < hailstone.size(); ++j) {
			if(inside(hailstone[i], hailstone[j])) {
				++p1;
			}
		}
	}
	cout << p1 << '\n';

	cout << p2_test(hailstone);
	return 0;
}