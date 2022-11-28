#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define REP(i,n) rep(i,0,n)
#define all(v) (v).begin(), (v).end()
#define rs resize
#define DBG(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl

const ld PI = acos(-1.0);
template<class T> using min_queue =
priority_queue<T, vector<T>, greater<T>>;
template<class T> int sz(const T &x) {
    return (int) x.size(); // copy the ampersand(&)!
}

template<class T> ostream& operator<<(ostream &os, vector<T> &v) {
    os << "\n[";
    for(T &x : v) os << x << ',';
    return os << "]\n";
}

struct pairhash {
    public:
    template<typename T1, typename T2>
    size_t operator()(const pair<T1, T2> &p) const {
        size_t lhs = hash<T1>()(p.x);
        size_t rhs = hash<T2>()(p.y);
        return lhs ^ (rhs+0x9e3779b9+(lhs<<6)+(lhs>>2));
    }
};

bool lies_below(ii p1, ii p2, ii p3) {
    // Check whether p2 lies below p1p3
    return (p1.x-p2.x)*(p3.y-p2.y) - (p1.y-p2.y)*(p3.x-p2.x) <= 0;
}

vii getC(vii A) {
    sort(all(A));
    vii R;
    for (ii p : A) {
        while (R.size() >= 2 && lies_below(R[R.size()-2], R[R.size()-1], p)) {
            R.pop_back();
        }
        R.pb(p);
    }
    return R;
}

vii flip(vii A) {
    vii R;
    for (ii p : A) {
        R.pb({p.x, -p.y});
    }
    return R;
}

bool f(vii L, vii U) {
    L = getC(L);
    U = flip(getC(flip(U)));
    //for (ii a : L) {
    //    cout << a.x << ", " << a.y << " | ";
    //}
    //cout << endl;
    //for (ii a : U) {
    //    cout << a.x << ", " << a.y << " | ";
    //}
    cout << endl;
    cout << endl;
    ll i = 0, j = 0;
    while (i < L.size() || j < U.size()) {
        if (j == U.size() || (i < L.size() && L[i].x < U[j].x)) {
            if (j > 0 && j < U.size()) {
                if (!lies_below(U[j-1], L[i], U[j])) {
                    return false;
                }
            }
            i++;
        } else {
            if (i > 0 && i < L.size()) {
                if (!lies_below(L[i], U[j], L[i-1])) {
                    return false;
                }
            }
            j++;
        }
    }
    return true;
}

void run() {
	ll n;
    cin >> n;
    vii A(n), B(n), C(n), D(n);
    for (ll i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        A[i] = {min(x1, x2), min(y1, y2)};
        B[i] = {max(x1, x2), min(y1, y2)};
        C[i] = {min(x1, x2), max(y1, y2)};
        D[i] = {max(x1, x2), max(y1, y2)};
    }
    if (f(A, D) || f(B, C)) {
        cout << "possible" << endl;
    } else {
        cout << "impossible" << endl;
    }
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
    run();
    return 0;
}