import java.util.*;

public class Paul {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int n = sc.nextInt();
		int m = sc.nextInt();

		int[] f = new int[m*m*m];
		for (int v = 0; v < m*m*m; v++) {
			f[v] = sc.nextInt() - 1;
		}

		int[] a = new int[n];
		for (int i = 0; i < n; i++) {
			a[i] = sc.nextInt() - 1;
		}

		for (int x = 0; x < m; x++) {
			for (int y = 0; y < m; y++) {
				boolean[] dp = new boolean[m*m];
				dp[m*x+y] = true;
				for (int c: a) {
					boolean[] ndp = new boolean[m*m];
					for (int v = 0; v < m*m*m; v++) {
						if (f[v] == c && dp[v/m]) {
							ndp[v%(m*m)] = true;
						}
					}
					dp = ndp;
				}
				if (dp[m*x+y]) {
					System.out.println("yes");
					return;
				}
			}
		}
		System.out.println("no");
	}
}
