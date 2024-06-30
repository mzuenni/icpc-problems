import java.util.Scanner;
import java.util.Arrays;
import java.util.Locale;
import java.lang.Long;
import java.lang.Math;

public class sol {

	public static final long mod = 1000000007;	
	public static final long decimals = 1000000;

	public static long powMod(long a, long b, long n) {
		long res = 1;
		while (b > 0) {
			if ((b & 1) != 0) res = (a * res) % n;
			a = (a * a) % n;
			b /= 2;
		}
		return res;
	}
	public static long powMod(long a, long b) {
		return powMod(a, b, mod);
	}
	public static long powMod(long a) {
		return powMod(a, mod - 2);
	}

	public static class FT {
		long[] tree;

		void update(int i, long val) {
			for (i++; i < tree.length; i += (i & (-i))) {
				tree[i] += val;
				tree[i] %= mod;
			}
		}

		FT(int n) {
			tree = new long[n + 1];
		}

		long prefix_sum(int i) {
			long sum = 0;
			for (i++; i > 0; i -= (i & (-i))) sum += tree[i];
			return sum % mod;
		}

	}

	public static class fast {
		FT lr, rl;
		int n;
		long mul, div;
		fast(int n, long mul) {
			lr = new FT(n);
			rl = new FT(n);
			this.n = n;
			this.mul = mul;
			div = powMod(mul);
		}
		void update(int pos, long light) {
			rl.update(n - pos, light*powMod(div, n - 1 - pos));
			lr.update(pos, light*powMod(div, pos));
		}
		long get(int pos) {
			return  rl.prefix_sum(n - 1 - pos) * powMod(mul, n - 1 - pos) +
					lr.prefix_sum(pos) * powMod(mul, pos);
		}
	}

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in).useLocale(Locale.US);
		int n = s.nextInt();
		int q = s.nextInt();
		double p = s.nextDouble();
		long pp = ((decimals - (long)Math.round(p*decimals)) * powMod(decimals)) % mod;
		fast sol = new fast(n, pp);
		for (int i = 0; i < q; i++) {
			String type = s.next();
			if (type.equals("+")) {
				long b = s.nextLong();
				int x = s.nextInt();
				sol.update(x - 1, b);
			} else if (type.equals("-")) {
				long b = s.nextLong();
				int x = s.nextInt();
				sol.update(x - 1, mod-b);
			} else {
				int x = s.nextInt();
				System.out.println(sol.get(x - 1) % mod);
			}
		}
	}
}
