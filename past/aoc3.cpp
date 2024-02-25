#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;


vector<string> s;
int rows=140, cols=140;


long long part1() {
	for(int i = 0; i < 140; ++i) {
		string in;
		cin >> in;
		s.push_back(in);
	}
	long long sum = 0;
	for(int i = 0; i < 140; ++i) {
		int number = 0;
		bool valid = 0;
		for(int j = 0; j < 140; ++j) {
			if(!isdigit(s[i][j])) {
				if (valid) sum += number;
				number = 0;
				valid = 0;
			}
			else {
				number = number * 10 + (s[i][j] - '0');

				if (i > 0 && !isdigit(s[i-1][j]) && s[i-1][j] != '.') valid = 1;
				else if (i < 139 && !isdigit(s[i+1][j]) && s[i+1][j] != '.') valid = 1;
				else if (j > 0 && !isdigit(s[i][j-1]) && s[i][j-1] != '.') valid = 1;
				else if (j < 139 && !isdigit(s[i][j+1]) && s[i][j+1] != '.') valid = 1;

				else if (i < 139 && j < 139 && !isdigit(s[i+1][j+1]) && s[i+1][j+1] != '.') valid = 1;
				else if (i < 139 && j > 0 && !isdigit(s[i+1][j-1]) && s[i+1][j-1] != '.') valid = 1;
				else if (i > 0 && j < 139 && !isdigit(s[i-1][j+1]) && s[i-1][j+1] != '.') valid = 1;
				else if (i > 0  && j > 0 && !isdigit(s[i-1][j-1]) && s[i-1][j-1] != '.') valid = 1;
			}
		}
		if(valid) {
			sum += number;
		}
	}
	return sum;
}


void parse() {
	for(int i = 0; i < rows; ++i) {
		string in;
		cin >> in;
		s.push_back(in);
	}
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			if(s[i][j] != '*') {
				if(!isdigit(s[i][j])) {
					s[i][j] = '.';
				}
			}
			else {
				int adj = 0;

				if (i < 139 && j > 0 && isdigit(s[i+1][j-1])) ++adj;
				if (i < 139 && isdigit(s[i+1][j]) && (j == 0 || !isdigit(s[i+1][j-1]))) ++adj;
				if (i < 139 && j < 139 && isdigit(s[i+1][j+1]) && !isdigit(s[i+1][j])) ++adj;
				
				if (i > 0  && j > 0 && isdigit(s[i-1][j-1])) ++adj;
				if (i > 0 && isdigit(s[i-1][j]) && (j == 0 || !isdigit(s[i-1][j-1]))) ++adj;
				if (i > 0 && j < 139 && isdigit(s[i-1][j+1]) && !isdigit(s[i-1][j])) ++adj;


				if (j > 0 && isdigit(s[i][j-1])) ++adj;
				if (j < 139 && isdigit(s[i][j+1])) ++adj;

				if(adj != 2) {
					s[i][j] = '.';
				}
			}
		}
	}
}

unordered_map<int, long long> ump;

long long part2() {
	parse();

	long long sum = 0;
	for(int i = 0; i < rows; ++i) {
		long long number = 0;
		unordered_set<long long> store;
		for(int j = 0; j < cols; ++j) {
			if(!isdigit(s[i][j])) {
				if(number) {
					for(const auto& a : store) {
						sum += number * ump[a];
						ump[a] += number;
					}
					number = 0;
					store.clear();
				}
			}
			else {
				number = number * 10 + (s[i][j] - '0');

				if (i < 139 && s[i+1][j] == '*') store.insert((i+1)*140+j);
				if (j > 0 && s[i][j-1] == '*') store.insert(i*140+j-1);
				if (i < 139 && j < 139 && s[i+1][j+1] == '*') store.insert((i+1)*140+j+1);
				if (i < 139 && j > 0 && s[i+1][j-1] == '*') store.insert(i*140+140+j-1);


				if (i > 0 && s[i-1][j] == '*') store.insert(i*140-140+j);
				if (j < 139 && s[i][j+1] == '*') store.insert(i*140+j+1);
				if (i > 0 && j < 139 && s[i-1][j+1] == '*') store.insert(i*140-140+j+1);
				if (i > 0  && j > 0 && s[i-1][j-1] == '*') store.insert(i*140-140+j-1);
			}
		}
		if(number) {
			for(const auto& a: store) {
				sum += number * ump[a];	
				ump[a] += number;
			}
		}
	}
	return sum;
}


int main() {

	cout << part2();
	return 0;
}