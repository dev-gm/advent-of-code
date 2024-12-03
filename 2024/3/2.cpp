#include <bits/stdc++.h>

int main() {
	int out = 0;

	std::string line;
	bool enable = true;
	while (std::getline(std::cin, line)) {
		std::regex reg {"(mul\\([0-9]*,[0-9]*\\)|do\\(\\)|don\\'t\\(\\))"};
		std::regex_token_iterator<std::string::iterator> rend,
			iter { line.begin(), line.end(), reg };
		for (; iter != rend; *iter++) {
			if (iter->str().contains("don't")) {
				enable = false;
			} else if (iter->str().contains("do")) {
				enable = true;
			} else if (enable) {
				out += std::ranges::fold_left_first(
					iter->str().substr(4, iter->length()-1)
						| std::views::split(',')
						| std::views::transform([](auto str) {
							return std::stoi(std::string_view(str).begin());
						}),
					std::multiplies<>()
				).value_or(0);
			}
		}
	}

	std::cout << out << "\n";
}
