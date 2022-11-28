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
	// start -> max answer
	map<int, int> best = {{-1, 0}};
	int i = 0;
	for(auto& s : ps) {
		cin >> s.l >> s.r;
		s.r += s.l;
		s.i = i++;
	}
	sort(begin(ps), end(ps), [](auto& l, auto& r) { return std::pair{l.r, -l.l} > std::pair{r.r, -r.l}; });
	for(auto& s : ps) {
		s.ans   = prev(best.upper_bound(s.l))->second + 1;
		auto it = best.insert_or_assign(s.l, s.ans).first;
		if(next(it) != best.end() && next(it)->second <= s.ans) best.erase(next(it));
	}
	sort(begin(ps), end(ps), [](auto& l, auto& r) { return l.i < r.i; });
	for(auto& s : ps) cout << s.ans-1 << ' ';
	cout << endl;
}
