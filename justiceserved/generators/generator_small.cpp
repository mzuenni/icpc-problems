#include "validate.h"
using namespace std;

std::vector<std::pair<Integer, Integer>> out, todo;
Integer n, m;

void recursive() {
	if (todo.size() == n) {
		Integer offset = 1 + (out.size() / n) * (m + 1);
		for (auto [l, x] : todo) out.push_back({l+offset, x});
	} else {
		for (Integer l = 0; l < m; l++) {
			for (Integer r = l + 1; r <= m; r++) {
				bool ok = true;
				for (auto [a, b] : todo) ok &= l != a || (r-l) != b;
				if (ok) {
					todo.push_back({l, r-l});
					recursive();
					todo.pop_back();
				}
			}
		}
	}
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	n = arguments["--n"].asInteger(4);
	m = arguments["--m"].asInteger(n);

	recursive();
	//Random::shuffle(out);

	testOut << out.size() << endl;
	testOut << join(out, '\n') << endl;
}
