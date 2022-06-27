// generate a testcase from a permutation
// n <= 44721 must hold (else the testcase gets too big)
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

constexpr ll DIM = 1000000000;

struct testcase {
	pt a, b;
	vector<pt> data;
};

bool isPerm(vector<ll> perm) {
	sort(all(perm));
	for (ll i = 0; i < sz(perm); i++) if (perm[i] != i) return false;
	return true;
}

testcase gen(const vector<ll>& perm) {
	assert(isPerm(perm));
	assert(!perm.empty());
	ll n = sz(perm);
	ll ma = n - 1;
	ll ha = n / 2;
	testcase res;
	res.a = pt(-ha, -ha*ma);
	res.b = pt(ha*ma, ha);
	assert(real(res.b) <= DIM);
	for (ll i = 0; i < n; i++) {
		res.data.push_back(pt(perm[i] - n + 1, i));
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
