#include "validate.h"

std::vector<Integer> genHalf(Integer length, Integer height) {
	std::vector<Integer> res(length);
	for (Integer i = 0; i < length; i++) {
		res[i] = Random::integer(std::min(i + 2, length), length + 1);
		Integer free = length - res[i];
		Integer dist = length - i;
		if (dist % 2 != free % 2) res[i] ^= 1;
		if (res[i] > length) res[i] -= 2;
		res[i] = height - res[i];
	}
	return res;
}

std::vector<Integer> gen(Integer length, Integer height) {
	auto l = genHalf(length / 2, height);
	auto r = genHalf(length / 2, height);
	reverse(r.begin(), r.end());
	append(l, r);
	return l;
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	auto n2 = arguments["--n2"].asInteger(Random::integer(1, 100'000));
	auto parts = arguments["--parts"].asInteger(Random::integer(1, n2));
	auto noice = arguments["--noice"].asInteger(Random::integer(0, 1000));

	auto tmp = Random::partition(n2, parts);
	std::vector<std::vector<Integer>> p(tmp.size());
	Integer h = 0;
	for (Integer x : tmp) h = std::max(h, x);
	for (Integer i = 0; i < tmp.size(); i++) {
		p[i] = gen(2*tmp[i], h);
	}
	tmp = flatten(p);
	for (Integer i = 0; i < noice; i++) {
		Random::select(tmp) ^= 1;
	}

	testOut << 2*n2 << " " << h << std::endl;
	testOut << join(tmp) << std::endl;
}
