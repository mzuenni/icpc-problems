import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.*;
import java.util.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		int n = Integer.valueOf(in.readLine());
		Point[] pts = new Point[n*2];
		for(int i = 0; i < n; i++) {
			String[] ps = in.readLine().split(" ");
			pts[i*2] = new Point(Long.valueOf(ps[0]), Long.valueOf(ps[1]));
			pts[i*2+1] = new Point(Long.valueOf(ps[2]), Long.valueOf(ps[3]));
		}

		Arrays.sort(pts);
		for(int i = 0; i < n * 2; i += 2) {
			if(!pts[i].equals(pts[i+1])) {
				System.out.println("yes");
				return;
			}
		}
		System.out.println("no");
	}

	static class Point implements Comparable<Point> {
		public long x, y;
		public Point(long x, long y) {
			this.x = x;
			this.y = y;
		}

		public boolean equals(Object other) {
			Point o = (Point)other;
			return x == o.x && y == o.y;
		}

		public int compareTo(Point other) {
			int c = Long.compare(x, other.x);
			if(c != 0) return c;
			return Long.compare(y, other.y);
		}
	}
}
