#include "validate.h"
using namespace std;

void printTestcase(vector<pair<Integer, Integer>> in, Integer limN) {
	using namespace Generator;
	Random::shuffle(in);
	while (in.size() > limN) in.pop_back();
	Integer m = 0;
	for (auto [a, b] : in) m += b;

	testOut << in.size() << " " << m << endl;
	testOut << join(in, '\n') << endl;
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(200'000);
	Integer m = arguments["--m"].asInteger(1'000'000);

	Integer l = 0;
	Integer r = m+1;
	while (l + 1 < r) {
		Integer mm = (l + r) / 2;
		Integer cur = 0;
		for (Integer i = 0; i < n; i+=3) {
			for (Integer j = 0; j < 3 && j+i < n; j++) {
				cur += mm - (i / 3);
			}
		}

		if (cur <= m) {
			l = mm;
		} else {
			r = mm;
		}

	}

	vector<pair<Integer, Integer>> out;
	for (Integer i = 0; i < n; i += 3, l--) {
		out.push_back({l-1, l});
		out.push_back({l, l});
		out.push_back({l+1, l});
	}
	printTestcase(out, n);
}
