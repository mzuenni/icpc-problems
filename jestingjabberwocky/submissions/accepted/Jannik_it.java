import java.util.*;

public class Jannik_it {
	final static int MAXN = 101101;
	final static char[] k = {'h','d','c','s'};
	static int[] idx = new int[256];

	static String s;

	public static void main (String[] args) {
		for (int i = 0; i < 4; i++) idx[k[i]] = i;

		String s = new Scanner(System.in).next();

		int[][] mem = new int[4][1<<4];

		for (int i = 0; i < s.length(); i++) {
			int j = idx[s.charAt(i)];
			int[][] mem2 = new int[4][1<<4];

			for (int last = 0; last < 4; last++)
				for (int mask = 0; mask < (1<<4); mask++) {
					int res = Integer.MAX_VALUE;

					if (last == j)
						res = Math.min(res, mem[last][mask]);

					// remove i
					res = Math.min(res, 1 + mem[last][mask]);

					// choose s[i]
					if ((mask & (1<<j)) == 0)
						res = Math.min(res, mem[j][mask | (1<<j)]);
					
					mem2[last][mask] = res;
				}
			mem = mem2;
		}

		int res = Integer.MAX_VALUE;
		for (int i = 0; i < 4; i++)
			res = Math.min(res, mem[i][1<<i]);
		System.out.println(res);
	}
}
