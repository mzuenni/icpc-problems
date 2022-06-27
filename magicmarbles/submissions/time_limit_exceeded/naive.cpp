#include <bits/stdc++.h>

using namespace std;
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;

int n, k, q;
vector<int> state;

void erase(int pos) {
	if (pos < 0 || pos >= sz(state)) return;
	int x = state[pos];
	int l = pos;
	int r = pos;
	while(l > 0 && state[l-1] == x) l--;
	while(r < sz(state) && state[r] == x) r++;
	if (r-l >= k) {
		state.erase(state.begin()+l, state.begin()+r);
		erase(l);
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k >> q;
	state.assign(n, -1);


	for (int i = 0; i < n; i++) cin >> state[i];
	for (int i = 0; i < q; i++) {
		int p, x;
		cin >> p >> x;
		state.insert(state.begin() + p, x);
		erase(p);
		cout << sz(state) << "\n";
	}
}
