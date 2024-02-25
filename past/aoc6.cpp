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

ll findlr(ll t, ll d) {
	ll c = 0;
	for(ll i  = 0; i <= t; ++i) {
		c += (i * (t-i) > d);
	}
	return c;
}


ll part1() {
	vector<ll> time;
	vector<ll> dist;

	ll n;
	cin >> n;

	string disc;
	cin >> disc;
	for(int i = 0; i < n; ++i) {
		ll a;
		cin >> a;
		time.push_back(a);
	}

	cin >> disc;
	for(int i = 0; i < n; ++i) {
		ll a;
		cin >> a;
		dist.push_back(a);
	}


	ll sum = 1;
	for(int i = 0; i < n; ++i) {
		ll left = findlr(time[i], dist[i]);
		sum *= left;
	}

	return sum;

}


ll part2() {
	string disc;
	cin >> disc;
	ll t, d;
	cin >> t;
	cin >> disc;
	cin >> d;

	ll sum = findlr(t, d);

	return sum;

}


unordered_map<char, ll> ump = {
	{'=', -2}, {'-', -1}, {'0', 0}, {'1', 1}, {'2', 2}
};



int main() {

	cout << part2();
	return 0;
}