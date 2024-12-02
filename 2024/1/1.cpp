#include <bits/stdc++.h>

int main() {
	std::vector<int> lhs, rhs;
	int e1, e2;
	while (std::cin >> e1 >> e2) {
		lhs.push_back(e1);
		rhs.push_back(e2);
	}
	std::sort(lhs.begin(), lhs.end());
	std::sort(rhs.begin(), rhs.end());
	std::cout << std::transform_reduce(lhs.begin(), lhs.end(), rhs.begin(), 0,
		std::plus<>(), [](int f, int s) { return abs(f - s); }) << '\n';
}
