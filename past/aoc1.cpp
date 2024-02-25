#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

using namespace std;

long long part1() {
	string in;
	long long sum = 0;

	do {
		cin >> in;
		sum += (*(find_if(in.begin(), in.end(), [](const auto & ch) {
			return ch >= '0' && ch <= '9';
		}))-'0') * 10 + *(find_if(in.rbegin(), in.rend(), [](const auto & ch) {
			return ch >= '0' && ch <= '9';
		})) - '0';
	}
	while(in != "fourzqlhcjksixthreejrl9");
	return sum;
}

vector<string> numStrings = {
	"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

template <class T>
pair<int, int> findStr(T l, T r, bool rev) {
	int occurance = INT_MAX, number = -1;
	for(int i = 0; i < 9; ++i) {
		string & num = numStrings[i];
		T found;
		if (rev) {
			found = search(l, r, num.rbegin(), num.rend());
		}
		else {
			found = search(l, r, num.begin(), num.end());
		}
		if (found != r) {
			int idx = found - l;
			if(idx < occurance) {
				occurance = idx;
				number = i;
			}
		}
	}
	return {occurance, number+1};
}

long long part2() {

	string in;
	long long sum = 0;

	do {
		cin >> in;

		// find left

		int leftNumIdx = find_if(in.begin(), in.end(), [](const auto & ch) {
			return ch >= '0' && ch <= '9';
		}) - in.begin();
		int rightNumIdx = find_if(in.rbegin(), in.rend(), [](const auto & ch) {
			return ch >= '0' && ch <= '9';
		}) - in.rbegin();

		pair<int, int> leftStrIdx = findStr(in.begin(), in.end(), false);
		pair<int, int> rightStrIdx = findStr(in.rbegin(), in.rend(), true);

		if(leftNumIdx < leftStrIdx.first) {
			sum += (in[leftNumIdx] - '0') * 10;
		}
		else {
			sum += leftStrIdx.second * 10;
		}
		if(rightNumIdx < rightStrIdx.first) {
			sum += (in[in.size() - 1 - rightNumIdx] - '0');
		}
		else {
			sum += rightStrIdx.second;
		}
	}
	while(in != "fourzqlhcjksixthreejrl9");
	return sum;
}

int main() {

	cout << part2();
	return 0;
}