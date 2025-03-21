#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

// unions[i] >= 0 => unions[i] =  parent
// unions[i]  < 0 => unions[i] = -height
vector<int> unions;

void init(int n) { //Initialisieren
	unions.assign(n, -1);
}

int findSet(int n) { // Pfadkompression
	if (unions[n] < 0) return n;
	return unions[n] = findSet(unions[n]);
}

void linkSets(int a, int b) { // Union by rank.
	//if (unions[b] > unions[a]) swap(a, b);
	if (unions[b] == unions[a]) unions[b]--;
	unions[a] = b;
}

void unionSets(int a, int b) { // Diese Funktion aufrufen.
	if (findSet(a) != findSet(b)) linkSets(findSet(a), findSet(b));
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, q;
	cin >> n >> q;
	vector<ll> lim(n), state(n), next(n, -1), cur(n), tmp;
	for (ll& x : lim) cin >> x;
	for (ll i = n - 1; i >= 0; i--) {
		while (!tmp.empty() && lim[tmp.back()] <= lim[i]) tmp.pop_back();
		if (!tmp.empty()) next[i] = tmp.back();
		tmp.push_back(i);
	}
	iota(all(cur), 0);
	init(n);
	for (ll i = 0; i < q; i++) {
		char t;
		ll p;
		cin >> t >> p;
		p--;
		if (t == '+') {
			ll x;
			cin >> x;
			while (x > 0 && p >= 0) {
				p = cur[findSet(p)];
				ll c = min(x, lim[p] - state[p]);
				state[p] += c;
				x -= c;
				if (lim[p] == state[p]) {
					if (next[p] >= 0) {
						ll pp = cur[findSet(next[p])];
						unionSets(p, pp);
						cur[findSet(pp)] = pp;
					} else {
						p = -1;
					}
				}
			}
		} else {
			cout << state[p] << endl;
		}
	}
}

