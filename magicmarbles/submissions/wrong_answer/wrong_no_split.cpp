#include <bits/stdc++.h>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

vector<ll> unions, unionSize;

ll findSet(ll n) {
	if (unions[n] < 0) return n;
	return unions[n] = findSet(unions[n]);
}

void linkSets(ll a, ll b) {
	unionSize[a] = unionSize[b] = unionSize[a] + unionSize[b];
	if (unions[a] > unions[b]) unions[a] = b;
	else if (unions[b] > unions[a]) unions[b] = a;
	else {
		unions[a] = b;
		unions[b]--;
}}

void unionSets(ll a, ll b) {
	if (findSet(a) != findSet(b)) linkSets(findSet(a), findSet(b));
}

struct marble {
	ll type, id;
};

ll n, k, q;
rope<marble> state;

void erase(ll pos) {
	if (pos < 0 || pos >= sz(state)) return;
	ll id = findSet(state[pos].id);
	cout << pos << " " << unionSize[id] << endl;
	if (unionSize[id] < k) return;
	while (pos > 0 && state[pos-1].type == state[pos].type) pos--;
	state.erase(pos, unionSize[id]);
	if (pos > 0 && pos < sz(state) && state[pos-1].type == state[pos].type) {
		unionSets(state[pos-1].id, state[pos].id);
		erase(pos);
	}
}

void add(ll type, ll pos) {
	ll id = sz(unions);
	unions.push_back(-1);
	unionSize.push_back(1);

	auto it = state.insert(state.mutable_begin() + pos, marble{type, id}); // O(log(n))
	if (pos > 0 && state[pos-1].type == type) {
		unionSets(state[pos-1].id, id);
	}
	if (pos + 1 < sz(state) && state[pos+1].type == type) {
		unionSets(state[pos+1].id, id);
	}
	erase(pos);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k >> q;
	for (ll i = 0; i < n; i++) {
		ll x;
		cin >> x;
		add(x, i);
	}
	for (ll i = 0; i < q; i++) {
		ll p, x;
		cin >> p >> x;
		add(x, p);
		cout << sz(state) << endl;
	}
}
