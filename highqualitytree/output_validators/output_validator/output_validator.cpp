#include "validation.h"

int main(int argc, char** argv) {
	std::ifstream in(argv[1]);
	OutputValidator v(argc, argv);

	int n;
	in >> n;
	int answer = v.read_integer("answer", 0, n - 1);
	v.newline();
}
