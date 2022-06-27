#include "icpc_gen_helper.h"
#include <bits/stdc++.h>

using namespace icpc_gen_helper;
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ll>;

constexpr ll DIM_RAND = 1000000000;

constexpr ll dx = 2*DIM_RAND;
constexpr ll dy = dx - 1;

bool ptComp(pt a, pt b) {
	return (imag(a) == imag(b)) ? real(a) < real(b) 
								: imag(a) < imag(b);
}

int main(int argc, char** argv) {
	Init(argc, argv);

	ll n = std::stoull(getParam("--n"));

	set<pt, bool(*)(pt, pt)> tmp(ptComp);
	tmp.insert(pt(DIM_RAND - 1, DIM_RAND - 2));
	while (tmp.size() < n) {
		// x/y == dx/dy;
		ll x = uniform_number(1ll, 2*DIM_RAND-2);
		ll y = (x*dx+dy-1) / dy;
		tmp.insert(pt(x-DIM_RAND, y-DIM_RAND));
	}

	vector<pt> points(tmp.begin(), tmp.end());
	shuffle(points.begin(), points.end(), rng);

	//print data
	cout << -DIM_RAND << " " << -DIM_RAND << " " << -DIM_RAND+dx << " " << -DIM_RAND+dy << endl;
	cout << points.size() << endl;
	for (auto p : points) {
		cout << real(p) << " " << imag(p) << endl;
	}
}
