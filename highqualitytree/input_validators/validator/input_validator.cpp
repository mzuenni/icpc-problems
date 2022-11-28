#include "validate.h"
using namespace std;

// unions[i] >= 0 => unions[i] =  parent
// unions[i]  < 0 => unions[i] = -height
vector<Integer> unions;

void init(Integer n) { //Initialisieren
	unions.assign(n, -1);
}

Integer findSet(Integer n) { // Pfadkompression
	if (unions[n] < 0) return n;
	return unions[n] = findSet(unions[n]);
}

void linkSets(Integer a, Integer b) { // Union by rank.
	if (unions[a] > unions[b]) unions[a] = b;
	else if (unions[b] > unions[a]) unions[b] = a;
	else {
		unions[a] = b;
		unions[b]--;
}}

void unionSets(Integer a, Integer b) { // Diese Funktion aufrufen.
	if (findSet(a) != findSet(b)) linkSets(findSet(a), findSet(b));
}

int main(int argc, char **argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;
	//juryErr	error output stream
	//juryOut	default output stream
	//testIn	testcase input
	Integer n = testIn.integer(1, 200001, constraint["n"]);
	testIn.newline();
	vector<Integer> deg(n + 1);
	deg[0] = 3;
	deg[1] = 1;

	init(n + 1);
	for (Integer i = 1; i < n; i++) {
		Integer a = testIn.integer(1, n + 1, constraint["a"]);
		testIn.space();
		Integer b = testIn.integer(1, n + 1, constraint["b"]);
		testIn.newline();
		if (findSet(a) == findSet(b)) juryOut << "Not a tree!" << WA;
		unionSets(a, b);
		deg[a]++;
		deg[b]++;
	}
	testIn.eof();
	for (Integer x : deg) {
		if (x > 3) juryOut << "Not a binarytree!" << WA;
	}
	return AC;
}
