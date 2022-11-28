#include "validate.h"
using namespace std;

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(7);
	Integer m = arguments["--m"].asInteger(n);
	Integer limn = arguments["--limn"].asInteger(200'000);

	std::vector<std::pair<Integer, Integer>> out;
	while (out.size() + n < limn) {
		Integer offset = 1 + (out.size() / n) * (m + 1);
		set<std::vector<Integer>> seen;
		while (seen.size() < n) {
			auto tmp = Random::increasing(2, 0, m+1);
			if (seen.find(tmp) == seen.end()) {
				seen.insert(tmp);
				out.push_back({tmp[0]+offset, tmp[1] - tmp[0]});
			}
		}
	}

	testOut << out.size() << endl;
	testOut << join(out, '\n') << endl;
}
