#include <cassert>
#include <deque>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

vector<int> parent, sz;
vector<vector<int>> children;

int n, depth;
float p0, p1, p2, pjoin;

// true with probability p
bool prob(float p) {
	return rand() % 1000000 < p * 1000000;
}

int branches = 0;

// generate a child of p
pair<int, int> gen(int p, int d) {
	// done.
	if(parent.size() == n) {
		--branches;
		return {0, -1};
	}
	// If depth is large, skip
	if(d > depth && prob(1. / depth)) {
		// kill for depth
		--branches;
		return {0, -1};
	}
	int u = parent.size();
	parent.push_back(p);
	sz.push_back(1);
	children.push_back({});

	float x = (rand() % 1000000) / 1000000.;
	if(branches > 1 && x < p0) {
		// 0 children; die here
		--branches;
		return {1, u};
	} else if(x < p0 + p1) {
		// 1 child
		auto [s, v] = gen(u, d + 1);
		sz[u] += s;
		if(v != -1) children[u].push_back(v);
	} else {
		++branches;
		// 2 children
		for(int i = 0; i < 2; ++i) {
			auto [s, v] = gen(u, d + 1);
			sz[u] += s;
			if(v != -1) children[u].push_back(v);
		}
	}
	return {sz[u], u};
}

vector<pair<int, int>> intervals;

void build(int u, deque<int> d) {
	assert(d.size() == 2 * sz[u]);
	intervals.push_back({d.front(), d.back()});
	d.pop_front();
	d.pop_back();
	if(children[u].size() == 1) {
		build(children[u][0], std::move(d));
	}
	if(children[u].size() == 2) {
		// split d into two parts.
		int c1 = children[u][0];
		int c2 = children[u][1];
		int s1 = 2 * sz[c1];
		int s2 = 2 * sz[c2];
		assert(d.size() == s1 + s2);
		// Determine overlap.
		int prefix = rand() % (s1 + 1);
		int suffix = rand() % (s2 + 1);
		// With 50% chance, we make them completely disjoint
		if(rand() % 2) {
			prefix = s1;
			suffix = s2;
		}
		deque<int> d1, d2;
		for(int i = 0; i < prefix; ++i) {
			d1.push_back(d.front());
			d.pop_front();
			--s1;
		}
		for(int i = 0; i < suffix; ++i) {
			d2.push_front(d.back());
			d.pop_back();
			--s2;
		}
		assert(2 * sz[c1] == prefix + s1);
		assert(2 * sz[c2] == suffix + s2);
		assert(d1.size() == prefix);
		assert(d2.size() == suffix);
		assert(d.size() == s1 + s2);
		{
			vector<int> left(s1 + s2, false);
			for(int cnt = 0; cnt < s1;) {
				int x = rand() % left.size();
				if(left[x]) continue;
				left[x] = true;
				++cnt;
			}
			for(int i = 0; i < s1 + s2; ++i) {
				if(left[i]) d1.push_back(d[i]);
			}
			for(int i = s1 + s2 - 1; i >= 0; --i) {
				if(!left[i]) d2.push_front(d[i]);
			}
		}
		assert(d1.size() == 2 * sz[c1]);
		assert(d2.size() == 2 * sz[c2]);
		d.clear();
		d.shrink_to_fit();
		build(c1, std::move(d1));
		build(c2, std::move(d2));
	}
}

int main(int argc, char** argv) {
	int seed = stoi(argv[1]);
	srand(seed);
	n      = stoi(argv[2]);
	p0     = stof(argv[3]);
	p1     = stof(argv[4]);
	p2     = stof(argv[5]);
	auto s = p0 + p1 + p2;
	p0 /= s;
	p1 /= s;
	p2 /= s;
	pjoin = stof(argv[6]);
	depth = 10000;
	if(argc > 7) {
		depth = stoi(argv[7]);
	}
	cerr << "n " << n << " p0/1/2 " << p0 << " " << p1 << " " << p2 << " pjoin " << pjoin
	     << " depth " << depth << endl;
	int sz = gen(-1, 0).first;
	cerr << "SIZE: " << sz << endl;
	deque<int> d(2 * sz);

	int pos = 1;
	for(int i = 0; i < 2 * sz; ++i) {
		// with probability pjoin, two consecutive positions are the same.
		if(!prob(pjoin)) {
			pos += rand() % 10 + 1;
		}
		d[i] = pos;
	}
	build(0, std::move(d));

	// Print all unique intervals.
	set<pair<int, int>> unique;
	for(auto [x, y] : intervals) {
		unique.insert({x, max(y, x + 1)});
	}
	cerr << "intervals: " << intervals.size() << endl;
	cerr << "unique:    " << unique.size() << endl;
	cout << unique.size() << endl;
	for(auto [x, y] : unique) {
		cout << x << ' ' << y - x << '\n';
	}
}
