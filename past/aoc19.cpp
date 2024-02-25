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

unordered_map<char, int> category = {
	{'x', 0}, 
	{'m', 1}, 
	{'a', 2}, 
	{'s', 3},
};


long long goodr(string &state, vector<vector<int>> ranges, unordered_map<string, vector<pair<pair<int, int>, string>>> & workflows) {
	for(auto & range : ranges) {
		if(range[0] > range[1]) return 0ll;
	}
	if(state == "R") return 0ll;
	if(state == "A") {
		ll prod = 1ll;
		for(auto & range : ranges) {
			prod *= (range[1] - range[0] + 1);
		}
		return prod;
	}

	ll sum = 0;
	vector<pair<pair<int, int>, string>> workflow = workflows[state];
	for(int i = 0; i < workflow.size(); ++i) {
		string new_state = workflow[i].second;
		if(i == workflow.size() - 1) {
			sum += goodr(new_state, ranges, workflows);
			break;
		}
		int cat = workflow[i].first.first;
		int val = workflow[i].first.second;
		if(val > 0) {
			int temp = ranges[cat][0];
			ranges[cat][0] = val + 1;
			sum += goodr(new_state, ranges, workflows);
			ranges[cat][0] = temp;
			ranges[cat][1] = val;
		}
		else {
			val = -val;
			int temp = ranges[cat][1];
			ranges[cat][1] = val - 1;
			sum += goodr(new_state, ranges, workflows);
			ranges[cat][1] = temp;
			ranges[cat][0] = val;
		}
	}
	return sum;
}


int main() {
	vector<string> works;
	string line;
	while(getline(cin, line) && line != "e") {
		works.push_back(line);
	}
	vector<string> sparts;
	while(getline(cin, line)) {
		sparts.push_back(line);
	}


	unordered_map<string, vector<pair<pair<int, int>, string>>> workflows;
	for (string & s : works) {
		string key;
		int i = 0;
		while(s[i] != '{') {
			key += s[i];
			++i;
		}
		++i; // skip {
		while(i != s.size()) {
			string rule;
			while(s[i] != '>' && s[i] != '<' && s[i] != '}') {
				rule += s[i];
				++i;
			}
			if(s[i] == '}') {
				workflows[key].push_back({{-1, -1}, rule});
				break;
			}
			bool less = (s[i] == '<');
			++i; // skip <>
			int num = 0;
			while(s[i] != ':') {
				num = num * 10 + s[i] - '0';
				++i;
			}
			++i; //skip :
			if(less) num *= -1;
			string val;
			while(s[i] != ',') {
				val += s[i];
				++i;
			}
			int irule = category[rule[0]];
			workflows[key].push_back({{irule, num}, val});
			++i; //skip ,
		}
	}
	vector<vector<int>> parts;
	for(string & s : sparts) {
		parts.push_back({});
		int i = 3;
		int num = 0;
		while(s[i] != ',') {
			num = num * 10 + s[i] - '0';
			++i;
		}
		parts.back().push_back(num);
		num = 0;
		i += 3;
		while(s[i] != ',') {
			num = num * 10 + s[i] - '0';
			++i;
		}
		parts.back().push_back(num);
		num = 0;
		i += 3;
		while(s[i] != ',') {
			num = num * 10 + s[i] - '0';
			++i;
		}
		parts.back().push_back(num);
		num = 0;
		i += 3;
		while(s[i] != '}') {
			num = num * 10 + s[i] - '0';
			++i;
		}
		parts.back().push_back(num);
	}

	// for (auto & b : workflows) {
	// 	cout << b.first << ':';
	// 	for(auto & a : b.second){
	// 		cout << a.first.first << ' ' << a.first.second << ' ' << a.second << ',';
	// 	}
	// 	cout << '\n';
	// }
	// cout << "next\n";
	// for(auto & a : parts) {
	// 	cout << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << a[3] << '\n';
	// }

	auto good = [&](const vector<int> & part) {
		string state = "in";
		while(state.size() != 1 || (state[0] != 'A' && state[0] != 'R')) {
			vector<pair<pair<int, int>, string>> workflow = workflows[state];
			//cout << state << ' ';
			for(int i = 0; i < workflow.size(); ++i) {
				if(i == workflow.size() - 1) {
					state=workflow[i].second;
					break;
				}
				int cat = workflow[i].first.first;
				int val = workflow[i].first.second;
				if(val > 0) {
					if(part[cat] > val) {
						state = workflow[i].second;
						break;
					}
				}
				else {
					val = -val;
					if(part[cat] < val) {
						state = workflow[i].second;
						break;
					}
				}
			}
		}
		return state == "A";
	};


	ll sum = 0;
	for (auto & part : parts) {
		if(good(part)) {
			//cout << "A\n";
			sum += part[0] + part[1] + part[2] + part[3];
		}
		// else {
		// 	cout << "R\n";
		// }
	}
	cout << sum << '\n';

	
	vector<vector<int>> initial_range = {{1, 4000}, {1,4000}, {1, 4000}, {1, 4000}};
	string initial_state = "in";
	ll p2 = goodr(initial_state, initial_range, workflows);
	cout << p2 << '\n';
	return 0;
}