#include "validate.h"
#include <cassert>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

using namespace Generator;

int main(int argc, char **argv) {
	init(argc, argv);

	const Integer n = arguments["--n"].asInteger(Random::integer(2, 100000));
	const Integer q = arguments["--q"].asInteger(Random::integer(1, 100000));
	const Integer hn = arguments["--hn"].asInteger(Random::integer(1,10));
	const Integer hp = arguments["--hp"].asInteger(Random::integer(1,100));

	vector<Integer> pos(n);
	iota(all(pos), 1);
	
	testOut << n << endl;
	testOut << join(all(pos)) << endl;

	std::vector<Integer> pos_to_id(2.1e6, -1);
	for (Integer i = 0; i < n; i++)
		pos_to_id[pos[i]] = i;

	set<Integer> holes;
	holes.emplace(pos.back() + 1);
	holes.emplace(0);

	testOut << q << endl;
	for (Integer i = 0; i < q ; i++) {
		const bool new_hole = (holes.size() < hn) and Random::integer(0,100) < hp;
		auto h_i = holes.begin();
		if (new_hole)
			advance( h_i, Random::integer(0, holes.size()-1) );
		const auto lo = *h_i;
		if (not new_hole)
			holes.erase(lo);
		auto hi_i = holes.upper_bound(lo);
		const auto hi = *hi_i;
		//if (hi - lo <= 3) { i--; continue; }
		const auto p = new_hole ? (lo + 1 + (hi - lo) / 3) : lo+1;
		assert(pos_to_id[p] >= 0);
		testOut << pos_to_id[p]+1 << '\n';
		assert( pos[pos_to_id[p]] == p );
		assert( pos_to_id[hi] == -1 );
		pos[ pos_to_id[hi] = pos_to_id[p] ] = hi;
		pos_to_id[p] = -1;
		assert( holes.emplace(p).second );
		if (std::next(hi_i) == holes.end())
			assert( holes.emplace(hi+1).second );
		holes.erase(hi_i);
	}
}
