// generates a random graph...
#include "validate.h"
#include "graph_gen.h"

using pt = std::pair<Integer, Integer>;
using line = std::pair<pt, pt>;

void print(std::vector<line>& lines) {
	using namespace Generator;
	Random::shuffle(lines);
	testOut << lines.size() << std::endl;
	testOut << join(lines, NEWLINE) << std::endl;
}

Integer gcd(Integer a, Integer b) { return b == 0 ? a : gcd(b, a % b); }

bool checkPoint(pt p, const std::vector<pt>& ps) {
	std::set<pt> seen;
	for (pt c : ps) {
		Integer dx = c.first - p.first;
		Integer dy = c.second - p.second;
		if (dx == 0 && dy == 0) return false;
		Integer d = gcd(dx, dy);
		dx /= d;
		dy /= d;
		if (seen.find({dx, dy}) != seen.end()) return false;
		seen.insert({dx, dy});
	}
	return true;
}

Graph g;
std::vector<Integer> num;
Integer counter;
bool bridge;

Integer dfs(Integer v, Integer from = -1) {
	Integer me = num[v] = ++counter, top = me;
	for (auto [efrom, eto, _] : g[v]) {
		if (eto == from) {}
		else if (num[eto]) {
			top = std::min(top, num[eto]);
		} else {
			Integer up = dfs(eto, efrom);
			top = std::min(top, up);
			if (up > me) bridge = true;
		}
	}
	return top;
}

Integer sq(Integer x) {
	return x*x;
}

Integer dist(pt a, pt b) {
	return sq(a.first - b.first) + sq(a.second - b.second);
}

bool hasBridge() {
	counter = 0;
	num.assign(g.nodeCount(), 0);
	bridge = false;
	for (Integer v = 0; v < g.nodeCount(); v++) {
		if (!num[v]) dfs(v);
	}
	return bridge;
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	Integer dim = arguments["--dim"].asInteger(1000000-7);
	Integer n = arguments["--n"].asInteger(200);
	Integer m = arguments["--m"].asInteger(1000);
	bool yes = !!arguments["--yes"];

	std::vector<pt> ps;
	while (ps.size() < n) {
		Integer x = Random::integer(-dim, dim + 1);
		Integer y = Random::integer(-dim, dim + 1);
		if (checkPoint({x, y}, ps)) {
			ps.push_back({x, y});
		}
	}

	do {
		auto deg = Random::partition(m - yes, n, 1);
		for (auto& d : deg) d *= 2;
		try {
			g = randomGraph(deg);
		} catch (std::exception) {
			g = clique(0);
		}
	} while(g.nodeCount() == 0 || hasBridge());

	if (yes) {
		Integer a = 0;
		Integer b = 1;
		for (Integer i = 0; i < n; i++) {
			for (Integer j = 0; j < i; j++) {
				if (dist(ps[i], ps[j]) < dist(ps[a], ps[b])) {
					a = i;
					b = j;
				}
			}
		}
		g.addEdge(a, b);
	}

	std::vector<line> lines;
	for (auto [a, b, _] : g.getEdges()) {
		lines.push_back({ps[a], ps[b]});
	}
	print(lines);
}
