#include "validate.h"
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

using namespace Generator;

int main(int argc, char **argv) {
	init(argc, argv);

	Integer n = arguments["--n"].asInteger(Random::integer(0, 100000));
	Integer q = arguments["--q"].asInteger(Random::integer(0, 100000));
	Integer p = arguments["--p"].asInteger(Random::integer(n + 1, 1000000));

	set<Integer> free;
	for (Integer i = 0; i < 2000007; i++) free.insert(i);
	map<Integer, Integer> posToId;
	vector<Integer> idToPos(n);
	for (Integer i = 0; i < n; i++) {
		idToPos[i] = p - n + i;
		posToId[idToPos[i]] = i;
		free.erase(idToPos[i]);
	}

	testOut << n << endl;
	testOut << join(all(idToPos)) << endl;
	testOut << q << endl;
	for (Integer i = 0; i < q ; i++) {
		Integer id;
		if (Random::integer(0, 75) == 0) {
			id = Random::integer(0, n);
		} else {
			id = posToId.begin()->second;
		}
		auto it = free.insert(idToPos[id]).first;
		it++;
		idToPos[id] = *it;
		posToId[idToPos[id]] = id;
		free.erase(it);
		testOut << id+1 << endl;
	}
}
