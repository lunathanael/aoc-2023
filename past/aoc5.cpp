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

using namespace std;

const int sc = 10;
const int a = 29-3;
const int b = 50-31;
const int c = 96 - 52;
const int d = 119 - 98;
const int e = 152 - 121;
const int f = 203 - 154;
const int g = 247 - 205;

long long part1() {
	vector<long long> seeds;
	string s;
	cin >> s;
	for (int i = 0; i < sc; ++i) {
		long long co;
		cin >> co;
		seeds.push_back(co);
	}


	cin >> s;
	cin >> s;
	unordered_set<int> occ;
	for(int j = 0; j < a; ++j) {
		long long start, end, range;
		cin >> end >> start >> range;
		for(int i = 0; i < sc; ++i) {
			if(seeds[i] >= start && seeds[i] < start + range && occ.find(i) == occ.end()){
				seeds[i] = seeds[i] - start + end;
				occ.insert(i);
			}
		}
	}

	cin >> s;
	cin >> s;
	occ.clear();
	for(int j = 0;j < b; ++j) {
		long long start, end, range;
		cin >> end >> start >> range;
		for(int i = 0; i < sc; ++i) {
			if(seeds[i] >= start && seeds[i] < start + range && occ.find(i) == occ.end()){
				seeds[i] = seeds[i] - start + end;
				occ.insert(i);
			}
		}
	}

	cin >> s;
	cin >> s;
	occ.clear();
	for(int j = 0; j < c; ++j) {
		long long start, end, range;
		cin >> end >> start >> range;
		for(int i = 0; i < sc; ++i) {
			if(seeds[i] >= start && seeds[i] < start + range && occ.find(i) == occ.end()){
				seeds[i] += -start + end;
				occ.insert(i);
			}
		}
	}

	cin >> s;
	cin >> s;
	occ.clear();
	for(int j = 0; j < d; ++j) {
		long long start, end, range;
		cin >> end >> start >> range;
		for(int i = 0; i < sc; ++i) {
			if(seeds[i] >= start && seeds[i] < start + range && occ.find(i) == occ.end()){
				seeds[i] = seeds[i] - start + end;
				occ.insert(i);
			}
		}
	}

	cin >> s;
	cin >> s;
	occ.clear();
	for(int j = 0; j < e; ++j) {
		long long start, end, range;
		cin >> end >> start >> range;
		for(int i = 0; i < sc; ++i) {
			if(seeds[i] >= start && seeds[i] < start + range && occ.find(i) == occ.end()){
				seeds[i] = seeds[i] - start + end;
				occ.insert(i);
			}
		}
	}

	cin >> s;
	cin >> s;
	occ.clear();
	for(int j = 0; j < f; ++j) {
		long long start, end, range;
		cin >> end >> start >> range;
		for(int i = 0; i < sc; ++i) {
			if(seeds[i] >= start && seeds[i] < start + range && occ.find(i) == occ.end()){
				seeds[i] = seeds[i] - start + end;
				occ.insert(i);
			}
		}
	}

	cin >> s;
	cin >> s;
	occ.clear();
	for(int j = 0; j < g; ++j) {
		long long start, end, range;
		cin >> end >> start >> range;
		for(int i = 0; i < sc; ++i) {
			if(seeds[i] >= start && seeds[i] < start + range && occ.find(i) == occ.end()){
				seeds[i] = seeds[i] - start + end;
				occ.insert(i);
			}
		}
	}



	return *min_element(seeds.begin(), seeds.end());
}
#define ll long long

long long part2() {
	set<pair<ll, ll>> s;
	int n;
	cin >> n;
    for(int i = 0; i < n; i += 2) {
        ll a, b;
        cin >> a >> b;
        s.insert({a, a + b - 1});
    }
    int q;
    cin >> q;
    vector<set<pair<pair<ll, ll>, pair<ll, ll>>>> v(q);
    for(int i = 0; i < q; i++) {
        int m;
        cin >> m;
        for(int j = 0; j < m; j++) {
            ll a, b, c;
            cin >> b >> a >> c;
            v[i].insert({{a, a + c - 1}, {b, b + c - 1}});
        }
    }
    cout << "read\n";
    for(int i = 0; i < q; i++) {
        set<pair<ll, ll>> tmp;
        while(!s.empty()) {
            auto x = *s.begin();
            s.erase(s.begin());
            auto itr = v[i].lower_bound({{x.first + 1, 0}, {0, 0}});
            if(itr == v[i].begin()) {
                tmp.insert(x);
                continue;
            }
            itr--;
            if(x.second < itr->first.first or x.first > itr->first.second) {
                tmp.insert(x);
                continue;
            }
            if(x.second <= itr->first.second) {
                ll diff = itr->second.first - itr->first.first;
                x.first += diff;
                x.second += diff;
                tmp.insert(x);
                continue;
            }
            ll diff = itr->second.first - itr->first.first;
            tmp.insert({x.first + diff, itr->first.second + diff});
            s.insert({itr->first.second + 1, x.second});
        }
        s = tmp;
    }
    return s.begin()->first;
}



int main() {

	cout << part2();
	return 0;
}