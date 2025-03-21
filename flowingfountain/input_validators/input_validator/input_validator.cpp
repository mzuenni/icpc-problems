#include "validation.h"

int main(int argc, char* argv[]) {
	InputValidator v(argc, argv);
	int n = v.read_integer("n", 1, 300'000);
	v.space();
	int q = v.read_integer("q", 1, 300'000);
	v.newline();
	auto cs = v.read_integers("c", n, 1, 1'000'000'000, UniqueTag{});

	bool hasQuery = false;
	for(int i = 0; i < q; ++i) {
		char t = v.read_string("t", 1, 1, "+?")[0];
		v.space();
		if(t == '+') {
			int l = v.read_integer("l", 1, n);
			v.space();
			int x = v.read_integer("x", 1, 1'000'000'000);
		} else {
			hasQuery = true;
			int l = v.read_integer("l", 1, n);
		}
		v.newline();
	}
	v.check(hasQuery, "No query found");
}
