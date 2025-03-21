#include "validation.h"

int main(int argc, char* argv[]) {
	std::ifstream in(argv[1]);
	AnswerValidator v(argc, argv);

	int n;
	in >> n;
	for(int i = 0; i < n; ++i) {
		int answer = v.read_integer("answer", 0, 1281347096);
		v.newline();
	}
}
