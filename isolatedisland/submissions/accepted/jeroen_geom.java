import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.*;
import java.util.*;

public class jeroen_geom {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		int n = Integer.valueOf(in.readLine());
		Segment[] segments = new Segment[n];
		for(int i = 0; i < n; i++) {
			String[] ps = in.readLine().split(" ");
			Point p1 = new Point(Long.valueOf(ps[0]), Long.valueOf(ps[1]));
			Point p2 = new Point(Long.valueOf(ps[2]), Long.valueOf(ps[3]));
			segments[i] = new Segment(p1, p2);
		}

		PriorityQueue<SweepLine> Q = new PriorityQueue<SweepLine>();
		for(int i = 0; i < n; i++) {
			Q.offer(new SweepLine(segments[i].p1, i));
			Q.offer(new SweepLine(segments[i].p2, i));
		}
		ArrayList<Integer> sweep_segs = new ArrayList<Integer>();
		ArrayList<Integer> sweep_regions = new ArrayList<Integer>();
		sweep_regions.add(0);
		int[] seg_pos = new int[n];
		for(int i = 0; i < n; i++) seg_pos[i] = -1;
		int nr_regions = 1;
		ArrayList<Integer> eq_regions = new ArrayList<Integer>();
		ArrayList<Integer> adj_regions = new ArrayList<Integer>();
		while(!Q.isEmpty()) {
			Point p = Q.peek().p;
			ArrayList<Integer> incoming = new ArrayList<Integer>();
			TreeMap<Frac, Integer> outgoing_slopes = new TreeMap<Frac, Integer>();
			int min_pos = n + 1;
			int nr_in = 0;
			int nr_out = 0;
			while(!Q.isEmpty() && Q.peek().p.equals(p)) {
				int i = Q.peek().i;
				Segment s = segments[i];
				if(!s.p1.equals(p)) {
					incoming.add(i);
					nr_in++;
					min_pos = Math.min(min_pos, seg_pos[i]);
				}
				if(!s.p2.equals(p)) {
					outgoing_slopes.put(s.slope(), i);
					nr_out++;
				}
				while(!Q.isEmpty() && Q.peek().p.equals(p) && Q.peek().i == i)
					Q.poll();
			}

			if(nr_in == 0) {
				int lower = -1;
				int upper = sweep_segs.size();
				while(upper - lower > 1) {
					int middle = (lower + upper) / 2;
					if(p.isAbove(segments[sweep_segs.get(middle)]))
						lower = middle;
					else
						upper = middle;
				}
				if(upper < sweep_segs.size() && collinear(segments[sweep_segs.get(upper)].p1, segments[sweep_segs.get(upper)].p2, p)) {
					int i = sweep_segs.get(upper);
					incoming.add(i);
					nr_in++;
					outgoing_slopes.put(segments[i].slope(), i);
					nr_out++;
				}
				min_pos = upper;
			}
			

			// The regions directly below and above the intersection
			int bottom_region = sweep_regions.get(min_pos);
			int top_region = sweep_regions.get(min_pos + nr_in);

			// Resize sweep_segs and sweep_regions
			if(nr_in < nr_out) {
				sweep_segs.addAll(min_pos, Collections.nCopies(nr_out - nr_in, 0));
				sweep_regions.addAll(min_pos, Collections.nCopies(nr_out - nr_in, 0));
			} else if(nr_in > nr_out) {
				// TODO: maybe this is a bit inefficient
				for(int i = 0; i < nr_in - nr_out; i++) {
					sweep_segs.remove(min_pos);
					sweep_regions.remove(min_pos);
				}
			}

			// Reset positions of incoming segments
			for(int i : incoming) {
				seg_pos[i] = -1;
			}

			// Update sweep_segs and seg_pos
			int j = 0;
			for(Map.Entry<Frac,Integer> slope : outgoing_slopes.entrySet()) {
				sweep_segs.set(min_pos+j, slope.getValue());
				seg_pos[slope.getValue()] = min_pos + j;
				j++;
			}
			if(nr_in != nr_out) {
				for(int i = min_pos + nr_out; i < sweep_segs.size(); i++) {
					seg_pos[sweep_segs.get(i)] = i;
				}
			}

			// Update sweep regions
			sweep_regions.set(min_pos, bottom_region);
			if(nr_out == 0) {
				eq_regions.add(bottom_region);
				eq_regions.add(top_region);
			} else {
				sweep_regions.set(min_pos+nr_out, top_region);
			}
			for(int i = 1; i < nr_out; i++) {
				sweep_regions.set(min_pos+i, nr_regions);
				nr_regions++;
			}

			// Add new adjacencies
			for (int i = 0; i < nr_out; i++) {
				adj_regions.add(sweep_regions.get(min_pos+i));
				adj_regions.add(sweep_regions.get(min_pos+i+1));
			}

			// Add new events to Q
			ArrayList<Integer> pot_intersections = new ArrayList<Integer>();
			if(min_pos - 1 >= 0 && min_pos < sweep_segs.size()) {
				pot_intersections.add(min_pos - 1);
			}
			if(nr_out > 0 && min_pos + nr_out < sweep_segs.size()) {
				pot_intersections.add(min_pos + nr_out - 1);
			}
			for(int i : pot_intersections) {
				Point intersection = null;
				Segment s1 = segments[sweep_segs.get(i)];
				Segment s2 = segments[sweep_segs.get(i+1)];
				if( (intersection = s1.intersect(s2)) != null && intersection.compareTo(p) > 0) {
					Q.offer(new SweepLine(intersection, sweep_segs.get(i)));
					Q.offer(new SweepLine(intersection, sweep_segs.get(i+1)));
				}
			}
		}

