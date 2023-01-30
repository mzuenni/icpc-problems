#include <iostream>
#include <set>

using namespace std;

int main() {
	int t; cin >> t;
	while (t-->0) {
		int n; cin >> n;
		multiset<int> a;
		for (int i = 0; i < n; i++) {
			int x; cin >> x;
			a.emplace(x);
		}
		int res = 0;
		for (; a.size() >= 3; res++) {
			int f = *a.begin(); a.erase(a.begin());
			int new_c = *prev(a.end()); a.erase(prev(a.end()));
			new_c += *prev(a.end()); a.erase(prev(a.end()));
			new_c++, f--;
			a.emplace(new_c);
			if (f > 0) a.emplace(f);
		}
		if (a.size() == 2)
			if (*a.begin() > 1) res++; // merge the two chains
		res++; // join single remaining chain
		cout << res << endl;
	}
	return 0;
}
