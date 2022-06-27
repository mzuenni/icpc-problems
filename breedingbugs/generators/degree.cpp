#include "validate.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

constexpr Integer N = 20000007;
bitset<N / 2> isNotPrime;

bool isPrime(Integer x) {
	if (x < 2 || x % 2 == 0) return x == 2;
	else return !isNotPrime[x / 2];
}

void primeSieve() {
	// i * i < N is enough for isPrime
	for (Integer i = 3; i < N; i += 2) {
		if (!isNotPrime[i / 2]) {
			for (Integer j = i * i; j < N; j+= 2 * i) {
				isNotPrime[j / 2] = 1;
			}
		}
	}
}

int main(int argc, char **argv) {
	using namespace Generator;
	Generator::init(argc, argv);
	
	primeSieve();

	Integer n = arguments["--n"].asInteger();
	Integer deg = arguments["--deg"].asInteger();
	
	vector<Integer> out(n);
	for (Integer i = 0; i < n; i++) out[i] = Random::integer(1, 10000000);

	for (Integer i = 0; i < 20; i++) {
		for (Integer& x : out) {
			while (true) {
				Integer d = 0;
				for (Integer y : out) if (isPrime(x+y)) d++;
				if (abs(d - deg) > 5) x = Random::integer(1, 10000000);
				else break;
			}
		}
	}

	Random::shuffle(all(out));

	testOut << n << endl;
	testOut << join(all(out)) << endl;
}
