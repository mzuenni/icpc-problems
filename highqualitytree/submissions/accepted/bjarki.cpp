#include <bits/stdc++.h>
using namespace std;

vector<int> adj[200100];

struct hcount {
	map<int,int> count;
	int diff;
	int height() {
		return count.empty() ? 0 : diff + count.rbegin()->first;
	}
	void slack(int s) {
		diff += s;
	}
	int poplargest() {
		auto it = count.rbegin();
		int res = it->second;
		count.erase(it->first);
		return res;
	}
	int size() {
		return count.size();
	}
	void mergefrom(hcount *other) {
		for (auto it : other->count) {
			count[it.first + other->diff - diff] += it.second;
		}
	}
	void add(int k, int v) {
		count[k - diff] += v;
	}
};

int answer = 0;
hcount* greedy(int at, int parent) {
	hcount *first = new hcount(), *second = new hcount();
	int degree = 0;
	for (auto child : adj[at])  {
		if (child == parent) continue;
		hcount* res = greedy(child, at);
		if (degree == 0) {
			delete first;
			first = res;
		} else {
			delete second;
			second = res;
		}
		degree++;
	}
	first->slack(1);
	second->slack(1);
	int h1 = first->height();
	int h2 = second->height();
	if (h1 > h2) {
		swap(h1,h2);
		swap(first,second);
	}
	while (abs(h1-h2) > 1) {
		answer += second->poplargest();
		h2 = second->height();
	}
	if (first->size() < second->size()) {
		swap(first,second);
	}
	first->mergefrom(second);
	first->add(0, 1);
	delete second;
	return first;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	delete greedy(0, -1);

	cout << answer << endl;

	return 0;
}
