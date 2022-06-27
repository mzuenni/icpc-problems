import java.util.*;

public class Jannik {

	final static int MAXN = 101101;
	final static char[] k = {'h','d','c','s'};
	static int[] idx = new int[256];

	static String s;

	static final int[][][] mem = new int[MAXN][4][1<<4];

	static int go(int i, int last, int mask) {
		if (i < 0) return 0;

		int res = Integer.MAX_VALUE;
		if (i == s.length()) {
			for (int l = 0; l < 4; l++)
				res = Math.min(res, go(i-1, l, (1<<l)));
			return res;
		}
		if (mem[i][last][mask] != -1) return mem[i][last][mask];

		int j = idx[s.charAt(i)];

		if (last == j)
			res = Math.min(res, go(i-1, last, mask));

		// remove i
		res = Math.min(res, 1 + go(i-1, last, mask));

		// choose s[i]
		if ((mask & (1<<j)) == 0) {
			res = Math.min(res, go(i-1, j, (mask | (1<<j))));
		}

		return mem[i][last][mask] = res;
	}
	public static void main(String[] args) {
		for (int i = 0; i < 4; i++) idx[k[i]] = i;

		for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < 4; j++)
				for (int k = 0; k < (1<<4); k++)
					mem[i][j][k] = -1;

		s = new Scanner(System.in).next();
		System.out.println(go(s.length(), 0, 0));
	}
}
