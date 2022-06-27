#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll mul = 1000;
constexpr ld eps = 1e-12;

ll readP() {
	ld x;
	cin >> x;
	return round(x * mul);
}

struct mix {
	ll c, cp, part;
	mix(ll _c = 0, ll _cp = 0) : 
		c(_c*mul), 
		cp(_cp), 
		part(_cp * _c) {
	}
	bool operator<(const mix& o) const {
		return cp < o.cp;
	}
};

ld solve(const vector<mix>& a,
		 const vector<mix>& b,
		 ld total,
		 ld part,
		 ll p) {
	for (auto e : a) {
		total += e.c;
		part += e.part;
	}
	for (auto e : b) {
		//(part+y*e.part)/(total+y*e.c)==p/mul
		//(part+y*e.part)*mul==p*(total+y*e.c)
		//mul*part+mul*y*e.part==p*total+p*y*e.c
		//mul*y*e.part-p*y*e.c==p*total-mul*part
		//y*(mul*e.part-p*e.c)==p*total-mul*part
		//y==(p*total-mul*part)/(mul*e.part-p*e.c)
		ld y = (p*total-mul*part)/(mul*e.part-p*e.c);
		if (y < 0) y = 0;
		if (y > 1) y = 1;
		//y = clamp(y, 0, 1);
		total += y*e.c;
		part += y*e.part;
	}
	if (abs(part*mul/total-p) > eps) return 0;
	return total;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	ll p = readP();
	vector<mix> less, more;
	ll total = 0;
	ll part = 0;
	for (ll i = 0; i < n; i++) {
		ll c;
		cin >> c;
		ll cp = readP();
		mix cur(c, cp);
		if (cp == p) {
			total += cur.c;
			part += cur.part;
		} else if (cp < p) less.push_back(cur);
		else more.push_back(cur);
	}

	sort(all(less));
	reverse(all(less));
	sort(all(more));

	ld a = solve(less, more, total, part, p);
	ld b = solve(more, less, total, part, p);

	cout << fixed << setprecision(10) << max(a, b)/mul << endl;
}