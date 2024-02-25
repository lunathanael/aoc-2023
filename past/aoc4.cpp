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

long long part1() {
	long long sum = 0;
	string a;
	for (int i = 0; i < 209; ++i) {
		unordered_set<int> ust;
		cin >> a;
		cin >> a;
		for(int j = 0; j < 10; ++j) {
			cin >> a;
			ust.insert(stoi(a));
		}
		cin >> a;
		long long winning = 1;
		for(int j = 0; j < 25; ++j) {
			cin >> a;
			if(ust.find(stoi(a)) != ust.end()) {
				winning <<= 1;
			}
		}
		sum += winning >> 1;
	}
	return sum;
}

long long part2() {
	vector<long long> count(209, 1);
	string a;
	for (int i = 0; i < 209; ++i) {
		unordered_set<int> ust;
		long long wins = 0;
		cin >> a;
		cin >> a;
		for(int j = 0; j < 10; ++j) {
			cin >> a;
			ust.insert(stoi(a));
		}
		cin >> a;
		for(int j = 0; j < 25; ++j) {
			cin >> a;
			if(ust.find(stoi(a)) != ust.end()) {
				++wins;
			}
		}

		for(int j = i + 1; j <= i + wins; ++j) {
			if(j >= count.size())	break;
			count[j] += count[i];
		}
	}
	return accumulate(count.begin(), count.end(), 0ll);
}



int main() {

	cout << part2();
	return 0;
}