		// Merge faces that are the same
		TreeSet<Integer>[] eq = new TreeSet[nr_regions];
		for(int i = 0; i < nr_regions; i++)
			eq[i] = new TreeSet<Integer>();
		for(int i = 0; i < eq_regions.size(); i += 2) {
			int a = eq_regions.get(i);
			int b = eq_regions.get(i+1);
			eq[a].add(b);
			eq[b].add(a);
		}

		int[] plot_index = new int[nr_regions];
		for(int i = 0; i < nr_regions; i++) plot_index[i] = -1;
		int nr_plots = 0;
		for(int i = 0; i < nr_regions; i++) {
			if(plot_index[i] < 0) {
				nr_plots++;
				ArrayList<Integer> r = new ArrayList<Integer>();
				r.add(i);
				for(int q = 0; q < r.size(); q++) {
					int j = r.get(q);
					if(plot_index[j] >= 0) continue;
					plot_index[j] = nr_plots - 1;
					for(int k : eq[j])
						r.add(k);
				}
			}
		}

		ArrayList<Integer>[] adj = new ArrayList[nr_plots];
		for(int i = 0; i < nr_plots; i++) adj[i] = new ArrayList<Integer>();
		for(int i = 0; i < adj_regions.size(); i += 2) {
			int a = adj_regions.get(i);
			int b = adj_regions.get(i+1);
			adj[plot_index[a]].add(plot_index[b]);
			adj[plot_index[b]].add(plot_index[a]);
		}

