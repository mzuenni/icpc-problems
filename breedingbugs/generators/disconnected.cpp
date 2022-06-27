#include "validate.h"
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

constexpr Integer lim = 50000;

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

// unions[i] >= 0 => unions[i] =  parent
// unions[i]  < 0 => unions[i] = -height
vector<Integer> unions, sizes;

void init(Integer n) { //Initialisieren
	unions.assign(n, -1);
	sizes.assign(n, 1);
}

Integer findSet(Integer n) { // Pfadkompression
	if (unions[n] < 0) return n;
	return unions[n] = findSet(unions[n]);
}

void linkSets(Integer a, Integer b) { // Union by rank.
	sizes[a] = sizes[b] = sizes[a] + sizes[b];
	if (unions[a] > unions[b]) unions[a] = b;
	else if (unions[b] > unions[a]) unions[b] = a;
	else {
		unions[a] = b;
		unions[b]--;
}}

void unionSets(Integer a, Integer b) { // Diese Funktion aufrufen.
	if (findSet(a) != findSet(b)) linkSets(findSet(a), findSet(b));
}

constexpr Integer MAX_TRIES = 50;


int main(int argc, char **argv) {
	using namespace Generator;
	Generator::init(argc, argv);

	primeSieve();

	Integer n = arguments["--n"].asInteger();
	Integer lim = arguments["--lim"].asInteger();

	std::vector<Integer> out(n, -1);
	for (Integer tries = 0; tries < MAX_TRIES; tries++) {
		init(n);
		std::vector<Integer> tmp(n);
		for (Integer i = 0; i < n; i++) {
			do {
				if (out[i] < 0)	tmp[i] = Random::integer(1, 10000000);
				else tmp[i] = out[i];

				set<Integer> neighbours;
				for (Integer j = 0; j < i; j++) {
					if (isPrime(tmp[i] + tmp[j])) {
						neighbours.insert(findSet(j));
					}
				}
				Integer nSize = 1;
				for (Integer x : neighbours) nSize += sizes[x];

				if (nSize <= lim) {
					for (Integer x : neighbours) {
						unionSets(x, i);
					}
					break;
				}
			} while (true);
		}
		if (tries + 1 >= MAX_TRIES) {
			out = tmp;
		} else {
			out.assign(n, -1);
			Integer next = 0;
			for (Integer i = 0; i < n; i++) {
				if (sizes[findSet(i)] <= lim && sizes[findSet(i)] > 2) {
					out[next] = tmp[i];
					next++;
				}
			}
		}

		/*map<Integer, Integer> count;
		for (Integer i = 0; i < n; i++) {
			count[sizes[findSet(i)]]++;
		}
		for (auto [a, b] : count) {
			juryErr << a << "\t " << b/a << std::endl;
		}*/
	}

	testOut << n << endl;
	testOut << join(all(out)) << endl;
}
