#include "validate.h"
#include "graph_gen.h"

Integer n = -1;
Integer q = -1;
Integer lim = -1;

//transforms any tree into a set of capacities that implicitly represent that key
std::vector<Integer> capacities(const Graph<NoData>& tree, Integer root = 0) {
	std::vector<Integer> degree(n), todo;
	for (Integer i = 0; i < n; i++) {
		degree[i] = tree.degree(i) - (i != root);
		if (degree[i] == 0) todo.push_back(i);
	}
	std::vector<Integer> minCap(n);
	Integer next = 0;
	while (!todo.empty()) {
		std::swap(todo.back(), Random::select(todo));
		Integer i = todo.back();
		todo.pop_back();
		minCap[i] = next;
		next++;
		for (auto edge : tree[i]) {
			degree[edge.to]--;
			if (degree[edge.to] == 0) todo.push_back(edge.to);
		}
	}
	assert(next == n);

	std::vector<Integer> res;
	auto dfs = [&](auto&& self, Integer cur, Integer pref) -> void {
		res.push_back(minCap[cur]);
		for (auto edge : tree[cur]) {
			if (edge.to == pref) continue;
			self(self, edge.to, cur);
		}
	};
	dfs(dfs, root, -1);
	std::reverse(allOf(res));

	std::vector<Integer> cap = Random::increasing(n, 1, lim / 10);
	for (Integer& x : res) x = cap[x];
	return res;
}

Graph<NoData> dfs_tree(const Graph<NoData>& g, Integer root = 0) {
	Graph<NoData> tree(n);
	std::vector<bool> seen(n);
	auto dfs = [&](auto&& self, Integer cur, Integer pref) -> void {
		seen[cur] = true;
		for (auto edge : g[cur]) {
			if (seen[edge.to]) continue;
			tree.addEdge(cur, edge.to);
			self(self, edge.to, cur);
		}
	};
	dfs(dfs, root, -1);
	return tree;
}

int main(int argc, char **argv) {
	Generator::init(argc, argv);
	using namespace Generator;

	n = arguments["--n"].asInteger(Random::integer(1, 300'001));
	q = arguments["--q"].asInteger(Random::integer(1, 300'001));
	lim = arguments["--lim"].asInteger(1'000'000'000);
	bool fill = !!arguments["--fill"];
	auto type = arguments["--type"].asString();

	Graph<NoData> tree;
	if (type == "random") {
		tree = randomTree(n);
	} else if (type == "path") {
		tree = path(n - 1);
	} else if (type == "binary") {
		tree = completeTree(log2(n));
		n = tree.nodeCount();
	} else if (type == "almost_path") {
		Integer w = arguments["--w"].asInteger(2);
		tree = grid(w, n / w);
		tree.permutate();
		tree = dfs_tree(tree);
	} else {
		return 1;
	}

	auto cap = capacities(tree);
	std::vector<Integer> leaves = {0};
	for (Integer i = 1; i < n; i++) {
		if (cap[i] <= cap[i - 1]) leaves.push_back(i);
	}

	testOut << n << " " << q << std::endl;
	testOut << cap << std::endl;

	if (fill) {
		auto perm = Random::perm(n);
		Integer qs = 0;
		for (Integer i : perm) {
			testOut << "+ " << i+1 << " " << std::max<Integer>(1, i - Random::integer(0, 10)) << std::endl;
			if (Random::integer(50) == 0) {//noise
				testOut << "? " << 1 + Random::integer(n) << std::endl;
				qs++;
			}
		}
		auto updates = Random::increasing(std::min<Integer>(n, q - n - qs), 0, n);
		for (Integer i : updates) {
			if (Random::integer(50) == 0) {//noise
				testOut << "? " << 1 + Random::integer(n) << std::endl;
			} else {
				testOut << "+ " << i+1 << " " << Random::integer(lim / 2, lim) << std::endl;
			}
		}
		for (Integer i = updates.size(); i < q - n - qs; i++) {
			testOut << "? " << 1 + Random::integer(n) << std::endl;
		}
	} else {
		auto updates = Random::multiple(q / 2, 0, leaves.size());
		auto queries = Random::multiple((q + 1) / 2, std::max<Integer>(0, n - 50), n);

		for (Integer i : updates) {
			i = Random::integer(10) == 0 ? Random::integer(n) : leaves[i];//noise
			testOut << "+ " << i+1 << " " << Random::integer(lim) << std::endl;

			if (!queries.empty() && Random::integer(10) == 0) {//noise
				queries.pop_back();
				testOut << "? " << 1 + Random::integer(n) << std::endl;
			}
		}
		for (Integer i : queries) {
			if (Random::integer(10) == 0) i = Random::integer(0, n);//noise
			testOut << "? " << i+1 << std::endl;
		}
	}
}
