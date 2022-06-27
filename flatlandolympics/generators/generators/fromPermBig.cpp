// generate a testcase from a permutation
// the permutation should be zero indexed
#include "icpc_gen_helper.h"
#include <bits/stdc++.h>

using namespace icpc_gen_helper;
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

struct testcase {
	pt a, b;
	vector<pt> data;
};

bool isPerm(vector<ll> perm) {
	sort(all(perm));
	for (ll i = 0; i < sz(perm); i++) if (perm[i] != i) return false;
	return true;
}

ll cross(pt a, pt b) {return imag(conj(a) * b);}

pt lineIntersection(pt p0, pt p1, pt p2, pt p3) {
	ll a = cross(p1 - p0, p3 - p2);
	ll b = cross(p2 - p0, p3 - p2);
	ld c = (ld)b/a;

	ll x = round(real(p0) + c * real(p1 - p0));
	ll y = round(imag(p0) + c * imag(p1 - p0));
	return {x, y};
}

testcase gen(const vector<ll>& perm) {
	assert(isPerm(perm));
	assert(!perm.empty());
	ll n = sz(perm);
	testcase res;
	res.a = pt(-2*n, 0);
	res.b = pt(0, -2*n);
	for (ll i = 0; i < n; i++) {
		res.data.push_back(lineIntersection(res.a, pt(0, 2*(n - 1- perm[i])), res.b, pt(2*i, 0)));
	}
	return res;
}

vector<ll> inverse(const vector<ll>& perm) {
	vector<ll> inv(sz(perm));
	for (ll i = 0; i < sz(perm); i++) {
		inv[perm[i]] = i;
	}
	return inv;
}

int main(int argc, char** argv) {
	Init(argc, argv);

	ll n = std::stoull(getParam("--n"));
	vector<ll> perm(n);
	if (hasFlag("--manual")) {
		ll i = 0;
		while (string(argv[i]) != "--n") i++;
		i += 2;
		for (ll j = 0; j < n; j++) {
			assert(i+j < argc);
			perm[j] = stoull(argv[i+j]);
		}
	} else if (hasFlag("--random")) {
		for (ll i = 0; i < n; i++) perm[i] = i;
		shuffle(all(perm), rng);
	} else {
		cerr << "needs either 'manual' or 'random' as parameter" << endl;
		return 1;
	}

	if (hasFlag("--inverse")) perm = inverse(perm);
	if (hasFlag("--reverse")) reverse(all(perm));

	auto test = gen(perm);
	shuffle(all(test.data), rng);

	cout << real(test.a) << " " << imag(test.a) << " ";
	cout << real(test.b) << " " << imag(test.b) << endl;
	cout << test.data.size() << endl;
	for (auto e : test.data) {
		cout << real(e) << " " << imag(e) << endl;
	}
}
