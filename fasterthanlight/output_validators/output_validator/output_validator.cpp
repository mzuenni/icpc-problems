#include "validation.h"

int main(int argc, char** argv) {
	OutputValidator v(argc, argv);
	auto answer = v.read_string("answer", 8, 10);
	v.check(answer == "impossible" || answer == "possible", "Answer must be [im]possible.");
	v.newline();
}
