#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

unordered_map<string, int> ump{{"red", 0}, {"green", 1}, {"blue",2}};

vector<int> occ = {12, 13, 14};

bool poss(string s) {
	vector<int> tmp = occ;
	int num = 0;
	for(int i = 0; i < s.size(); ++i) {
		if(s[i] == ' ' || s[i] == ',') continue;
		if(s[i] == ';') {
			tmp = occ;
		}
		else if (isdigit(s[i])) {
			num = num * 10 + (s[i] - '0');
		}
		else {
			if(s[i] == 'r') {
				tmp[0] -= num;
				if(tmp[0] < 0) return false;
				i += 2;
			}
			else if (s[i] == 'g') {
				tmp[1] -= num;
				if(tmp[1] < 0) return false;
				i += 4;
			}
			else {
				tmp[2] -= num;
				if(tmp[2] < 0) return false;
				i += 3;
			}
			num = 0;
		}
	}
	return true;
}

long long powerr(string s) {
	vector<int> m = {0, 0, 0};
	vector<int> tmp = {0, 0, 0};
	int num = 0;
	for(int i = 0; i < s.size(); ++i) {
		if(s[i] == ' ' || s[i] == ',') continue;
		if(s[i] == ';') {
			m[0] = max(m[0], tmp[0]);
			m[1] = max(m[1], tmp[1]);
			m[2] = max(m[2], tmp[2]);
			tmp = {0, 0, 0};
		}
		else if (isdigit(s[i])) {
			num = num * 10 + (s[i] - '0');
		}
		else {
			if(s[i] == 'r') {
				tmp[0] += num;
				i += 2;
			}
			else if (s[i] == 'g') {
				tmp[1] += num;
				i += 4;
			}
			else {
				tmp[2] += num;
				i += 3;
			}
			num = 0;
		}
	}
	m[0] = max(m[0], tmp[0]);
	m[1] = max(m[1], tmp[1]);
	m[2] = max(m[2], tmp[2]);
	return (m[0] * m[1]) * m[2];
}

long long part1() {
	long long sum = 0;
	for(int i = 1; i <= 100; ++i) {
		string game;
  		getline(cin,game);
  		if(i < 10) {
  			game = game.substr(8, game.size() - 8);
  		}
  		else if (i < 100) {
  			game = game.substr(9, game.size() - 9);
  		}
  		else {
  			game = game.substr(10, game.size() - 10);
  		}
  		if(poss(game)) sum += i;
	}
	return sum;
}


long long part2() {
	long long sum = 0;
	for(int i = 1; i <= 100; ++i) {
		string game;
  		getline(cin,game);
  		if(i < 10) {
  			game = game.substr(8, game.size() - 8);
  		}
  		else if (i < 100) {
  			game = game.substr(9, game.size() - 9);
  		}
  		else {
  			game = game.substr(10, game.size() - 10);
  		}
  		sum += powerr(game);
	}
	return sum;
}


int main() {

	cout << part2();
	return 0;
}