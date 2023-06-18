#include <iostream>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

using ll = long long;
using vll = vector<ll>;

#define sz(a) ((ll)(a).size())

bool valid(const string& s) {
	ll o = 0;
	for (char c : s) {
		o += c == '(' ? 1 : -1;
		if (o < 0) return false;
	}
	return o == 0;
}

int main() {
	const auto start = chrono::system_clock::now();

	string s;
	cin >> s;
	ll n = s.size();
	
	mt19937 gen(random_device{}());
	uniform_int_distribution<> distrib(0, n-1);

	while (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start).count()/1e3 < 0.95) {
		ll i = distrib(gen);
		const string tmp = s.substr(i) + s.substr(0, i);
		if (not valid(tmp) or tmp == s) continue;
		cout << tmp << endl;
		return 0;
	}
	cout << "no\n";

	return 0;
}
