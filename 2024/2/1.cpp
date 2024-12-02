#include <bits/stdc++.h>

int main() {
	int safe_count = 0;
	std::string line;
	while (std::getline(std::cin, line)) {
		safe_count += (bool)std::ranges::fold_left_first(
			line
				| std::views::split(' ')
				| std::views::transform([](auto level) {
					return std::stoi(std::string_view(level).begin());
				})
				| std::views::pairwise_transform([](int a, int b) {
					int diff = abs(a - b);
					return (diff >= 1 && diff <= 3) ? a - b : 0;
				}),
			[](int a, int b) {
				return a && (a > 0) == (b > 0) ? b : 0;
			}
		).value_or(0);
	}
	std::cout << safe_count << "\n";
}
