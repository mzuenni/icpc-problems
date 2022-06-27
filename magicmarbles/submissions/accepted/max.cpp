#include <bits/stdc++.h>
#include <ext/rope>

using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;

using __gnu_cxx::rope;
using __gnu_cxx::char_producer;

constexpr int NOCOLOR = -1;

struct chain {
    // (color, i, len)
    struct Run { int color; size_t pos; size_t len; };
    using rope_t = rope<Run>;
    rope_t data;
    size_t max_run;

    chain(size_t max_run) : max_run(max_run) { }

    struct Generator : public char_producer<Run> {
        int color;
        size_t length;

        Generator(const Generator&) = default;
        Generator(Generator&&) = default;
        Generator(int color, size_t length) : color(color), length(length) { }
        Generator& operator=(const Generator&) = default;
        Generator& operator=(Generator&&) = default;

        virtual ~Generator() {
        }

        void operator()(size_t start, size_t len, Run* buffer) override {
            for (size_t i = 0; i < len; ++i) {
                buffer[i] = {color, start + i, length};
            }
        }
    };

    rope_t make_run(int color, size_t length) {
        Generator* gen = new Generator(color, length);
        return rope_t(gen, length, color);
    }

    Run run_at(size_t i) {
        if (i >= data.size()) {
            return Run {NOCOLOR, 0, 0};
        } else {
            return data[i];
        }
    }

    size_t insert(size_t pos, int color) {
        Run run = run_at(pos);
        auto start = pos - run.pos;
        auto len = run.len;
        assert(pos <= data.size());
        Run run_before = run_at(pos - 1);
        size_t deletion = 0;
        if (run.color == color) {
            data.erase(start, len);
            if (len + 1 < max_run) {
                data.insert(start, make_run(color, len + 1));
            } else {
                deletion = start;
            }
        } else if (run_before.color == color) {
            auto bstart = pos - run_before.pos - 1;
            auto blen = run_before.len;
            data.erase(bstart, blen);
            if (blen + 1 < max_run) {
                data.insert(bstart, make_run(color, blen + 1));
            } else {
                deletion = bstart;
            }
        } else {
            data.erase(start, len);
            data.insert(start, make_run(run.color, run.pos));
            data.insert(pos, make_run(color, 1));
            data.insert(pos + 1, make_run(run.color, run.len - run.pos));
        }

        while (deletion > 0 && run_at(deletion).color == run_at(deletion - 1).color) {
            auto first = run_at(deletion - 1);
            auto second = run_at(deletion);
            assert(second.pos == 0);
            auto start = deletion - first.len;
            auto len = first.len + second.len;
            deletion = start;
            data.erase(start, len);
            if (len < max_run) {
                data.insert(start, make_run(first.color, len));
            } 
        }

        return data.size();
    }

    inline size_t size() {
        return data.size();
    }

    vector<Run> flatten() {
        return vector(data.begin(), data.end());
    }
};

int main() {
    ll n, k, q;
    cin >> n >> k >> q;
    chain c(k);
    for (ll i = 0; i < n; ++i) {
        ll m;
        cin >> m;
        c.insert(c.size(), m);
    }
    for (ll i = 0; i < q; ++i) {
        ll p, m;
        cin >> p >> m;
        cout << c.insert(p, m) << '\n';
    }
}
