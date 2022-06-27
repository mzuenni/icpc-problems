#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <complex.h>
#define rep(E, F) for (E = 0; E < (F); E++)
typedef long long ll;
typedef struct { ll x, y; } pt;
ll min(ll a, ll b) { if (a > b) return b; return a; }
ll max(ll a, ll b) { if (a < b) return b; return a; }

ll get_int()
{
	ll r = 0, c = getchar(), s = 1;
	while (c != '-' && c < '0' || c > '9') c = getchar();
	while (c == '-') s *= -1, c = getchar();
	while (c >= '0' && c <= '9') r = r*10 + c - '0', c = getchar();
	return s*r;
}

#define MAXN 400000
#define LEFT(x) ((x)*2)
#define RIGHT(x) ((x)*2 + 1)
ll pp[5*MAXN + 1], o[5*MAXN + 1], pn = MAXN;

void prop(ll x, ll y, ll e)
{ // Fall sem dreifir lygnum uppfærslum niður um eina hæð.
	pp[e] += (y - x + 1)*o[e];   
	if (x != y) o[LEFT(e)] += o[e], o[RIGHT(e)] += o[e];
	o[e] = 0;
}
ll qrec(ll i, ll j, ll x, ll y, ll e)
{ // Við erum að leita að bili [x, y] og erum í [i, j].
	prop(i, j, e);
	if (x == i && y == j) return pp[e];
	ll m = (i + j)/2;
	if (y <= m) return qrec(i, m, x, y, LEFT(e));
	else if (x > m) return qrec(m + 1, j, x, y, RIGHT(e));
	return qrec(i, m, x, m, LEFT(e)) + qrec(m + 1, j, m + 1, y, RIGHT(e));
}
ll query(ll x, ll y)
{ // Finnum summuna yfir [x, y].
	if (y == -1) return 0;
	return qrec(0, pn - 1, x, y, 1);
}
void urec(ll i, ll j, ll x, ll y, ll z, ll e)
{ // Við erum að leita að bili [x, y] og erum í [i, j].
	prop(i, j, e);
	if (x == i && y == j) { o[e] = z; return; }
	ll m = (i + j)/2;
	pp[e] += (y - x + 1)*z;
	if (y <= m) urec(i, m, x, y, z, LEFT(e));
	else if (x > m) urec(m + 1, j, x, y, z, RIGHT(e));
	else urec(i, m, x, m, z, LEFT(e)), urec(m + 1, j, m + 1, y, z, RIGHT(e));
}
void update(ll x, ll z)
{ // Bætum z við stökin á bilinu [x, y]
	//printf("update %lld %lld\n", x, z);
	urec(0, pn - 1, x, x, z, 1);
}

typedef struct { pt x; ll y; } par;
ll sign(ll x)
{
	if (x == 0) return 0;
	return x < 0 ? -1 : 1;
}

ll closer(pt a, pt b, pt c, pt d)
{ // whos closer, a or b, to the line through c and d?
	// p/q
	//printf("comparing distance of (%lld %lld) and (%lld %lld)\n", a.x, a.y, b.x, b.y);
	ll p, q, ax = a.x, ay = a.y, bx = b.x, by = b.y, cx = c.x, cy = c.y, dx = d.x, dy = d.y;
	p = (cy - dy)*(cx - ax) + (dx - cx)*(cy - ay);
	q = (bx - ax)*(cy - dy) + (dx - cx)*(by - ay);
	//printf("  with p = %lld\n", (ll)p);
	//printf("   and q = %lld\n", (ll)q);
	if (q == 0) return 0;
	if (sign(p) != sign(q)) return -1; // p/q is negative so a is closer
	p *= sign(p), q *= sign(q);
	assert(p > q);
	if (p*2 == q) return 0;
	return p*2 < q ? -1 : 1;
}

pt c, d; // given line in problem
int distcmp(const void* p1, const void* p2)
{
	pt a = ((par*)p1)->x, b = ((par*)p2)->x;
	return closer(a, b, c, d);
}

ll ccw(pt a, pt b, pt c)
{
	ll x1 = a.x, y1 = a.y, x2 = b.x, y2 = b.y, x3 = c.x, y3 = c.y, r;
	r = x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
	if (r == 0) return r;
	return r < 0 ? 1 : -1;
}

ll sqdist(pt a, pt b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

pt piv;
ll sgn;
int angcmp(const void* p1, const void* p2)
{
	pt a = ((par*)p1)->x, b = ((par*)p2)->x;
	ll r = -ccw(a, piv, b);
	//printf(">> ccw((%lld, %lld), (%lld, %lld), (%lld, %lld)) = %lld\n", a.x, a.y, piv.x, piv.y, b.x, b.y, ccw(a, piv, b));
	if (r == 0) return sgn*sqdist(a, piv) < sgn*sqdist(b, piv) ? 1 : -1;
	return r;
}

void compress(par *p, ll n)
{
	ll i, j, k;
	qsort(p, n, sizeof *p, distcmp);
	//printf("fdsafdsafdsafdsafdsafdsafdsafdsafdsafdsafdsafdsafdsafdsaf\n");
	//rep(i, n) rep(j, n) printf("test: %lld\n", closer(p[i].x, p[j].x, c, d));
	for (i = j = k = 0; i < n; i = j, j = i, k++) while (j < n && closer(p[i].x, p[j].x, c, d) == 0) p[j++].y = k;
}

ll sgns[4] = {-1, 1, 1, -1}, ss = 0;
ll sweep(par *p, ll n, pt o)
{
	ll r = 0, i;
	piv = o;
	sgn = sgns[ss++];
	//printf(">> sgn = %lld\n", sgn);
	qsort(p, n, sizeof *p, angcmp);
	//printf("> sweeping for\n"); rep(i, n) printf(" >> (%lld %lld) | %lld\n", p[i].x.x, p[i].x.y, p[i].y);
	rep(i, 5*n + 1) pp[i] = 0;
	rep(i, n) update(p[i].y, 1);
	rep(i, n) r += query(0, p[i].y - 1), update(p[i].y, -1);
	//printf("the sweep is returning r = %lld\n", r);
	return r;
}

par p[MAXN];
ll solve(pt *a, ll n, pt c, pt d)
{
	ll i, r = 0;
	rep(i, n) p[i].x = a[i];
	compress(p, n);
	ll x = sweep(p, n, c), y = sweep(p, n, d);
	//printf("swepps give: %lld %lld\n", x, y);
	r = llabs(x - y);
	//printf("so we return %lld\n", r);
	return r;
}

int main()
{
	ll xs = get_int(), ys = get_int(), xe = get_int(), ye = get_int();
	pt zs = {xs, ys}, ze = {xe, ye};
	c = zs, d = ze;
	ll i, n = get_int(), aa = 0, bb = 0, l = 0, r = 0;
	pt a[n], b[n];
	rep(i, n)
	{
		ll x = get_int(), y = get_int(), w;
		pt z = {x, y};
		w = ccw(z, c, d);
		if (w == 0) sqdist(z, c) < sqdist(z, d) ? l++ : r++;
		else if (w == 1) a[aa++] = z;
		else b[bb++] = z;
	}
	//printf(">> r, l = %lld %lld\n", r, l);
	ll x = l*(l - 1)/2 + r*(r - 1)/2;
	x += solve(a, aa, d, c);
   	x += solve(b, bb, d, c);
	printf("%lld\n", x);
	return 0;
}
