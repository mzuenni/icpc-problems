#include "validate.h"
using namespace OutputValidator;

Integer n, m;
std::vector<std::pair<Integer, Integer>> edges;
std::vector<std::map<Integer, Integer>> adj;

void check(InputStream& in, Integer expected, Verdict verdict) {
	in.expectInt(expected);
	in.newline();

	std::vector<bool> used(m);
	for (Integer i = 0; i < expected; i++) {
		Integer k = in.integer(1, m+2);
		in.newline();
		auto vs = in.integers(1, n+1, k);
		in.newline();

		for (Integer j = 0; j + 1 < k; j++) {
			Integer a = vs[j] - 1;
			Integer b = vs[j + 1] - 1;
			if (adj[a].find(b) == adj[a].end()) juryOut << "edge not found: " << a+1 << "-" << b+1 << verdict;
			Integer edge = adj[a][b];
			if (used[edge]) juryOut << "edge used twice: " << a+1 << "-" << b+1 << verdict;
			used[edge] = true;
		}
	}
	for (Integer i = 0; i < m; i++) {
		auto [a, b] = edges[i];
		if (!used[i]) juryOut << "edge not used: " << a+1 << "-" << b+1 << verdict;
	}
}

int main(int argc, char *argv[]) {
	OutputValidator::init(argc, argv);

	n = testIn.integer();
	m = testIn.integer();
	for (Integer i = 0; i < 2*n; i++) testIn.integer();//skip coordinates

	edges.assign(m, {});
	adj.assign(n, {});
	for (Integer i = 0; i < m; i++) {
		Integer a = testIn.integer();
		Integer b = testIn.integer();
		a--;
		b--;
		edges[i] = {a, b};
		adj[a][b] = adj[b][a] = i;//no selfloops and multiedges so this is fine
	}

	Integer expected = 0;
	{
		std::vector<bool> seen(n);
		auto odd = [&](auto&& self, Integer i) -> Integer {
			if (seen[i]) return 0;
			seen[i] = true;
			Integer res = adj[i].size() & 1;
			for (auto [to, id] : adj[i]) res += self(self, to);
			return res;
		};

		for (Integer i = 0; i < n; i++) {
			if (!seen[i]) {
				expected += std::max<Integer>(1, odd(odd, i) / 2);
			}
		}
	}

	//check(juryAns, expected, FAIL);//optional
	check(teamAns, expected, WA);
	return AC;
}
