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
    size_t operator()(const std::pair<long long, long long>& p) const {
        auto k1 = static_cast<size_t>(std::abs(p.first));
        auto k2 = static_cast<size_t>(std::abs(p.second));
        return 0.5 * (k1 + k2) * (k1 + k2 + 1) + k2;
    }
};










int main() {
	vector<string> vs;
	string line;
	while(getline(cin, line)) {
		vs.push_back(line);
	}


	int m = vs.size(), n = vs[0].size();

	auto valid = [&](int row, int col) {
		return row >= 0 && row < m && col >= 0 && col < n;
	};

	vector<string> final = vs;
	std::unordered_set<std::pair<long long, long long>, hash_pair> curr;
	for(long long i = 0; i < m; ++i) {
		for(long long j = 0; j < n; ++j) {
			if(vs[i][j] == 'S'){
				curr.insert({i, j});
				vs[i][j] = '.';
			}
		}
	}

	for(int i = 0; i < 64; ++i) {
		vector<string> temp = vs;
		for(int r = 0; r < m; ++r) {
			for(int c = 0; c < n; ++c) {
				if(final[r][c] == 'S') {

					if(valid(r+1, c) && temp[r+1][c] == '.')
						temp[r+1][c] = 'S';

					if(valid(r-1, c) && temp[r-1][c] == '.')
						temp[r-1][c] = 'S';

					if(valid(r, c+1) && temp[r][c+1] == '.')
						temp[r][c+1] = 'S';

					if(valid(r, c-1) && temp[r][c-1] == '.')
						temp[r][c-1] = 'S';

				}
			}
		}
		final = temp;
	}

	int count = 0;
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			if(final[i][j] == 'S')
				++count;
		}
	}
	cout << count << '\n';

	auto modr = [&](long long row) {
		long long new_row =((row%m)+m)%m;
		//assert(new_row >= 0 && new_row < m);
		return new_row;
	};

	auto modc = [&](long long col) {
		long long new_col = ((col%n)+n)%n;
		//assert(new_col >= 0 && new_col < n);
		return new_col;
	};

	auto start = std::chrono::steady_clock::now( );
	ll goal = 26501365;
	vector<pair<ll, ll>> points;
	for(long long step = 1; step <= goal; ++step) {
		std::unordered_set<std::pair<long long, long long>, hash_pair> next;

		for(auto & coord : curr) {
			long long row = coord.first, col = coord.second;
			if(vs[modr(row+1)][modc(col)] == '.')
				next.insert({row+1, col});

			if(vs[modr(row-1)][modc(col)] == '.')
				next.insert({row - 1, col});

			if(vs[modr(row)][modc(col+1)] == '.')
				next.insert({row,col+1});

			if(vs[modr(row)][modc(col-1)] == '.')
				next.insert({row,col-1});
		}
		curr = next;


		if(step % n == goal % n) {
			points.push_back({step, static_cast<ll>(curr.size())});
			cout << "!";
		}
		if(points.size() == 3) break;
	}
	cout << '\n';
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ) - start );
    

	auto quad = [&](ll target){
		target = target / n;
		ll a_0 = points[0].second;
		ll a_1 = points[1].second;
		ll a_2 = points[2].second;

		ll b_0 = a_0;
		ll b_1 = a_1 - a_0;
		ll b_2 = a_2 - a_1;

		return b_0 + b_1 * target + ((target * (target-1))/2)*(b_2-b_1);
	};

	cout << quad(goal) << '\n';
    std::cout << "milliseconds since start: " << elapsed.count( ) << "ms" <<'\n';
	return 0;
}