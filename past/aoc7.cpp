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

string c = "23456789TJQKA";

// 13 at each rank
// 7 ranks

ll r(string card) {
	unordered_map<char, int> ump;
	for(char & c : card) ++ump[c];

	int mx = 0, i = -1;
	for(auto & a : ump) {
		if(a.second > mx) {
			i = a.first;
			mx = a.second;
		}
	}
	if(mx == 3) {
		for(auto & a : ump) {
			if(a.second == 2 && a.first != i) {
				return 4;
			}
		}
		return 3;
	}
	if(mx == 2) {
		for(auto & a : ump) {
			if(a.second == 2 && a.first != i) {
				return 2;
			}
		}
		return 1;
	}
	if(mx == 5) return 6;
	if(mx == 4) return 5;
	if(mx == 1) return 0;
	return -1;
}

unordered_map<char, int> mp = {{'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4}, {'7', 5}, {'8', 6}, {'9', 7}, {'T', 8}, {'J', 9}, {'Q', 10}, {'K', 11}, {'A', 12}};

bool smaller(string a, string b) {
	for (char & c : a) {
		c = mp[c];
	}
	for (char & c : b) {
		c = mp[c];
	}
	return a < b;
}

ll part1() {
	ll sum  = 0;
	ll n;
	cin >> n;

	vector<vector<ll>> cards(3, vector<ll>());
	vector<string> cs;
	for(int i = 0; i < n; ++i) {
		string card;
		ll bid;
		cin >> card;
		cin >> bid;

		ll score = r(card);
		cards[0].push_back(score);
		cards[1].push_back(bid);
		cards[2].push_back(i);
		cs.push_back(card);
	}
	sort(cards[2].begin(), cards[2].end(), [&](const auto & a, const auto & b) {
		return cards[0][a] < cards[0][b] || (cards[0][a] == cards[0][b] && (smaller(cs[a], cs[b])));
	});
	for(int i = 0; i < n;) {
		sum += (cards[1][cards[2][i]] * (++i));
	}


	return sum;
}

unordered_map<char, int> m2 = {{'J', 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5}, {'7', 6}, {'8', 7}, {'9', 8}, {'T', 9}, {'Q', 10}, {'K', 11}, {'A', 12}};

bool smaller2(string a, string b) {
	for (char & c : a) {
		c = m2[c];
	}
	for (char & c : b) {
		c = m2[c];
	}
	return a < b;
}

ll r2(string card) {
	unordered_map<char, int> ump;
	for(char & c : card) {
		if(c != 'J') {
			++ump[c];
		}
	}

	int mx = 0, i = -1;
	for(auto & a : ump) {
		if(a.second > mx) {
			i = a.first;
			mx = a.second;
		}
	}
	mx += count(card.begin(), card.end(), 'J');


	if(mx == 3) {
		for(auto & a : ump) {
			if(a.second == 2 && a.first != i) {
				return 4;
			}
		}
		return 3;
	}
	if(mx == 2) {
		for(auto & a : ump) {
			if(a.second == 2 && a.first != i) {
				return 2;
			}
		}
		return 1;
	}
	if(mx == 5) return 6;
	if(mx == 4) return 5;
	if(mx == 1) return 0;
	return -1;
}

ll part2() {
	ll sum  = 0;
	ll n;
	cin >> n;

	vector<vector<ll>> cards(3, vector<ll>());
	vector<string> cs;
	for(int i = 0; i < n; ++i) {
		string card;
		ll bid;
		cin >> card;
		cin >> bid;

		ll score = r2(card);
		cards[0].push_back(score);
		cards[1].push_back(bid);
		cards[2].push_back(i);
		cs.push_back(card);
	}
	sort(cards[2].begin(), cards[2].end(), [&](const auto & a, const auto & b) {
		return cards[0][a] < cards[0][b] || (cards[0][a] == cards[0][b] && (smaller2(cs[a], cs[b])));
	});
	for(int i = 0; i < n;) {
		sum += (cards[1][cards[2][i]] * (++i));
	}


	return sum;
}

int main() {

	cout << part2();
	return 0;
}