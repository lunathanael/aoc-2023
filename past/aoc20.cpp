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

// bool -> is high

pair<ll, ll> rec(
	vector<pair<int, bool>> & curr,
	vector<pair<bool, vector<int>>> &mv,
	unordered_map<int, unordered_map<int, bool>> &conj,
	unordered_map<int, bool> & flip,
	queue<int> & changes) {
	if(curr.empty()) return {0, 0};

	ll low = 0, high = 0;
	vector<pair<int, bool>> next;
	for(pair<int, bool> & p : curr) {
		if(p.second) ++high;
		else ++low;

		int key = p.first;
		bool high = p.second;
		if(mv[key].second.empty()) continue;

		if(mv[key].first == false) {
			// is flip flop
			if(high == false) {
				flip[key] ^= 1;

				bool nxt_h = (flip[key] == 1);
				for(int & i : mv[key].second) {
					next.push_back({i, nxt_h});
					if(mv[i].second.empty()) continue;
					if(mv[i].first == true) {
						changes.push(key);
					}
				}
			}
		}
		else {
			int idx = changes.front();
			changes.pop();

			conj[key][idx] = high;

			bool nxt_h = any_of(conj[key].begin(), conj[key].end(), [](const auto & a) {
				return a.second == false;
			});

			for(int & i : mv[key].second) {
				next.push_back({i, nxt_h});
				if(mv[i].second.empty()) continue;
				if(mv[i].first == true) {
					changes.push(key);
				}
			}
		}
	}

	pair<ll, ll> res = rec(next, mv, conj, flip, changes);
	return {low + res.first, high + res.second};
}

int cs;

unordered_map<int, ll> ump;
bool p2(
	ll & sum1,
	ll & sum2,
	ll & press,
	vector<pair<int, bool>> & curr,
	vector<pair<bool, vector<int>>> &mv,
	unordered_map<int, unordered_map<int, bool>> &conj,
	unordered_map<int, bool> & flip,
	queue<int> & changes) {
	if(curr.empty()) return false;

	vector<pair<int, bool>> next;
	for(pair<int, bool> & p : curr) {
		if(p.second) ++sum2;
		else ++sum1;

		int key = p.first;
		bool high = p.second;
		if(mv[key].second.empty()) continue;


		if(mv[key].first == false) {
			// is flip flop
			if(high == false) {
				flip[key] ^= 1;

				bool nxt_h = (flip[key] == 1);
				for(int & i : mv[key].second) {
					next.push_back({i, nxt_h});
					if(mv[i].second.empty()) continue;
					if(mv[i].first == true) {
						changes.push(key);
					}
				}
			}
		}
		else {
			int idx = changes.front();
			changes.pop();

			conj[key][idx] = high;

			if(key == cs && high == true) {
				if(ump.find(idx) == ump.end()) 
					ump[idx] = (press);
			}

			bool nxt_h = any_of(conj[key].begin(), conj[key].end(), [](const auto & a) {
				return a.second == false;
			});

			for(int & i : mv[key].second) {
				next.push_back({i, nxt_h});
				if(mv[i].second.empty()) continue;
				if(mv[i].first == true) {
					changes.push(key);
				}
			}
		}
	}
	return p2(sum1, sum2, press, next, mv, conj, flip, changes);
}

int main() {
	vector<string> vs;
	string line;
	while(getline(cin, line)) {
		vs.push_back(line);
	}

	//parse
	unordered_map<string, int> module;
	vector<pair<bool, vector<int>>> mv;
	unordered_map<int, unordered_map<int, bool>> conj;
	unordered_map<int, bool> flip;

	vector<string> broad;
	for(string & s : vs) {
		if(s[0] == 'b') {
			s.push_back(',');
			int i = 0;
			while(s[i] != '>') ++i;
			i+=2;
			string a;
			while(i < s.size()) {
				if(s[i] == ',') {
					broad.push_back(a);
					a = "";
					++i; // skip space
				}
				else {
					a += s[i];
				}
				++i;
			}
		}
		else {
			s.push_back(',');
			int i = 1;
			string key;
			while(s[i] != ' ') key += s[i++];

			if(module.find(key) == module.end()) {
				module[key] = module.size();
				mv.push_back({false,{}});
			}
			int ikey = module[key];


			while(s[i] != '>') ++i;
			i+=2;

			vector<int> out;
			string a;
			while(i < s.size()) {
				if(s[i] == ',') {
					if(module.find(a) == module.end()) {
						module[a] = module.size();
						mv.push_back({false,{}});
					}
					out.push_back(module[a]);
					a = "";
					++i; // skip space
				}
				else {
					a += s[i];
				}
				++i;
			}

			if(s[0] == '%') {
				mv[ikey] = {false, out};
				flip[ikey] = false;
			}
			else {
				mv[ikey] = {true, out};
				conj[ikey] = unordered_map<int, bool>();
			}
		}
	}
	cs = module["cs"];



	for(auto & a : conj) {
		int key = a.first;
		for(int i = 0; i < mv.size(); ++i) {
			vector<int> & v = mv[i].second;
			if(find(v.begin(), v.end(), key) != v.end()) {
				(a.second)[i] = false;
			}
		}
	}

	

	vector<pair<int, bool>> first;
	queue<int> changes;
	for(string & s : broad) {
		first.push_back({module[s], false});
	}

	ll sum1 = 0, sum2 = 0;

	// for(int i = 0; i < 1000; ++i) {
	// 	++sum1;
	// 	pair<ll, ll> p = rec(first, mv, conj, flip, changes);
	// 	sum1 += p.first;
	// 	sum2 += p.second;
	// }
	// cout << (sum1 * sum2) << '\n';


	ll part1 = 0;
	ll presses = 0;
	while(ump.size() != 4) {
		++presses;
		++sum1;
		p2(sum1, sum2, presses, first, mv, conj, flip, changes);
		if(presses == 1000) part1 = (sum1 * sum2);
	}
	cout << part1 << '\n';

	ll part2 = 1;
	for(auto & a : ump) {
		part2 = lcm(part2, a.second);
	}
	cout << part2;

	return 0;
}

// //ans
// 230402300925361
// 23436070925787