#include <bits/stdc++.h>

int main() {
	int count = 0;
	std::string line;
	while (std::getline(std::cin, line)) {
		struct A {
			int prev = 0, prev2 = 0, i = 0;
			bool rm = false;
			enum : bool { POS, NEG } sign;

			bool valid(int diff) {
				return abs(diff) >= 1 && abs(diff) <= 3 && (diff > 0) == sign;
			}
		};
		std::array<std::optional<A>, 2> as = {A{.sign = A::POS}, A{.sign = A::NEG}};
		for (int diff : line
			| std::views::split(' ')
			| std::views::transform([](auto level) {
				return std::stoi(std::string_view(level).begin());
	   		})
			| std::views::pairwise_transform(std::minus<>())
		) {
			for (auto& a : as) {
				if (!a.has_value()) {
					continue;
				}
				if (a->i == 0) {
					a->prev = diff;
					++a->i;
					continue;
				}
				// remove first number
				if (a->i == 1 && a->valid(diff) && !a->valid(a->prev)) {
					if (a->rm) {
						a = std::nullopt;
						if (!as[0].has_value() && !as[1].has_value()) {
							break;
						}
					}
					a->rm = true;
				} else if (!a->valid(a->prev)) {
					// prev2:(a - b) prev:(b - c) diff:(c - d)
					// remove c
					if (!a->rm && a->valid(a->prev + diff)) {
						a->prev += diff;
						--a->i;
					// remove b
					} else if (!a->rm && a->i > 1 && a->valid(a->prev + a->prev2)) {
						a->prev2 += a->prev;
						a->prev = diff;
					} else {
						a = std::nullopt;
						if (!as[0].has_value() && !as[1].has_value()) {
							break;
						}
						continue;
					}
					a->rm = true;
					continue;
				}
				a->prev2 = a->prev;
				a->prev = diff;
				if (a->i == 1) {
					++a->i;
				}
			}
		}
		for (auto& a : as) {
			if (!a.has_value() || a->valid(a->prev)) {
				continue;
			}
			if (a->rm || (a->i > 1 && !a->valid(a->prev2) && !a->valid(a->prev + a->prev2))) {
				a = std::nullopt;
			}
		}
		count += as[0].has_value() || as[1].has_value();
	}
	std::cout << count << "\n";
}
