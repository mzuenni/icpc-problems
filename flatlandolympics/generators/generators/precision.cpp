#include "icpc_gen_helper.h"
#include <bits/stdc++.h>

using namespace icpc_gen_helper;
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ll>;

constexpr ll DIM = 1000000000;
constexpr ll n = 223;

static_assert(2*n*n <= 100000);

int main(int argc, char** argv) {
	Init(argc, argv);

	vector<pt> points;
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			points.push_back({-DIM + i, -DIM + j});
			points.push_back({ DIM - i,  DIM - j});
		}
	}
	shuffle(points.begin(), points.end(), rng);

	//print data
	cout << "0 0 1 1" << endl;
	cout << points.size() << endl;
	for (auto p : points) {
		cout << real(p) << " " << imag(p) << endl;
	}
}
