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

ll calc(vector<ll> & v) {
	if (all_of(v.begin(), v.end(), [&](int x){ return x==v[0]; })) {
		return v[0];
	}
	vector<ll> diff;
	for(int i = 1; i < v.size(); ++i) {
		diff.push_back(v[i] - v[i-1]);
	}
	return v.back() + calc(diff);
}

ll part1() {
	ll sum = 0;
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i) {
		vector<ll>v;
		for(int j = 0; j < 21; ++j) {
			ll a;
			cin >> a;
			v.push_back(a);
		}
		sum += calc(v);
	}
	

	return sum;
}


ll part2() {
	ll sum = 0;
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i) {
		vector<ll>v;
		for(int j = 0; j < 21; ++j) {
			ll a;
			cin >> a;
			v.push_back(a);
		}
		reverse(v.begin(), v.end());
		sum += calc(v);
	}
	

	return sum;
}

int main() {

	cout << part2();
	return 0;
}