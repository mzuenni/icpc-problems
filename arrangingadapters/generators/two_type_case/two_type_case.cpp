#include "validate.h"
#include <cassert>

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::integer(4, 200'000));
    Integer np = Random::integer(1, n/2.7), nm = n - 2*np;
    Integer s = arguments["--s"].asInteger(Random::integer(1, 1'000'000'000/5 - np));

    std::vector<Integer> u = Random::partition(s, 2*np, 1);
    assert(u.size() == 2*np);
    std::vector<Integer> v = Random::distinct(np, 2*np);
    assert(v.size() == np);
    std::vector<bool> w(2*np, false);
    Integer sum = 0, max_u = 3;
    for (Integer x : v) w[x] = true;
    for (Integer i = 0; i < u.size(); i++) u[i] = u[i]*3 + (w[i] ? 2 : 1), max_u = std::max(max_u, u[i]), sum += u[i];
	
    std::vector<Integer> t = Random::multiple(nm, max_u + 1, 1'000'000'000);
    u.insert(u.end(), t.begin(), t.end());

    assert(sum == (s+np)*3);
    
    Random::shuffle(u);
    testOut << u.size() << " " << s+np+2 << std::endl;
    testOut << join(u) << std::endl;
}
