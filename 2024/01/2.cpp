#include <bits/stdc++.h>

int main() {
	std::vector<int> lhs;
	std::unordered_map<int, int> rhs;
	int e1, e2;
	while (std::cin >> e1 >> e2) {
		lhs.push_back(e1);
		rhs[e2]++;
	}
	std::cout << std::transform_reduce(lhs.begin(), lhs.end(), 0,
		std::plus<>(), [&rhs](int e) { return e * rhs[e]; }) << '\n';
}
