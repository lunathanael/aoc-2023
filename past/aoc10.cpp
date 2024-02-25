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

using namespace std;

#define ll long long int

ll part1() {
	ll sum = 0;
	int r, c;
	cin >> r >> c;

	string b[r];
	for(int i = 0; i < r; ++i) {
		string s;
		cin >> s;
		b[i] = s;
	}

	int rr = -1, cc = -1;
	for(int i = 0; i < r; ++i) {
		for(int j = 0; j < c; ++j) {
			if(b[i][j] == 'S') {
				rr = i;
				cc = j;
				break;
			}
		}
		if(rr != -1) break;
	}

	int ii = rr, jj = cc, previ = rr, prevj = cc;
	do {
		++sum;
		if(b[ii][jj] == '|') {
			if(ii + 1 != previ || jj != prevj) {
				previ = ii;
				prevj = jj;
				++ii;
			}
			else {
				previ = ii;
				prevj = jj;
				--ii;
			}
		}
		else if (b[ii][jj] == '-') {
			if(ii != previ || jj+1 != prevj) {
				previ = ii;
				prevj = jj;
				++jj;
			}
			else {
				previ = ii;
				prevj = jj;
				--jj;
			}
		}
		else if (b[ii][jj] == 'L') {
			if(ii - 1 != previ || jj != prevj) {
				previ = ii;
				prevj = jj;
				--ii;
			}
			else {
				previ = ii;
				prevj = jj;
				++jj;
			}
		}
		else if (b[ii][jj] == 'J') {
			if(ii - 1 != previ || jj != prevj) {
				previ = ii;
				prevj = jj;
				--ii;
			}
			else {
				previ = ii;
				prevj = jj;
				--jj;
			}
		}
		else if (b[ii][jj] == '7') {
			if(ii + 1 != previ || jj != prevj) {
				previ = ii;
				prevj = jj;
				++ii;
			}
			else {
				previ = ii;
				prevj = jj;
				--jj;
			}
		}
		else if (b[ii][jj] == 'F') {
			if(ii + 1 != previ || jj != prevj) {
				previ = ii;
				prevj = jj;
				++ii;
			}
			else {
				previ = ii;
				prevj = jj;
				++jj;
			}
		}
		else if (b[ii][jj] == 'S') {
			++ii;
		}
	}
	while (b[ii][jj] != 'S');
	

	return sum / 2;
}

ll part2() {
	ll sum = 0;
	int r, c;
	cin >> r >> c;

	string b[r];
	for(int i = 0; i < r; ++i) {
		string s;
		cin >> s;
		b[i] = s;
	}

	int rr = -1, cc = -1;
	for(int i = 0; i < r; ++i) {
		for(int j = 0; j < c; ++j) {
			if(b[i][j] == 'S') {
				rr = i;
				cc = j;
				break;
			}
		}
		if(rr != -1) break;
	}

	vector<vector<bool>> A(r, vector<bool>(c, false));
	int ii = rr, jj = cc, previ = rr, prevj = cc;
	b[ii][jj] = '7';
	do {
		A[ii][jj] = 1;
		if(b[ii][jj] == '|') {
			if(ii + 1 != previ || jj != prevj) {
				previ = ii;
				prevj = jj;
				++ii;
			}
			else {
				previ = ii;
				prevj = jj;
				--ii;
			}
		}
		else if (b[ii][jj] == '-') {
			if(ii != previ || jj+1 != prevj) {
				previ = ii;
				prevj = jj;
				++jj;
			}
			else {
				previ = ii;
				prevj = jj;
				--jj;
			}
		}
		else if (b[ii][jj] == 'L') {
			if(ii - 1 != previ || jj != prevj) {
				previ = ii;
				prevj = jj;
				--ii;
			}
			else {
				previ = ii;
				prevj = jj;
				++jj;
			}
		}
		else if (b[ii][jj] == 'J') {
			if(ii - 1 != previ || jj != prevj) {
				previ = ii;
				prevj = jj;
				--ii;
			}
			else {
				previ = ii;
				prevj = jj;
				--jj;
			}
		}
		else if (b[ii][jj] == '7') {
			if(ii + 1 != previ || jj != prevj) {
				previ = ii;
				prevj = jj;
				++ii;
			}
			else {
				previ = ii;
				prevj = jj;
				--jj;
			}
		}
		else if (b[ii][jj] == 'F') {
			if(ii + 1 != previ || jj != prevj) {
				previ = ii;
				prevj = jj;
				++ii;
			}
			else {
				previ = ii;
				prevj = jj;
				++jj;
			}
		}
	}
	while (!A[ii][jj]);

	int ct = 0;
	for(int i = 0; i < r; ++i) {
		bool in  = false;
		for(int j = 0; j < c; ++j) {
			if(A[i][j]) {
				if(b[i][j] == '|' || b[i][j] == 'J' || b[i][j] == 'L') {
					in ^= 1;
				}
			}
			else {
				ct += in;
			}
		}
	}

	return ct;
}

int main() {

	cout << part2();
	return 0;
}