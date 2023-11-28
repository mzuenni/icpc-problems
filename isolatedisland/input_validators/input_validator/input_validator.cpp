#include "validation.h"
#include <cassert>
#include <queue>
using namespace std;

typedef long long ll;

#define x first
#define y second

struct frac {
	/*
	Fraction
	May also be 1/0, in which case it is larger than any other value
	*/
	__int128 p,q;
	frac(__int128 n) {
		p = n; q = 1;
	}
	frac(__int128 a, __int128 b) {
		assert(a != 0 || b != 0);
		p = a; q = b;
	}

	std::strong_ordering operator<=>(const frac& b) const {
		__int128 ap = p, aq = q, bp = b.p, bq = b.q;
		if (aq < 0 || (aq == 0 && ap < 0)) {
			ap *= -1; aq *= -1;
		}
		if (bq < 0 || (bq == 0 && bp < 0)) {
			bp *= -1; bq *= -1;
		}
		return ap*bq <=> bp*aq;
	}
	bool operator==(const frac& b) const { return p*b.q == q*b.p; }
};

frac operator+(const frac a, const frac b) { return frac(a.p*b.q+b.p*a.q, a.q*b.q); }
frac operator-(const frac a, const frac b) { return frac(a.p*b.q-b.p*a.q, a.q*b.q); }
frac operator*(const frac a, const frac b) { return frac(a.p*b.p, a.q*b.q); }
frac operator/(const frac a, const frac b) { return frac(a.p*b.q, a.q*b.p); }

frac& operator+=(frac &a, const frac b) { return a = a+b; }
frac& operator-=(frac &a, const frac b) { return a = a-b; }
frac& operator*=(frac &a, const frac b) { return a = a*b; }
frac& operator/=(frac &a, const frac b) { return a = a/b; }

string to_string(frac a) { // Might break when values are too large
	if (a.q == 0) {
		return "1/0";
	} else if (a.p%a.q == 0) {
		return to_string((ll) (a.p/a.q));
	} else {
		return to_string((ll) a.p) + "/" + to_string((ll) a.q);
		//return to_string(((long double) a.p)/a.q);
	}
}

typedef pair<frac, frac> pt;
typedef pair<pt, pt> seg;

pt operator+(pt p, pt q) { return {p.x+q.x, p.y+q.y}; }
pt operator-(pt p, pt q) { return {p.x-q.x, p.y-q.y}; }
pt operator*(pt p, frac n) { return {p.x*n, p.y*n}; }
pt operator*(frac n, pt p) { return p*n; }

pt& operator+=(pt &p, pt q) { return p = p+q; }
pt& operator-=(pt &p, pt q) { return p = p-q; }

frac operator*(pt p, pt q) { return p.x*q.x + p.y*q.y; } // inner product
frac operator^(pt p, pt q) { return p.x*q.y - p.y*q.x; } // outer product

string to_string(pt p) {
	return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}
string to_string(seg s) {
	return to_string(s.x) + " " + to_string(s.y);
}

frac slope(pt p) { return p.y/p.x; }
frac slope(seg s) { return slope(s.y-s.x); }

bool collinear(pt p1, pt p2, pt p3) { return ((p2-p1)^(p3-p1)) == 0; }
bool is_above(pt p, seg s) {
	if (s.x.x == s.y.x) { // Vertical segment
		return p.y > s.y.y;
	} else {
		return ((s.y-s.x)^(p-s.x)) > 0;
	}
}

bool intersect(seg s1, seg s2, pt& p) {
	// Returns whether the segments intersect in a single point.
	// If they do, p becomes the intersection
	pt d1 = s1.y-s1.x, d2 = s2.y-s2.x;
	pt p1 = s1.x, p2 = s2.x;
	if ((d1^d2) == 0) { // Parallel
		if (s1.y == s2.x) {
			p = s1.y;
			return true;
		} else if (s1.x == s2.y) {
			p = s1.x;
			return true;
		} else {
			return false;
		}
	}
	p = p1+((p2-p1)^d2)/(d1^d2)*d1;
	assert(collinear(p, s1.x, s1.y) && collinear(p, s2.x, s2.y));
	return (s1.x <= p && p <= s1.y && s2.x <= p && p <= s2.y);
}

