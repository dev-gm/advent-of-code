#include <bits/stdc++.h>

template<const char str[], int len = 4>
void check_match(int& count, int& match, char ch) {
	if (ch == str[match]) {
		++match;
		if (match == len) {
			++count;
			match = 0;
		}
	} else {
		match = 0;
		if (ch == str[0]) {
			++match;
		}
	}
}

static const char xmas[] = "XMAS";
static const char samx[] = "SAMX";

int main() {
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(std::cin, line)) {
		lines.push_back(line);
	}
	int count = 0, y = lines.size(), x = lines[0].size(), match, rmatch;
	for (int i = 0; i < y; ++i) {
		match = rmatch = 0;
		for (int j = 0; j < x; ++j) {
			check_match<xmas>(count, match, lines[i][j]);
			check_match<samx>(count, rmatch, lines[i][j]);
		}
	}
	for (int j = 0; j < x; ++j) {
		match = rmatch = 0;
		for (int i = 0; i < y; ++i) {
			check_match<xmas>(count, match, lines[i][j]);
			check_match<samx>(count, rmatch, lines[i][j]);
		}
	}
	for (int start_i = 0, start_j = 0; start_i < y-1 && start_j < x; ++start_i, ++start_j) {
		match = rmatch = 0;
		for (int i = start_i+1, j = 0; i < y && j < x; ++i, ++j) {
			check_match<xmas>(count, match, lines[i][j]);
			check_match<samx>(count, rmatch, lines[i][j]);
		}
		match = rmatch = 0;
		for (int i = 0, j = start_j; i < y && j < x; ++i, ++j) {
			check_match<xmas>(count, match, lines[i][j]);
			check_match<samx>(count, rmatch, lines[i][j]);
		}
		match = rmatch = 0;
		for (int i = start_i, j = 0; i >= 0 && j < x; --i, ++j) {
			check_match<xmas>(count, match, lines[i][j]);
			check_match<samx>(count, rmatch, lines[i][j]);
		}
		match = rmatch = 0;
		for (int i = y-1, j = start_j; i >= 0 && j < x; --i, ++j) {
			check_match<xmas>(count, match, lines[i][j]);
			check_match<samx>(count, rmatch, lines[i][j]);
		}
	}
	std::cout << count << "\n";
}
