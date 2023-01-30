#include "validate.h"
using namespace std;

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(200'000);
	Integer m = arguments["--m"].asInteger(1'000'000);
	Integer c = arguments["--c"].asInteger(1'000'000);

	Integer tmp = m / n;
	testOut << n << " " << tmp * n << endl;
	for (Integer i = 0; i < n; i++) {
		testOut << c << " " << tmp << endl;
	}
}