		// Compute distances from the ocean
		int[] dist = new int[nr_plots];
		boolean[] visited = new boolean[nr_plots];
		for(int i = 0; i < nr_plots; i++) {
			visited[i] = false;
			dist[i] = -1;
		}
		ArrayList<Integer> r = new ArrayList<Integer>();
		r.add(0);
		dist[0] = 0;
		for(int q = 0; q < r.size(); q++) {
			int i = r.get(q);
			visited[i] = true;
			for(int j : adj[i]) {
				if(dist[j] >= 0) continue;
				dist[j] = dist[i] + 1;
				r.add(j);
			}
		}
		for(int i = 0; i < nr_plots; i++) {
			for(int j : adj[i]) {
				if(dist[i] == dist[j]) {
					System.out.println("yes");
					return;
				}
			}
		}
		System.out.println("no");
	}

	public static boolean collinear(Point p1, Point p2, Point p3) {
		return p2.minus(p1).cross(p3.minus(p1)).compareTo(new Frac(0)) == 0;
	}

	public static long gcd(long a, long b) {
		return b == 0 ? a : gcd(b, a % b);
	}

	static class SweepLine implements Comparable<SweepLine> {
		public Point p;
		public int i;

		public SweepLine(Point p, int i) {
			this.p = p;
			this.i = i;
		}

		public int compareTo(SweepLine other) {
			int c = p.compareTo(other.p);
			if(c != 0) return c;
			return i - other.i;
		}
	}

	static class Point implements Comparable<Point> {
		public Frac x, y;
		public Point(Frac x, Frac y) {
			this.x = x;
			this.y = y;
		}
		public Point(long x, long y) {
			this(new Frac(x), new Frac(y));
		}

		public boolean equals(Object other) {
			Point o = (Point)other;
			return o.x.equals(x) && o.y.equals(y);
		}

		public int compareTo(Point other) {
			int c = x.compareTo(other.x);
			if(c != 0) return c;
			return y.compareTo(other.y);
		}

		public Frac slope() {
			return y.div(x);
		}

		public Point minus(Point p) {
			return new Point(x.minus(p.x), y.minus(p.y));
		}

		public Point add(Point p) {
			return new Point(x.add(p.x), y.add(p.y));
		}
		
		public Frac dot(Point p) {
			return x.times(p.x).add(y.times(p.y));
		}

		public Frac cross(Point p) {
			return x.times(p.y).minus(y.times(p.x));
		}

		public boolean isAbove(Segment s) {
			if(s.p1.x.equals(s.p2.x))
				return y.compareTo(s.p2.y) > 0;
			return s.p2.minus(s.p1).cross(this.minus(s.p1)).compareTo(new Frac(0)) > 0;
		}

		public String toString() {
			return "(" + x + ", " + y + ")";
		}
	}

	static class Segment {
		public Point p1, p2;

		public Segment(Point p1, Point p2) {
			if(p1.compareTo(p2) < 0) {
				this.p1 = p1;
				this.p2 = p2;
			} else {
				this.p1 = p2;
				this.p2 = p1;
			}
		}

		public Frac slope() {
			return p2.minus(p1).slope();
		}

		public Point intersect(Segment s) {
			Point d1 = p2.minus(p1);
			Point d2 = s.p2.minus(s.p1);
			if(d1.cross(d2).compareTo(new Frac(0)) == 0) {
				if(p1.compareTo(s.p1) == 0)
					return p2;
				else if(p1.compareTo(s.p2) == 0)
					return p1;
				else
					return null;
			}
			Point p = p1.add(s.p1.minus(p1).cross(d2).div(d1.cross(d2)).dot(d1));
			if(p1.compareTo(p) <= 0 && p.compareTo(p2) <= 0 && s.p1.compareTo(p) <= 0 && p.compareTo(s.p2) <= 0)
				return p;
			return null;
		}

		public String toString() {
			return p1 + " " + p2;
		}
	}
	
	static class Frac implements Comparable<Frac> {
		private long p, q;

		public Frac(long x) {
			this(x, 1);
		}
		
		public Frac(long p, long q) {
			if(q < 0) {
				p = -p;
				q = -q;
			}
			this.p = p;
			this.q = q;
		}

		public Frac add(Frac o) {
			return new Frac(p*o.q + o.p * q, q * o.q);
		}

		public Frac minus(Frac o) {
			return new Frac(p * o.q - o.p * q, q * o.q);
		}

		public Frac times(Frac o) {
			return new Frac(p * o.p, q * o.q);
		}

		public Point dot(Point p) {
			return new Point(p.x.times(this), p.y.times(this));
		}

		public Frac div(Frac o) {
			return new Frac(p * o.q, q * o.p);
		}

		public boolean equals(Object other) {
			Frac o = (Frac)other;
			return this.compareTo(o) == 0;
		}

		public int compareTo(Frac o) {
			// First look at the most significant bits, this may exceed 64 bits
			int c = Long.compare(Math.multiplyHigh(p, o.q), Math.multiplyHigh(o.p, q));
			if(c != 0) return c;
			return Long.compareUnsigned(p * o.q, o.p * q);
		}

		public String toString() {
			return p + "/" + q;
		}
	}
}
