#include "validation.h"
using namespace std;

int main(int argc, char* argv[]) {
	// Set up the input and answer streams.
	std::ifstream in(argv[1]);
	AnswerValidator v(argc, argv);

	int n, q;
	in >> n >> q;
	int capacity;
	for(int i = 0; i < n; ++i) {
		in >> capacity;
	}
	for(int i = 0; i < q; ++i) {
		char type;
		in >> type;
		if(type == '+') {
			int x, y;
			in >> x >> y;
		} else {
			int x;
			in >> x;
			int answer = v.read_integer("answer", 0, 1000000000);
			v.newline();
		}
	}
}
