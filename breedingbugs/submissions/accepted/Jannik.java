import java.util.*;

public class Jannik {
	static class IntList extends ArrayList<Integer> {}
	static final int MAXN = 755;

	static int[] matchedTo = new int[MAXN];
	static boolean[] vis = new boolean[MAXN];
	static IntList[] adj = new IntList[MAXN]; // sufficient to add edges in one direction

	static boolean dfs(int i) {
		int ls = matchedTo[i];
		if (ls == -1) return true;
		if (vis[i]) return false;
		vis[i] = true;
		for (int j : adj[ls])
			if (dfs(j)) {
				matchedTo[matchedTo[j] = ls] = j;
				return true;
			}
		return false;
	}
	static int maxMatching(int n) {
		Arrays.fill(matchedTo, -1);
		int res = 0;
		for (int i = 0; i < n; i++)
			if (matchedTo[i] == -1) {
				Arrays.fill(vis, false);
				for (int j : adj[i])
					if (dfs(j)) {
						matchedTo[matchedTo[j] = i] = j;
						res++;
						break;
					}
			}
		return res;
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();

		int[] a = new int[n];
		int n2 = 0, max = 0;
		boolean one = false;
		for (int i = 0; i < n; i++) {
			int x = in.nextInt();
			if (x != 1 || !one) {
				a[n2++] = x;
				max = Math.max(max, x);
			}
			one |= x == 1;
		}
		n = n2;

		for (int i = 0; i < n; i++)
			adj[i] = new IntList();

		boolean[] not_prime = new boolean[2 * max + 1];
		not_prime[0] = not_prime[1] = true;
		for (long p = 2; p < not_prime.length; p++)
			if (!not_prime[(int)p])
				for (long j = p*p; j < (long) not_prime.length; j += p)
					not_prime[(int)j] = true;

		for (int i = 0; i < n; i++)
			if (a[i] % 2 == 0)
				for (int j = 0; j < n; j++)
					if (!not_prime[a[i]+a[j]])
						adj[i].add(j);

		System.out.println(n - maxMatching(n));
	}
}
