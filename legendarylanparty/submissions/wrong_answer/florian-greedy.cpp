#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	long long n, m;
	std::cin >> n >> m;

	std::vector<std::pair<long long, long long>> cables(n);

	for(long long i = 0; i < n; ++i) {
		std::cin >> cables[i].first >> cables[i].second;
	}

	// Sort small ports to front
	std::sort(begin(cables), end(cables), [](auto &a, auto &b) {
		return a.first < b.first;
	});


	long long cost = 0;
	long long len = 0;
	for (auto [c, m]: cables) {
		cost += c * len;
		len += m;
	}

	std::cout << cost << std::endl;
}