// Input bounds
const int MIN_N = 3;
const int MAX_N = 1'000;
const int MAX_COORD = 1'000'000;


int main(int argc, char *argv[]) {
	InputValidator v(argc, argv);

	//
	// Read input
	//
	ll n = v.read_integer("n", MIN_N, MAX_N);
	v.newline();

	vector<seg> segments;
	for (ll i = 0; i < n; i++) {
		frac x1(v.read_integer("x1", -MAX_COORD, MAX_COORD));
		v.space();
		frac y1(v.read_integer("y1", -MAX_COORD, MAX_COORD));
		v.space();
		frac x2(v.read_integer("x2", -MAX_COORD, MAX_COORD));
		v.space();
		frac y2(v.read_integer("y2", -MAX_COORD, MAX_COORD));
		v.newline();
		
		pt p1 = {x1,y1}, p2 = {x2,y2};
		v.check(p1 != p2, "Endpoints of segment "+to_string(i)+" coincide");
		if (p2 < p1) swap(p1, p2);
		seg s = {p1, p2};
		segments.push_back(s);
	}

	//
	// Check whether segments intersect in at most 1 point
	//
	for (ll i = 0; i < n; i++) {
		for (ll j = i+1; j < n; j++) {
			seg s = segments[i], t = segments[j];
			bool col = (collinear(s.x,s.y,t.x) && collinear(s.x,s.y,t.y));
			v.check(!col || s.y <= t.x || t.y <= s.x,
				"Segments "+to_string(i)+" and "+to_string(j)+" overlap");
		}
	}

	//
	// Build the dual graph using a sweep line
	//
	priority_queue<pair<pt, ll>, vector<pair<pt,ll>>, greater<pair<pt,ll>>> Q;
	for (ll i = 0; i < n; i++) {
		Q.push({segments[i].x, i});
		Q.push({segments[i].y, i});
	}
	vector<ll> sweep_segs; // The (indices of) segments currently intersecting the sweepline
	ll nr_regions = 1;
	vector<ll> sweep_regions = {0}; // The regions currently intersecting the sweepline
	vector<ll> seg_pos(n,-1); // The positions of the segments along the sweepline
	vector<pair<ll,ll>> eq_regions; // Pairs of regions that are actually the same
	vector<pair<ll,ll>> adj_regions; // Pairs of regions that touch along a segment

	while (!Q.empty()) {
		pt p = Q.top().x;
		vector<ll> incoming; // The segments through p that are partially to the left
		vector<pair<frac,ll>> outgoing_slopes; // Slopes + segs partially to the right of p
		ll min_pos = n+1; // The first position in sweep_segs of a seg passing through or over p
		ll nr_in = 0, nr_out = 0;
		while (!Q.empty() && Q.top().x == p) {
			ll i = Q.top().y;
			seg s = segments[i];
			if (s.x != p) {
				incoming.push_back(i);
				nr_in++;
				min_pos = min(min_pos, seg_pos[i]);
			}
			if (s.y != p) {
				outgoing_slopes.push_back({slope(s), i});
				nr_out++;
			}
			while (!Q.empty() && Q.top() == pair<pt,ll>{p, i}) Q.pop();
		}

		if (nr_in == 0) { // min_pos should be determined with binary search
			ll lower = -1, upper = sweep_segs.size();
			while (upper-lower > 1) {
				ll middle = (lower + upper)/2;
				if (is_above(p, segments[sweep_segs[middle]])) {
					lower = middle;
				} else {
					upper = middle;
				}
			}
			if (upper < sweep_segs.size() &&
					collinear(segments[sweep_segs[upper]].x,segments[sweep_segs[upper]].y,p)) {
				// Additional intersection found
				ll i = sweep_segs[upper];
				incoming.push_back(i);
				nr_in++;
				outgoing_slopes.push_back({slope(segments[i]), i});
				nr_out++;
			}
			min_pos = upper;
		}

		// The regions directly below and above the intersection
		ll bottom_region = sweep_regions[min_pos];
		ll top_region = sweep_regions[min_pos+nr_in];

		// Resize sweep_segs and sweep_regions
		if (nr_in < nr_out) {
			sweep_segs.insert(sweep_segs.begin()+min_pos, nr_out-nr_in, 0);
			sweep_regions.insert(sweep_regions.begin()+min_pos, nr_out-nr_in, 0);
		} else if (nr_in > nr_out) {
			sweep_segs.erase(sweep_segs.begin()+min_pos,
				sweep_segs.begin()+min_pos+nr_in-nr_out);
			sweep_regions.erase(sweep_regions.begin()+min_pos,
				sweep_regions.begin()+min_pos+nr_in-nr_out);
		}

		// Reset positions of incoming segments
		for (ll i : incoming) {
			seg_pos[i] = -1;
		}

		// Update sweep_segs and seg_pos
		sort(outgoing_slopes.begin(), outgoing_slopes.end());
		for (ll i = 0; i < nr_out; i++) {
			sweep_segs[min_pos+i] = outgoing_slopes[i].y;
			seg_pos[outgoing_slopes[i].y] = min_pos+i;
		}
		if (nr_in != nr_out) {
			for (ll i = min_pos+nr_out; i < sweep_segs.size(); i++) {
				seg_pos[sweep_segs[i]] = i;
			}
		}

		// Update sweep_regions
		sweep_regions[min_pos] = bottom_region;
		if (nr_out == 0) {
			eq_regions.push_back({bottom_region, top_region});
		} else {
			sweep_regions[min_pos+nr_out] = top_region;
		}
		for (ll i = 1; i < nr_out; i++) {
			sweep_regions[min_pos+i] = nr_regions;
			nr_regions++;
		}

		// Add new adjacencies
		for (ll i = 0; i < nr_out; i++) {
			adj_regions.push_back({sweep_regions[min_pos+i], sweep_regions[min_pos+i+1]});
		}

		// Add new events to Q
		vector<ll> pot_intersections;
		if (min_pos-1 >= 0 && min_pos < sweep_segs.size()) {
			pot_intersections.push_back(min_pos-1);
		}
		if (nr_out > 0 && min_pos+nr_out < sweep_segs.size()) {
			pot_intersections.push_back(min_pos+nr_out-1);
		}
		for (ll i : pot_intersections) {
			pt intersection(0,0);
			seg s1 = segments[sweep_segs[i]], s2 = segments[sweep_segs[i+1]];
			if (intersect(s1, s2, intersection) && intersection > p) {
				// There is an intersection in the future
				Q.push({intersection, sweep_segs[i]});
				Q.push({intersection, sweep_segs[i+1]});
			}
		}
	}

	//
	// Merge faces that are the same
	// and check that no segment has the same face on both sides
	//
	vector<vector<ll>> eq(nr_regions);
	for (pair<ll, ll> a : eq_regions) {
		eq[a.x].push_back(a.y);
		eq[a.y].push_back(a.x);
	}

	vector<ll> plot_index(nr_regions, -1);
	ll nr_plots = 0;
	for (ll i = 0; i < nr_regions; i++) {
		if (plot_index[i] < 0) {
			nr_plots++;
			vector<ll> R = {i};
			for (ll q = 0; q < R.size(); q++) {
				ll j = R[q];
				if (plot_index[j] >= 0) continue;
				plot_index[j] = nr_plots-1;
				for (ll k : eq[j]) {
					R.push_back(k);
				}
			}
		}
	}

	vector<vector<ll>> adj(nr_plots);
	for (pair<ll, ll> a : adj_regions) {
		v.check(plot_index[a.x] != plot_index[a.y],
			"There is a segment with the same plot on both sides.");
		adj[plot_index[a.x]].push_back(plot_index[a.y]);
		adj[plot_index[a.y]].push_back(plot_index[a.x]);
	}

	//
	// Check whether the dual graph is connected when removing the ocean
	//
	vector<bool> visited(nr_plots, false);
	vector<ll> R = {1};
	for (ll q = 0; q < R.size(); q++) {
		ll i = R[q];
		if (visited[i] || i == 0) continue;
		visited[i] = true;
		for (ll j : adj[i]) {
			R.push_back(j);
		}
	}
	for (ll i = 1; i < nr_plots; i++) {
		v.check(visited[i], "The island is not connected");
	}
}
