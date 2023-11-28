#include <bits/stdc++.h>
using namespace std;

vector<int> find_random_partition(const vector<int> &a, int n, double timeout) {
	clock_t start = clock();
	vector<int> v(n+1);
	while (double(clock()-start)/CLOCKS_PER_SEC < timeout) {
		int r = n, k = 0, m = size(a);
		while (r > 0) {
			while (m > 0 && a[m-1] > r) m--;
			if (m == 0) break;
			int i = a[m-1] == r ? m-1 : rand() % m;
			v[k] = a[i];
			r -= v[k++];
		}
		if (r == 0) {
			v.resize(k);
			return v;
		}
	}
	return {};
}

void fail() {
	cout << "impossible" << '\n';
	exit(0);
}

void print_vector(const vector<int> &v) {
	int n = size(v);
	cout << n << '\n';
	for (int i = 0; i < n; i++) {
		cout << v[i] << " \n"[i+1==n];
	}
}

int main() {
	srand(17);

	int m, n;
	cin >> m >> n;

	vector<int> a(m);
	for (int &x: a) {
        cin >> x;
    }
	sort(begin(a), end(a));
	a.erase(unique(begin(a), end(a)), end(a));
	while (!a.empty() && a.back() > n) a.pop_back();
	m = size(a);

    for (int z = 0; z < 4; z++)
    {
        auto v = find_random_partition(a, n, 0.05);
        if (v.empty()) fail();
        //sort(begin(v), end(v), greater<int>());

        vector<int> w = v, u = v, pos(w.size());
        for (int i = 1; i < size(u); i++) u[i] += u[i-1];
        reverse(begin(w), end(w));

        clock_t start = clock();
        while (double(clock()-start)/CLOCKS_PER_SEC < 0.65) {
            int sum = 0, j = 0, c = 0;
            for (int i = 0; i < v.size()-1; i++)
            {
                sum += w[i];
                while (sum > u[j]) j++;
                if (sum == u[j])
                {
                    pos[c++] = i;
                }
            }
            if (c == 0)
            {
                cout << "possible" << '\n';
                print_vector(v);
                print_vector(w);
                return 0;
            }
            else
            {
                for (int i = 0; i < c; i++)
                {
                    if (pos[i] < v.size()-1) swap(w[pos[i]], w[pos[i]+1]);
                    else swap(w[pos[i]], w[0]);
                }
            }
        }
    }


	fail();
}
