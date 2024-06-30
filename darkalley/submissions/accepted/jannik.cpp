#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

using u64 = uint64_t;

constexpr u64 M = 1e9 + 7;

u64 powm(u64 x, u64 e) {
	if (e == 0) return 1;
	u64 s = powm(x, e / 2);
	(s *= s) %= M;
	if (e % 2) (s *= x) %= M;
	return s;
}

u64 inv(u64 x) { return powm(x, M - 2); }

template <typename T>
struct segtree_t {
	static constexpr T unit = 0;
	T f(const T& a, const T& b) { return (a + b) % M; }
	vector<T> s;
	u64 n;
	segtree_t(u64 n = 0, T init = unit) : s(2 * n, init) , n(n) { }
	void add(u64 i, const T& val) {
		for ((s[i += n] += val) %= M; i /= 2;)
			s[i] = f(s[i * 2], s[i * 2 + 1]);
	}
	T query(u64 b, u64 e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2 != 0) ra = f(ra, s[b++]);
			if (e % 2 != 0) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main()
{
	u64 n, num_q, f;
	cin >> n >> num_q;
	{
		string a;
		cin >> a;
		assert(a.substr(0, 2) == "0.");
		u64 q = powm(10, a.size() - 2);
		u64 p = q - stoull(a.substr(2));
		f = (p * inv(q)) % M;
	}
	const u64 f_inv = inv(f);

	vector<u64> pow_f(n, 1), pow_i(n, 1);
	for (u64 i = 1; i < n; i++) {
		pow_f[i] = (pow_f[i-1] * f) % M;
		pow_i[i] = (pow_i[i-1] * f_inv) % M;
	}

	segtree_t<u64> r(n), l(n);
	for (char c; num_q-- > 0 && cin >> c; )
		if (c == '?') {
			u64 x; cin >> x, x--;
			const u64 y = n - 1 - x;
			u64 res = (l.query(0, x + 1) * pow_f[x]) % M;
			res += (r.query(0, y + 1) * pow_f[y]) % M;
			cout << res % M << '\n';
		} else {
			u64 b, x; cin >> b >> x, x--;
			if (c == '-') b = M - b;
			l.add(x, (b * pow_i[x]) % M);
			if (u64 y = n - 1 - x; y + 1 < n)
				r.add(y + 1, (b * pow_i[y]) % M);
		}
	return 0;
}
