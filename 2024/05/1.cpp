#include <bits/stdc++.h>

int main() {
	std::string line;
	// before, after
	std::unordered_map<int, std::vector<int>> arules;
	// after, before
	std::unordered_map<int, std::vector<int>> brules;

	while (std::getline(std::cin, line)) {
		if (line.empty()) {
			break;
		}
		std::stringstream ss {line};
		std::string s;
		std::getline(ss, s, '|');
		int a = std::stoi(s);
		std::getline(ss, s, '|');
		int b = std::stoi(s);
		arules[a].push_back(b);
		brules[b].push_back(a);
	}

	int total = 0;
	while (std::getline(std::cin, line)) {
		std::unordered_map<int, bool> prev;
		std::vector<int> nums;
		std::stringstream ss {line};
		std::string s;
		while (std::getline(ss, s, ',')) {
			int num = std::stoi(s);
			if (prev.contains(num) && brules.contains(num)) {
				for (int before : brules.at(num)) {
					if (!prev.contains(before)) {
						goto while_end;
					}
				}
			}
			if (arules.contains(num)) {
				for (int after : arules.at(num)) {
					if (prev.contains(after)) {
						goto while_end;
					}
				}
			}
			prev[num] = true;
			nums.push_back(num);
		}
		total += nums[nums.size()/2];
	while_end:
	}

	std::cout << total << '\n';
}
