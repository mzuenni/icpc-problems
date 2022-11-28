#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct S {
	int l, r, i, ans;
};
int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<S> ps(n);
	// end -> max answer
	map<int, int> best;
	best[2e9] = 0;
	int i     = 0;
	for(auto& s : ps) {
		cin >> s.l >> s.r;
		s.r += s.l;
		s.i = i++;
	}
	// WA because this should sort by r as well.
	sort(begin(ps), end(ps), [](auto& l, auto& r) { return l.l < r.l; });
	for(auto& s : ps) {
		s.ans   = best.lower_bound(s.r)->second + 1;
		auto it = best.insert_or_assign(s.r, s.ans).first;
		if(it != best.begin() && prev(it)->second <= s.ans) best.erase(prev(it));
	}
	sort(begin(ps), end(ps), [](auto& l, auto& r) { return l.i < r.i; });
	for(auto& s : ps) cout << s.ans-1 << ' ';
	cout << endl;
}
