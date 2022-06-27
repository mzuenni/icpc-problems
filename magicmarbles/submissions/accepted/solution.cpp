#include <bits/stdc++.h>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

struct marble {
	ll color, pos, runLength;
};

struct marbleRun : char_producer<marble> {
private:
	ll color, runLength;
public:
	marbleRun(ll _color, ll _runLength) : color(_color), runLength(_runLength) {}
	marbleRun() : marbleRun(0, 0) {}

	virtual void operator()(size_t start_pos, size_t len, marble* buffer) {
		for (ll i = 0; i < len; i++) {
			buffer[i] = {color, (ll)start_pos + i, runLength};
		}
	}
};

constexpr ll qLim = 200000;
struct marbles {
private:
	marbleRun runMemory[qLim * 7];
	ll nextRun = 0;

	rope<marble> generateRun(ll color, ll runLength = 1) {
		runMemory[nextRun] = marbleRun(color, runLength);
		rope<marble> res(&runMemory[nextRun], runLength, false);
		nextRun++;
		return res;
	}

	rope<marble> state;
	ll maxRun = 0;
public:
	marbles() {
		state.append({-1, 0, 1});//guard
	}

	void setMaxRun(ll _maxRun) {
		maxRun = _maxRun;
	}

	ll size() {
		return sz(state) - 1;
	}

	void erase(ll pos) {
		if (pos < 0 || pos > sz(*this)) return;
		if (state[pos].runLength < maxRun) return;
		ll runLength = state[pos].runLength;
		pos -= state[pos].pos;
		state.erase(pos, runLength);
		if (pos > 0 && pos < sz(*this) && state[pos].color == state[pos-1].color) {
			//combine
			ll color = state[pos].color;
			runLength = state[pos].runLength + state[pos-1].runLength;
			pos = pos - 1 - state[pos - 1].pos;
			state.erase(pos, runLength);
			auto tmp = generateRun(color, runLength);
			state.insert(pos, tmp);
			erase(pos);
		}
	}

	void add(ll pos, ll color) {
		assert(pos >= 0 && pos <= sz(*this));

		if (pos > 0 && state[pos-1].color == color) pos--;

		ll otherLeft = state[pos].pos;
		ll otherPos = pos - otherLeft;
		ll otherlength = state[pos].runLength;
		ll otherColor = state[pos].color;

		state.erase(otherPos, otherlength);
		if (color == otherColor) {
			//append
			auto tmp = generateRun(color, otherlength + 1);
			state.insert(otherPos, tmp);
		} else {
			//split
			auto l = generateRun(otherColor, otherLeft);
			auto m = generateRun(color, 1);
			auto r = generateRun(otherColor, otherlength - otherLeft);
			state.insert(otherPos, r);
			state.insert(otherPos, m);
			state.insert(otherPos, l);
		}
		erase(pos);
	}
};

marbles state;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, k, q;
	cin >> n >> k >> q;
	state.setMaxRun(k);;
	for (ll i = 0; i < n; i++) {
		ll x;
		cin >> x;
		state.add(i, x);
	}
	for (ll i = 0; i < q; i++) {
		ll c, x;
		cin >> c >> x;
		state.add(c, x);
		cout << sz(state) << endl;
	}
}
