#include "validate.h"
using namespace std;

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer A = arguments["--A"].asInteger(1);
	Integer B = arguments["--B"].asInteger(199999);
	Integer lengthA = arguments["--lengthA"].asInteger(10000000);
	Integer lengthB = arguments["--lengthB"].asInteger(1000000);
	judgeAssert(A + B <= 200000, "invalid parameters");

	testOut << A+B << endl;
	for (Integer i = 1; i <= A; i++) {
		testOut << i << " " << lengthA << endl;
	}
	for (Integer i = 1; i <= B; i++) {
		testOut << i+A << " " << lengthB << endl;
	}
}
