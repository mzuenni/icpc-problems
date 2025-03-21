#include "validate.h"

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	const Integer n = arguments["--n"].asInteger(Random::integer(1, 300'001));
	const Integer q = arguments["--q"].asInteger(Random::integer(1, 300'001));
    const Integer bucketSize = arguments["--bucketsize"].asInteger(n);
    const Integer numberOfBuckets = (n + bucketSize - 1) / bucketSize;
	const Integer lim = arguments["--lim"].asInteger(1'000'000'000);
    const Integer maxIndex = arguments["--maxindex"].asInteger(n);
    
    const std::string internalOrder = arguments["--internalorder"].asString("any");
    const std::string order = arguments["--order"].asString("increasing");

	testOut << n << " " << q << std::endl;
    std::vector<Integer> levels;
    levels.reserve(n);
    for (Integer bucket = 0; bucket < numberOfBuckets; bucket++) {
        const Integer index{ order == "increasing" ? bucket : numberOfBuckets - bucket - 1 };
        Integer lower{ index * (lim / numberOfBuckets) + 1 };
        Integer upper{ lower + (lim / numberOfBuckets) };
        if (lower > upper) {
            std::swap(lower, upper);
        }
        const auto contents{ internalOrder == "any" ? Random::distinct(bucketSize, lower, upper) :
                             internalOrder == "increasing" ? Random::increasing(bucketSize, lower, upper) :
                             Random::decreasing(bucketSize, lower, upper) };
        for (const auto x : contents) {
            levels.push_back(x);
            if (levels.size() == n) {
                break;
            }
        }
    }
	testOut << levels << std::endl;
	for (Integer i = 0; i < q; i++) {
		if (Random::bit()) testOut << "+ " << Random::integer(1, maxIndex + 1) << " " << Random::integer(1, lim) << std::endl;
		else testOut << "? " << Random::integer(1, n+1) << std::endl;
	}
}
