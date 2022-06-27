#include "icpc_gen_helper.h"
#include <bits/stdc++.h>

using namespace icpc_gen_helper;
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ll>;

constexpr ll DIM_RAND = 1000000000;

bool ptComp(pt a, pt b) {
	return (imag(a) == imag(b)) ? real(a) < real(b) 
								: imag(a) < imag(b);
}

ll cross(pt a, pt b) {return imag(conj(a) * b);}

bool pointOnLineSegment(pt a, pt b, pt p) {
	if (cross(b - a, p - a) != 0) return false;
	ll dist = norm(a - b);
	return norm(a - p) <= dist && norm(b - p) <= dist;
}

pt randomPoint() {
	return pt(uniform_number(-DIM_RAND, DIM_RAND), 
			  uniform_number(-DIM_RAND, DIM_RAND));
}
int main(int argc, char** argv) {
	Init(argc, argv);

	ll n = std::stoull(getParam("--n"));
	
	pt s, e;
	s = randomPoint();
	do {
		e = randomPoint();
	} while(s == e);

	set<pt, bool(*)(pt, pt)> tmp(ptComp);
	while (tmp.size() < n) {
		pt p = randomPoint();
		if (!pointOnLineSegment(s, e, p)) tmp.insert(p);
	}

	vector<pt> points(tmp.begin(), tmp.end());
	shuffle(points.begin(), points.end(), rng);

	//print data
	cout << real(s) << " " << imag(s) << " " << real(e) << " " << imag(e) << endl;
	cout << points.size() << endl;
	for (auto p : points) {
		cout << real(p) << " " << imag(p) << endl;
	}
}
