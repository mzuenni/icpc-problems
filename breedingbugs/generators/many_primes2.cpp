#include "validate.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

constexpr Integer N = 19999998;
bitset<N / 2> isNotPrime;
vector<Integer> primes = {2};

bool isPrime(Integer x) {
	if (x < 2 || x % 2 == 0) return x == 2;
	else return !isNotPrime[x / 2];
}

void primeSieve() {
	// i * i < N is enough for isPrime
	for (Integer i = 3; i < N; i += 2) {
		if (!isNotPrime[i / 2]) {
			primes.push_back(i);
			for (Integer j = i * i; j < N; j+= 2 * i) {
				isNotPrime[j / 2] = 1;
			}
		}
	}
}

int main(int argc, char **argv) {
	using namespace Generator;
	Generator::init(argc, argv);

	Integer n = arguments["--n"].asInteger();

	primeSieve();
	reverse(all(primes));

	vector<Integer> out(n, 10000000 - 2);
	for (Integer i = 0; 2*i < n; i++) out[i] = primes[i] - (10000000 - 2);

	Random::shuffle(all(out));

	testOut << n << endl;
	testOut << join(all(out)) << endl;
}
