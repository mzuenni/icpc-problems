#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll maxSigma = 11;
constexpr ll maxN= 256;
ll rule[maxSigma][maxSigma][maxSigma];
using bits = bitset<maxSigma*maxSigma>;
array<bits, maxSigma * maxSigma * maxN> adj;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, sigma;
	cin >> n >> sigma;

	for (ll a = 0; a < sigma; a++) {
		for (ll b = 0; b < sigma; b++) {
			for (ll c = 0; c < sigma; c++) {
				cin >> rule[a][b][c];
				rule[a][b][c]--;
			}
		}
	}

	vector<ll> state(n);
	for (ll i = 0; i < n; i++) {
		cin >> state[i];
		state[i]--;
	}

	for (ll i = 0; i < n; i++) {
		for (ll a = 0; a < sigma; a++) {
			for (ll b = 0; b < sigma; b++) {
				for (ll c = 0; c < sigma; c++) {
					if (rule[a][b][c] == state[i]) {
						adj[(a * maxSigma + b) * maxN + i][b * maxSigma + c] = true;
					}
				}
			}
		}
	}
	for (ll a = 0; a < sigma; a++) {
			for (ll b = 0; b < sigma; b++) {
				bits seen = adj[(a * maxSigma + b) * maxN];
				for (ll i = 1; i < n; i++) {
					bits old;
					swap(old, seen);
					for (ll c = 0; c < sigma; c++) {
						for (ll d = 0; d < sigma; d++) {
							if (old[c * maxSigma + d]) {
								seen |= adj[(c * maxSigma + d) * maxN + i];
							}
						}
					}
				}
				if (seen[a * maxSigma + b]) {
					cout << "YES" << endl;
					return 0;
				}
			}
		}
	cout << "NO" << endl;
}
