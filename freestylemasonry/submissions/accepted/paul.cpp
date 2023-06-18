#include <bits/stdc++.h>
using namespace std;

bool solve() {
	int w, h;
	cin >> w >> h;

	int top = h;
	while (w--) {
		int bot; cin >> bot;
		if (bot > top) return false;
		if ((top-bot)%2 == 0) {
			top = min(top+1, h);
		} else {
			top = top-1;
		}
	}
	return top == h;
}

int main() {
	cout << (solve() ? "possible" : "impossible") << '\n';
}
