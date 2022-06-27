import java.util.ArrayList;
import java.util.Scanner;

public class mzuenniScanner {
	
	public static class Point {
		public long x, y, id;
		Point(Scanner in) {
			x = in.nextLong();
			y = in.nextLong();
			id = -1;
		}
		
		Point(long _x, long _y) {
			x = _x;
			y = _y;
			id = -1;
		}
		
		public void sub(Point p) {
			x -= p.x;
			y -= p.y;
		}
		
		public long cross(Point o) {
			return x*o.y - o.x*y;
		}
		
		public long norm() {
			return x*x+y*y;
		}
	}
	
	public static long merge(Point[] v, Point[] left, Point[] right) {
		int a = 0, b = 0, i = 0;
		long inv = 0;
		while (a < left.length && b < right.length) {
			if (left[a].id < right[b].id) v[i++] = left[a++];
			else {
				inv += left.length - a;
				v[i++] = right[b++];
			}
		}
		while (a < left.length) v[i++] = left[a++];
		while (b < right.length) v[i++] = right[b++];
		return inv;
	}

	public static long mergeSort(Point[] v) {
		int n = v.length;
		Point[] left = new Point[n/2];
		Point[] right = new Point[(n+1)/2];
		for (int i = 0; i < n / 2; i++) left[i] = v[i];
		for (int i = n / 2; i < n; i++) right[i - n / 2] = v[i];

		long result = 0;
		if (left.length > 1) result += mergeSort(left);
		if (right.length > 1) result += mergeSort(right);
		return result + merge(v, left, right);
	}
	
	public static long solve(ArrayList<Point> in, Point e) {
		in.sort((a,b) -> {
			if (a.cross(b) == 0) {
				return Long.compare(b.norm(), a.norm());
			} else {
				return Long.compare(a.cross(b), 0);
			}
		});
		for (int i = 0; i < in.size(); i++) {
			in.get(i).id = i;
			in.get(i).sub(e);
		}
		in.sort((a,b) -> {
			if (a.cross(b) == 0) {
				return Long.compare(a.norm(), b.norm());
			} else {
				return Long.compare(a.cross(b), 0);
			}
		});
		return mergeSort(in.toArray(Point[]::new));
	}

	public static void main(String[] args) {		
		Scanner in = new Scanner(System.in);//dont do this...
		Point s = new Point(in);
		Point e = new Point(in);
		e.sub(s);
		Point orth = new Point(-e.y, e.x);
		int n = in.nextInt();
		ArrayList<Point> upper = new ArrayList<>();
		ArrayList<Point> lower = new ArrayList<>();
		for (int i = 0; i < n; i++) {
			Point c = new Point(in);
			c.sub(s);
			if (e.cross(c) > 0 || (e.cross(c) == 0 && orth.cross(c) < 0)) upper.add(c);
			else lower.add(new Point(-c.x+e.x, -c.y+e.y));
		}
		in.close();
		System.out.println(solve(upper, e) + solve(lower, e));
	}

}
