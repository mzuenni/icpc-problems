#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <ranges>

using namespace std;

using u64 = uint64_t;

int main()
{
	u64 n;
	cin >> n;
	vector<pair<u64, u64>> d(n);
	for (auto& [a, b] : d)
		cin >> a >> b;
	for (u64 i = 0; i < n; i++)
		d.emplace_back(d[i].second, d[i].first);

	sort(d.begin(), d.end());

	u64 res = 0;
	for (auto[a,b] : d | std::views::reverse) {
		if (a*a*a < res)
			break;
		bool ok = false;
		for (u64 i = 2*n; i--> 0; )
			if (d[i].first < b)
				break;
			else if (d[i].second >= b) {
				ok = true;
				break;
			}
		if (ok)
			res = max(res, a*b*b);
	}

	cout << res << '\n';
	return 0;
}
