/*
Following Maarten's suggestion, we generate a test case with three types of adapters.
There are two modes:
- 0 : exactly n/3 adapters of each type
- 1 : the same, but with +/- 1 adapters of each type
*/

#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::integer(1, 200'000/3));
	Integer s = arguments["--s"].asInteger(Random::integer(1, 1'000'000'000));
    Integer m = arguments["--m"].asInteger(Random::integer(0, 2));
	
    Integer s1 = Random::integer(3, s/3);
    Integer s2 = Random::integer(3, s/3);
    Integer s3 = Random::integer(3, s/3);
    Integer sz1 = n, sz2 = n, sz3 = n;
    
    Integer dice_toss = Random::integer(0, 2);
    if (dice_toss == 0) sz1++;
    else if (dice_toss == 1) sz1--;
    dice_toss = Random::integer(0, 2);
    if (dice_toss == 0) sz2++;
    else if (dice_toss == 1) sz2--;
    dice_toss = Random::integer(0, 2);
    if (dice_toss == 0) sz2++;
    else if (dice_toss == 1) sz2--;

    std::vector<Integer> v(sz1 + sz2 + sz3);

    for (Integer i = 0; i < sz1; i++) v[i] = s1;
    for (Integer i = sz1; i < sz1 + sz2; i++) v[i] = s2;
    for (Integer i = sz1 + sz2; i < sz1 + sz2 + sz3; i++) v[i] = s3;

    Random::shuffle(v);
    testOut << v.size() << " " << s << std::endl;
    testOut << join(v) << std::endl;
}
