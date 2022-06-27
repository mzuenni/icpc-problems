#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ld eps = 1e-12;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	ld p;
	cin >> n >> p;
	ll sum = 0;
	vector<pair<ld, ld>> less, more;
	for (ll i = 0; i < n; i++) {
		ld c, cp;
		cin >> c >> cp;
		sum += c;
		if (cp <= p) less.push_back({cp, c});
		else more.push_back({cp, c});
	}

	sort(all(less));
	reverse(all(less));
	sort(all(more));
	ld res = 0;

	auto calc = [&](ld x){
		ld total = 0;
		ld part = 0;
		for (auto e : less) {
			ld y = min(e.second, x-total);
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
			ld y = min(e.second, (p*total-part)/(e.first-p));
			total += y;
			part += y*e.first;
		}
		res = total;
		return part/total >= p-eps;
	};

	ld l = 0;
	ld r = sum;
	for (ll i = 0; i < 500; i++) {
		ld m = (l + r) / 2;
		if (calc(m)) {
			l = m;
		} else {
			r = m;
		}
	}
	calc(l);
	cout << fixed << setprecision(10) << res << endl;
}
