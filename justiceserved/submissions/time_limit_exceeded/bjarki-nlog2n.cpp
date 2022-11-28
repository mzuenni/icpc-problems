#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

struct event {
	int time;
	int suspect;
	int suspect_end;
	bool operator <(const event &other) const {
		if (time != other.time) return time < other.time;
		if (suspect_end != other.suspect_end) return suspect_end > other.suspect_end;
		return suspect < other.suspect;
	}
};

multiset<int> segtree[4*((int)2e5)+10];

int st_max(int at, int l, int r, int ql, int qr) {
	if (qr < l) return -1;
	if (r < ql) return -1;
	if (ql <= l && r <= qr) {
		if (segtree[at].empty()) {
			return -1;
		}
		return *segtree[at].rbegin();
	}
	int m = (l+r)/2;
	return max(
		st_max(2*at+1, l, m, ql, qr),
		st_max(2*at+2, m+1, r, ql, qr)
	);
}
void st_add(int at, int l, int r, int qi, int value) {
	if (qi < l) return;
	if (r < qi) return;
	segtree[at].insert(value);
	if (l == r) {
		return;
	}
	int m = (l+r)/2;
	st_add(2*at+1, l, m, qi, value);
	st_add(2*at+2, m+1, r, qi, value);
}

int main() {
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<event> evs;
	set<int> ends;
	for (int i = 0; i < n; i++) {
		int a, d;
		cin >> a >> d;
		evs.emplace_back(event {a, i, a+d});
		ends.insert(a+d);
	}
	map<int,int> end_index;
	for (auto end : ends) {
		end_index.insert({end, end_index.size()});
	}
	int st_end = end_index.size()+1;
	sort(evs.begin(), evs.end());
	vector<int> result(n);
	for (auto ev : evs) {
		int end = ev.suspect_end;
		int mx = st_max(0, 0, st_end, end_index[end], st_end);
		result[ev.suspect] = mx+1;
		st_add(0, 0, st_end, end_index[end], mx+1);
	}
	for (int i = 0; i < n; i++) {
		cout << result[i] << endl;
	}
	return 0;
}
