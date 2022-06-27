import java.util.Scanner;
import java.lang.Math;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Locale;

public class sol {

	public static long mul = 1000;
	public static double eps = 1e-9;

	public static class mix implements Comparable<mix> {
		long c, cp, part;
		mix(long _c, long _cp) {
			c = _c*mul;
			cp = _cp;
			part = _cp * _c;
		}

		@Override
		public int compareTo(mix other) {
			return Long.compare(this.cp, other.cp);
		}
	}

	public static double solve(ArrayList<mix> a,
							   ArrayList<mix> b,
							   double total,
							   double part,
							   long p) {
		for (mix e : a) {
			total += e.c;
			part += e.part;
		}
		for (mix e : b) {
			//(part+y*e.part)/(total+y*e.c)==p/mul
			//(part+y*e.part)*mul==p*(total+y*e.c)
			//mul*part+mul*y*e.part==p*total+p*y*e.c
			//mul*y*e.part-p*y*e.c==p*total-mul*part
			//y*(mul*e.part-p*e.c)==p*total-mul*part
			//y==(p*total-mul*part)/(mul*e.part-p*e.c)
			double y = (p*total-mul*part)/(mul*e.part-p*e.c);
			if (y < 0) y = 0;
			if (y > 1) y = 1;
			//y = clamp(y, 0, 1);
			total += y*e.c;
			part += y*e.part;
		}
		if (Math.abs(part*mul/total-p) > eps) return 0;
		return total;
	}

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in).useLocale(Locale.US);//dont do this...
		int n = s.nextInt();
		long p = (long)(s.nextDouble() * mul);

		ArrayList<mix> less = new ArrayList<>();
		ArrayList<mix> more = new ArrayList<>();

		long total = 0;
		long part = 0;
		for (int i = 0; i < n; i++) {
			long c = s.nextLong();
			long cp = (long)(s.nextDouble() * mul);
			mix cur = new mix(c, cp);
			if (cp == p) {
				total += cur.c;
				part += cur.part;
			} else if (cp < p) less.add(cur);
			else more.add(cur);
		}
		s.close();

		Collections.sort(less);
		Collections.reverse(less);
		Collections.sort(more);

		double a = solve(less, more, total, part, p);
		double b = solve(more, less, total, part, p);

		System.out.println(Math.max(a, b)/mul);
	}

}