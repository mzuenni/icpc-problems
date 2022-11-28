import java.io.*;
import java.util.*;

public class PaulScanner {
	class Point {
		long x, y;

		public Point(long x, long y) {
			this.x = x;
			this.y = y;
		}

		Point subtract(Point p) {
			return new Point(x-p.x, y-p.y);
		}
		
		long cross(Point p) {
			return x*p.y - y*p.x;
		}

		int compare(Point p, Point q) {
			return Long.signum((q.x-x)*(p.y-y) - (q.y-y)*(p.x-x));
		}

		long squaredDistance(Point p) {
			return (p.x-x)*(p.x-x) + (p.y-y)*(p.y-y);
		}
	}

	Point[] convexHull(Point[] p) {
		if (p.length <= 2) return p;
		Arrays.sort(p, Comparator.<Point>comparingLong(a -> a.x).thenComparingLong(a -> a.y));
		Comparator<Point> cmp = (a,b) -> p[0].compare(a,b);
		Arrays.sort(p, 1, p.length, cmp.thenComparingLong(a -> p[0].squaredDistance(a)));
		int k = 2;
		for (int i = 2; i < p.length; i++) {
			for (p[k++] = p[i]; k >= 3 && p[k-3].compare(p[k-2],p[k-1]) >= 0; k--) {
				p[k-2] = p[k-1];
			}
		}
		return Arrays.copyOf(p,k);
	}
	
	boolean hasDividingLine(Point[] a, Point[] b) {
		Point v = a[1].subtract(a[0]);
		int j = 0;
		for (int k = 1; k < b.length; k++) {
			if (v.cross(b[k]) > v.cross(b[j])) j = k;
		}
		for (int i = 0; i < a.length; i++) {
			v = a[(i+1)%a.length].subtract(a[i]);
			while (v.cross(b[(j+1)%b.length]) > v.cross(b[j])) j = (j+1)%b.length;
			if (v.cross(b[j]) <= v.cross(a[i])) return true;
		}
		return false;
	}

	void run() throws Exception {
		Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		int n = sc.nextInt();
		Point[][] corners = new Point[4][n];
		for (int i = 0; i < n; i++) {
			int x1 = sc.nextInt();
			int y1 = sc.nextInt();
			int x2 = sc.nextInt();
			int y2 = sc.nextInt();
			corners[0][i] = new Point(x1, y1);
			corners[1][i] = new Point(x1, y2);
			corners[2][i] = new Point(x2, y2);
			corners[3][i] = new Point(x2, y1);
		}
		
		for (int k = 0; k < 4; k++) {
			corners[k] = convexHull(corners[k]);
		}
		
		boolean res = n == 1;
		for (int k = 0; k < 4; k++) {
			res = res || hasDividingLine(corners[k], corners[(k+2)%4]);
		}
		System.out.println(res ? "possible" : "impossible");
	}

	public static void main(String[] args) throws Exception {
		new PaulScanner().run();
	}
}
