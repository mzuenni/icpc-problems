#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

vector<int> kmpPreprocessing(const string& sub) {
	vector<int> b(sz(sub) + 1);
	b[0] = -1;
	for (int i = 0, j = -1; i < sz(sub);) {
		while (j >= 0 && sub[i] != sub[j]) j = b[j];
		b[++i] = ++j;
	}
	return b;
}
vector<int> kmpSearch(const string& s, const string& sub) {
	vector<int> result, pre = kmpPreprocessing(sub);
	for (int i = 0, j = 0; i < sz(s);) {
		while (j >= 0 && s[i] != sub[j]) j = pre[j];
		i++; j++;
		if (j == sz(sub)) {
			result.push_back(i - j);
			j = pre[j];
	}}
	return result;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> s;
	auto tmp = kmpSearch(s+s, s);
	set<int> pos(all(tmp));

	ll cur = 0;
	ll i = 0;
	do {
		if (s[i] == '(') cur++;
		else cur--;
		i++;
		if (cur == 0 && pos.find(i) == pos.end()) break;
	} while(i < sz(s));
	if (i < sz(s)) {
		rotate(s.begin(), s.begin() + i, s.end());
		cout << s << endl;
	} else {
		cout << "no" << endl;
	}
}
