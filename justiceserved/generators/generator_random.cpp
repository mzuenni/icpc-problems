#include "validate.h"
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

vector<Integer> generateEnds(Integer x, Integer p) {
	set<Integer> tmp;
	while (sz(tmp) < x) {
		Integer y = Random::integer(1, p);
		tmp.insert(y);
	}
	vector<Integer> res(all(tmp));
	return res;
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(200000);
	Integer p = arguments["--p"].asInteger(1000000001);
	Integer disjointEnds = arguments["--ends"].asInteger(50000);

	auto ends = generateEnds(disjointEnds, p);
	set<pair<Integer, Integer>> seen;
	vector<pair<Integer, Integer>> res;
	for (Integer i = 0; i < n; i++) {
		Integer l = 0;
		Integer r = 0;
		do {
			l = Random::select(ends);
			do {
				r = Random::select(ends);
			} while(l == r);
			if (r < l) swap(l, r);
		} while(seen.count({l, r}) > 0);
		seen.insert({l, r});
		res.push_back({l, r-l});
	}

	sort(all(res), [](const pair<Integer, Integer>& a,
					  const pair<Integer, Integer>& b){
		return a.second > b.second;
	});

	testOut << n << endl;
	for (auto e : res) testOut << e << endl;
}
