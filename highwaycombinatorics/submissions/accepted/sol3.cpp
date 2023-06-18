#include <bits/stdc++.h>
using namespace std;
 
#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()
 
using ll = long long;
using ld = long double;

constexpr ll mod = 1000000007;
constexpr ll lim = 200;

//not checked
constexpr ll baseLim = 150000;

mt19937 rng(123456789);
ll rint(ll l, ll r) {
	return uniform_int_distribution<ll>(l, r-1)(rng);
}

ll powMod(ll a, ll b = mod-2, ll n = mod) {
	ll res = 1;
	while (b > 0) {
		if (b & 1) res = (a * res) % n;
		a = (a * a) % n;
		b /= 2;
	}
	return res;
}

struct entry {
	ll val, ops;
	basic_string<ll> fibs;
	bool operator<(const entry& o) const {
		if(val != o.val) return val < o.val;
		if(ops != o.ops) return ops < o.ops;
		return false;
	}
	bool operator==(const entry& o) const {
		if(val != o.val) return false;
		if(ops != o.ops) return false;
		return true;
	}
};

vector<entry> fibs;
vector<entry> base;
void precalc() {
	ll f0 = 1;
	ll f1 = 1;
	for (ll i = 0; i < 101; i++) {
		swap(f0, f1);
		f1 += f0;
		f1 %= mod;
		fibs.push_back({f1, i + 2, {i}});
	}

	while (sz(base) < baseLim) {
		ll n = rint(70, lim/2);
		ll k = rint(3, 20);

		vector<ll> todo(k);
		for (ll& x : todo) x = rint(0, n-3*k);
		todo.back() = n-3*k;
		sort(all(todo));

		entry e{1,0,{}};
		ll last = 0;
		ll expected = 0;
		for (ll x : todo) {
			swap(last, x);
			x = last - x;
			expected += x;

			e.val *= fibs[x].val;
			e.val %= mod;
			e.ops += fibs[x].ops + 1;
			e.fibs.push_back(x);
		}
		base.push_back(e);
	}
	sort(all(base));
	base.erase(unique(all(base)), base.end());
}

entry solve(ll x) {
	for (const auto& e : base) {
		ll y = (x * powMod(e.val)) % mod;
		auto it = lower_bound(all(base), entry{y, 0, {}});
		if (it != base.end() && it->val == y) {
			entry res = e;
			res.val *= it->val;
			res.val %= mod;
			res.ops += it->ops + 1;
			res.fibs += it->fibs;
			return res;
		}
	}
	exit(1);
	return {-1, -1, {}};
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	precalc();
	ll x;
	cin >> x;
	if (x == 0) {
		cout << ".##" << endl;
		cout << "##." << endl;
	} else {
		entry e = solve(x);
		string res;
		for (ll x : e.fibs) {
			res += string(x + 2, '.');
			res += '#';
		}
		res.pop_back();

		cout << res << endl;
		cout << res << endl;
	}
}
