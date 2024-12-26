#include <bits/stdc++.h>

#define IDX(rlen, i, j) ((rlen*i)+j)

bool follow_path(int &count, std::unordered_map<int, std::vector<int>> &main_map, int &cur_perp, int &cur_main, bool *spaces, int rlen, int mlen, bool narrow, bool v) {
	int m = narrow ? -1 : mlen;
	if (main_map.count(cur_main)) {
		for (int l : main_map[cur_main]) {
			if (narrow) {
				if (l < cur_perp) {
					m = std::max(m, l);
				}
			} else {
				if (l > cur_perp) {
					m = std::min(m, l);
				}
			}
		}
	}
	for (int l = cur_perp; narrow ? l > m : l < m; narrow ? --l : ++l) {
		int idx = v ? IDX(rlen, l, cur_main) : IDX(rlen, cur_main, l);
		if (!spaces[idx]) {
			spaces[idx] = true;
			++count;
		}
	}
	cur_perp = narrow ? m+1 : m-1;
	if (m == (narrow ? -1 : mlen)) {
		return true;
	}
	return false;
}

int main() {
	std::unordered_map<int, std::vector<int>> horiz, vert;
	int cur[2];
	std::string s;
	int i, j = 0;
	for (i = 0; std::getline(std::cin, s); ++i) {
		for (j = 0; (ulong)j < s.size(); ++j) {
			switch (s[j]) {
			case '#':
				horiz[i].push_back(j);
				vert[j].push_back(i);
				break;
			case '^':
				cur[0] = i;
				cur[1] = j;
				break;
			}
		}
	}
	bool spaces[i*j];
	for (int x = 0; x < i*j; ++x) {
		spaces[x] = false;
	}
	int iter = 0, count = 0;
	bool exited = false;
	while (!exited) {
		switch (iter%4) {
			case 0:
				exited = follow_path(count, vert, cur[0], cur[1], (bool *)spaces, j, 0, true, true);
				break;
			case 1:
				exited = follow_path(count, horiz, cur[1], cur[0], (bool *)spaces, j, i, false, false);
				break;
			case 2:
				exited = follow_path(count, vert, cur[0], cur[1], (bool *)spaces, j, j, false, true);
				break;
			case 3:
				exited = follow_path(count, horiz, cur[1], cur[0], (bool *)spaces, j, 0, true, false);
				break;
		}
		++iter;
	}
	std::cout << count << "\n";
	return 0;
}
