#include "icpc_gen_helper.h"
#include <bits/stdc++.h>

using namespace icpc_gen_helper;
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ll>;

constexpr ll DIM_RAND = 1000;

int main(int argc, char** argv) {
	Init(argc, argv);

	ll w = std::stoull(getParam("--w"));
	ll h = std::stoull(getParam("--h"));
	
	pt s(-3*w, 0);
	pt e(6*w+2, 0);

	pt rot(uniform_number(-DIM_RAND, DIM_RAND), 
		   uniform_number(-DIM_RAND, DIM_RAND));
	pt add(uniform_number(-DIM_RAND, DIM_RAND), 
		   uniform_number(-DIM_RAND, DIM_RAND));
	auto transform = [&](pt& p){
		p *= rot;
		p += add;
	};

	vector<pt> points;
	for (ll y = 1; y <= h; y++) {
		for (ll x = 1; x <= w; x++) {
			ll dx = uniform_number(-1, 1);
			ll dy = uniform_number(-1, 1);
			points.push_back(pt(3*x+dx, 3*y+dy));
		}
	}

	//randomize data
	transform(s);
	transform(e);
	for (auto& p : points) transform(p);
	shuffle(points.begin(), points.end(), rng);

	//print data
	cout << real(s) << " " << imag(s) << " " << real(e) << " " << imag(e) << endl;
	cout << points.size() << endl;
	for (auto p : points) {
		cout << real(p) << " " << imag(p) << endl;
	}
}
