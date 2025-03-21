#include "validation.h"

// Check the grammar of the input files.
// You should also check properties of the input.
// E.g., check that a graph is connected.

int main(int argc, char* argv[]) {
	InputValidator v(argc, argv);
	int t = v.read_integer("t", 1, 100'000);
	v.newline();
	v.read_integers("n", t, 1, 1'000'000'000'000'000'000, Arbitrary, Newline);
}
