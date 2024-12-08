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
		bool correct = true;
		std::unordered_map<int, bool> prev;
		std::vector<int> nums;
		std::stringstream ss {line};
		std::string s;
		while (std::getline(ss, s, ',')) {
			int num = std::stoi(s);
			if (prev.contains(num) && brules.contains(num)) {
				for (int before : brules.at(num)) {
					if (!prev.contains(before)) {
						correct = false;
					}
				}
			}
			if (arules.contains(num)) {
				for (int after : arules.at(num)) {
					if (prev.contains(after)) {
						correct = false;
					}
				}
			}
			prev[num] = true;
			nums.push_back(num);
		}
		if (!correct) {
			std::unordered_map<int, bool> prev2;
			for (int i = 0; i < (int)nums.size(); ++i) {
				int num = nums[i];
				if (arules.contains(num)) {
					int m = i;
					for (int after : arules.at(num)) {
						if (prev2.contains(after)) {
							for (int j = 0; j < m; ++j) {
								if (nums[j] == after) {
									m = j;
									break;
								}
							}
						}
					}
					if (m < i) {
						nums.erase(nums.begin()+i);
						nums.insert(nums.begin()+m, num);
					}
				}
				prev2[num] = true;
			}
			total += nums[nums.size()/2];
		}
	}

	std::cout << total << '\n';
}
