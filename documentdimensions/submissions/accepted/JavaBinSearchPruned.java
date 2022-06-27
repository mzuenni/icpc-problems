import java.util.*;

public class JavaBinSearchPruned {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[] w = new int[n];
		int maxLen = 0;
		for (int i = 0; i < n; i++) {
			w[i] = in.next().length();
			maxLen = Math.max(maxLen, w[i]);
		}
		int[] pfx = new int[n+1];
		for (int i = 0, s = 0; i < n; i++)
			pfx[i + 1] = (s += w[i] + 1);

		int res = Integer.MAX_VALUE;
outer:
		for (int s = maxLen; s <= pfx[n]; s++) {
			int i = 0, lines = 0;
			while (i < n) {
				lines++;
				if (lines + s >= res) continue outer;
				int lo = i + 1, hi = n+1;
				while (lo + 1 < hi) {
					int m = lo + (hi - lo) / 2;
					if (pfx[m] > pfx[i] - 1 + s) hi = m;
					else lo = m;
				}
				if (hi - i > 1 && hi <= n && pfx[hi] - pfx[i] - 1 > s) hi--;
				i = hi;
			}
			res = Math.min(res, lines + s);
		}
		System.out.println(res);
	}
}
