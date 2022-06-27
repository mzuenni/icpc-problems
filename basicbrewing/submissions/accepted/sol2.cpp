#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using lld = __float128;

constexpr ld reps = 1e-8;
constexpr lld eps = reps*reps;

istream& operator>>(istream& is, lld& x) {
	ld y;
	is >> y;
	x = y;
	return is;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	lld p;
	cin >> n >> p;
	ll sum = 0;
	vector<pair<lld, lld>> less, more;
	for (ll i = 0; i < n; i++) {
		lld c, cp;
		cin >> c >> cp;
		sum += c;
		if (cp <= p) less.push_back({cp, c});
		else more.push_back({cp, c});
	}

	sort(all(less));
	reverse(all(less));
	sort(all(more));
	lld res = 0;

	auto calc = [&](lld x){
		lld total = 0;
		lld part = 0;
		for (auto e : less) {
			lld y = min(e.second, x-total);
			total += y;
			part += y*e.first;
		}
		for (auto e : more) {
			//total += e.second;
			//part += e.first*e.second;

			//part/total <= p;
			//(part+y*e.first)/(total+y) <= p;
			//part+y*e.first <= p*(total+y);
			//part+y*e.first <= p*total+p*y;
			//y*e.first-p*y <= p*total-part;
			//y*(e.first-p) <= p*total-part;
			//y <= (p*total-part)/(e.first-p);
			lld y = min(e.second, (p*total-part)/(e.first-p));
			total += y;
			part += y*e.first;
		}
		res = total;
		return part/total >= p-eps;
	};

	lld l = 0;
	lld r = sum;
	for (ll i = 0; i < 1000; i++) {
		lld m = (l + r) / 2;
		if (calc(m)) {
			l = m;
		} else {
			r = m;
		}
	}
	calc(l);
	cout << fixed << setprecision(10) << (ld)res << endl;
}
