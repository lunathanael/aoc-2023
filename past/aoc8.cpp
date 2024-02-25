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

#define ll long long int

unordered_map<string, string> umpl, umpr;
vector<string> u;

string inst;

ll part1() {
	ll sum = 0;

	int n;
	cin >> n;

	cin >> inst;

	int m;
	cin >> m;
	for(int i = 0; i < m; ++i) {
		string s;
		cin >> s;
		string r;
		cin >> r;
		cin >> r;
		umpl[s] = r.substr(1, 3);
		cin >> r;
		umpr[s] = r.substr(0, 3);
	}

	ll step = 0;
	string curr = "AAA";
	while(curr != "ZZZ") {
		if (inst[step++ % n] == 'L') {
			curr = umpl[curr];
		}
		else {
			curr = umpr[curr];
		}
	}

	return step;
}

ll part2() {
	ll sum = 0;

	int n;
	cin >> n;

	cin >> inst;

	int m;
	cin >> m;
	for(int i = 0; i < m; ++i) {
		string s;
		cin >> s;

		if(s[2] == 'A') {
			u.push_back(s);
		}
		
		string r;
		cin >> r;
		cin >> r;
		umpl[s] = r.substr(1, 3);
		cin >> r;
		umpr[s] = r.substr(0, 3);
	}

	for(string curr : u) {
		ll step = 0;
		while(curr[2] != 'Z') {
			if (inst[step++ % n] == 'L') {
				curr = umpl[curr];
			}
			else {
				curr = umpr[curr];
			}
		}
		cout << step << '\n';
	}

	// ll step = 0;
	// while(any_of(u.begin(), u.end(), [](const auto & a) {
	// 	return a[2] != 'Z';
	// })) {
	// 	if (inst[step++ % n] == 'L') {
	// 		for(string & s : u) s = umpl[s];
	// 	}
	// 	else {
	// 		for(string & s : u) s = umpr[s];
	// 	}
	// 	if(step % 42690 == 1) cout << step << '\n';
	// }

	return 0;
}


int main() {

	cout << part2();
	return 0;
}