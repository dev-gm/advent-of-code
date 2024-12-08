#include <bits/stdc++.h>

template<const char str[], int len = 3>
void check_match(int& count, int& match, std::vector<std::string> lines, int i, int j) {
	if (lines[i][j] == str[match]) {
		++match;
		if (match == len) {
			if ((lines[i][j-2] == str[0] && lines[i-2][j] == str[2]) ||
				(lines[i][j-2] == str[2] && lines[i-2][j] == str[0])) {
				++count;
			}
			match = 0;
		}
	} else {
		match = 0;
		if (lines[i][j] == str[0]) {
			++match;
		}
	}
}

static const char mas[] = "MAS";
static const char sam[] = "SAM";

int main() {
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(std::cin, line)) {
		lines.push_back(line);
	}
	int count = 0, y = lines.size(), x = lines[0].size(), mmatch, smatch;
	for (int start_i = 0, start_j = 0; start_i < y && start_j < x; ++start_i, ++start_j) {
		mmatch = smatch = 0;
		for (int i = start_i+1, j = 0; i < y && j < x; ++i, ++j) {
			check_match<mas>(count, mmatch, lines, i, j);
			check_match<sam>(count, smatch, lines, i, j);
		}
		mmatch = smatch = 0;
		for (int i = 0, j = start_j; i < y && j < x; ++i, ++j) {
			check_match<mas>(count, mmatch, lines, i, j);
			check_match<sam>(count, smatch, lines, i, j);
		}
	}
	std::cout << count << "\n";
}
