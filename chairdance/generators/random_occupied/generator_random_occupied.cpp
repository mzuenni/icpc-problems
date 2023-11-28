#include "validate.h"

const std::string ops = "+*?";

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer n = arguments["--n"].asInteger(Random::prime(1, 707)*Random::prime(1, 707));
	Integer q = arguments["--q"].asInteger(500'001);

	testOut << n << " " << q << std::endl;
	Integer a = 1;
	Integer b = 0;
	for (Integer i = 0; i < q; i++) {
		char op = Random::select(ops);
		Integer x;
		if (op == '?') {
			//y + b = x		mod n;
			//gcd(y, n) == 0		mod gcd(a, n)
			Integer tmp = std::gcd(a, n);
			Integer y = tmp * Random::integer(0, n / tmp);
			x = (y + b) % n;
			if (x == 0) x += n;
		} else {
			x = Random::integer(1ll,n+1);
			if (op == '+') b = (b + x) % n;
			if (op == '*') {
				b = (b * x) % n;
				a = (a * x) % n;
			}
		}
		testOut << op << " " << x << std::endl;
	}
}
