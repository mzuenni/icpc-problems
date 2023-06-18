import java.util.*;
import java.util.stream.*;

public class Paul {
	final int N = 654321;
	final int M = 100;
	final int MOD = (int) 1e9 + 7;

	int mulMod(int x, int y) {
		return (int) ((long) x * y % MOD);
	}

	int expMod(int x, int n) {
		int res = 1;
		for (; n > 0; n /= 2) {
			if (n%2 == 1) res = mulMod(res, x);
			x = mulMod(x, x);
		}
		return res;
	}

	int invMod(int x) {
		return expMod(x, MOD-2);
	}

	void run() {
		Scanner sc = new Scanner(System.in);
		int x = sc.nextInt();

		int[] fib = new int[N];
		fib[1] = 1;
		for (int i = 2; i < N; i++) {
			fib[i] = (fib[i-1] + fib[i-2]) % MOD;
		}

		int[] hash = new int[N];
		int[] len = new int[N];
		int[] bound = new int[N];
		int[] prev = new int[N];

		hash[0] = 1;
		len[0] = 0;
		bound[0] = M-1;
		prev[0] = -1;

		int j = 1;
		outer:
		for (int i = 0; ; i++) {
			for (int k = 3; k <= bound[i]; k++) {
				if (len[i]+k > M) continue;
				hash[j] = mulMod(hash[i], fib[k]);
				len[j] = len[i]+k;
				bound[j] = k;
				prev[j] = i;
				if (++j == N) break outer;
			}
		}

		int[] indices = IntStream.range(0, N).boxed().sorted(Comparator.comparingInt(i -> hash[i]))
								 .mapToInt(Integer::intValue).toArray();

		for (int i = 0; i < N; i++) {
			int y = mulMod(x, invMod(hash[i]));
			int lo = 0, hi = N;
			while (hi-lo > 1) {
				int md = (lo+hi)/2;
				if (hash[indices[md]] <= y) lo = md; else hi = md;
			}
			if (hash[indices[lo]] == y) {
				String res = "#";
				for (int k: new int[]{i, indices[lo]}) {
					for (; k > 0; k = prev[k]) {
						res += ".".repeat(bound[k]-1) + "#";
					}
				}
				if (res.length() > 1) res = res.substring(1);
				System.out.println(res);
				System.out.println(res);
				return;
			}
		}
		System.out.println(".##\n##.");
	}

	public static void main(String[] args) {
		new Paul().run();
	}
}
