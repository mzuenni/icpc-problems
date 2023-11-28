import java.util.Scanner;
import java.util.Queue;
import java.util.Arrays;
import java.util.Collections;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.Set;
import java.util.TreeSet;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class bitset {

	public static class Vector extends ArrayList<Integer> {}

	public static class FastIO {
		static BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
		static StringTokenizer tokens = new StringTokenizer("");
		
		static boolean hasNext() throws IOException {
			while (!tokens.hasMoreTokens()) {
				String line = r.readLine();
				if (line == null) return false;
				tokens = new StringTokenizer(line);
			}
			return true;
		}

		static String next() throws IOException {
			hasNext();
			return tokens.nextToken();
		}
		
		static int nextInt() throws IOException {
			return Integer.parseInt(next());
		}

	}

	public static final int lim = 300007;
	public static long[] dp = new long[lim / 64 + 7];
	public static int n = 0;
	public static int w = 0;
	public static int[] ws;

	public static boolean getDp(int i) {
		return ((dp[i / 64] >>> (i & 63)) & 1L) != 0L;
	}

	public static void clearDp(int i) {
		dp[i / 64] &= ~(1L << (i & 63));
	}

	public static void orDp(int i, boolean value) {
		if (value) dp[i / 64] |= 1L << (i & 63);
	}

	public static ArrayDeque<Integer> reconstruct(int first){
		Vector res = new Vector();
		res.add(first);
		int remains = w - first;
		for (int j = n - 1; j >= 0; j--) {
			while (remains >= ws[j] && getDp(remains - ws[j])) {
				remains -= ws[j];
				res.add(ws[j]);
			}
		}
		Collections.sort(res);
		return new ArrayDeque<Integer>(res);
	}

	public static void main(String args[]) throws IOException {
		n = FastIO.nextInt();
		w = FastIO.nextInt();
		ws = new int[n];
		for (int i = 0; i < n; i++) {
			ws[i] = FastIO.nextInt();
		}
		ws = Arrays.stream(ws).sorted().distinct().sorted().toArray();
		n = ws.length;

		dp[0] = 1;
		for (int x : ws) {
			if (getDp(w)) break;
			boolean neq = false;
			for (int i = x; i <= w; i += x) neq |= getDp(i);
			if (x < 64) {//multiple set operations for same long
				for (int i = x; i < w; i++) orDp(i, getDp(i - x));
			} else {
				int ia = x / 64;
				int ib = x & 63;
				for (int i = 0; 64*i+x < w; i++) {
					dp[i + ia] |= dp[i] << ib;
					if (ib != 0) dp[i + ia + 1] |= dp[i] >>> (64 - ib);
				}
				clearDp(w);//we know it wasnt set before
			}
			if (x == w || w % x != 0 || neq) orDp(w, getDp(w - x));
		}

		int divs = 0;
		for (int x : ws) if (w % x == 0) divs++;

		if (!getDp(w) && divs < 2) {
			System.out.println("impossible");
		} else {
			System.out.println("possible");
			ArrayList<ArrayDeque<Integer>> rows = new ArrayList<ArrayDeque<Integer>>();
			for (int x : ws) {
				if (getDp(w - x)) {
					ArrayDeque<Integer> row = reconstruct(x);
					int mi = row.peekFirst();
					int ma = row.peekLast();
					rows.add(row);
					if (row.size() == 1) {
						rows.clear();
						rows.add(row);
						rows.add(row);
					}
					if (rows.size() == 2) break;
					if (mi == ma) continue;
					rows.remove(rows.size() - 1);
					
					if (w % ma == 0) {
						row.addLast(mi);
						row.removeFirst();
						rows.add(row);
						rows.add(new ArrayDeque<Integer>());
						for (int i = 0; i < w; i += ma) rows.get(rows.size() - 1).addLast(ma);
						break;
					} else {
						row = reconstruct(ma);
						mi = row.peekFirst();
						rows.add(row.clone());
						while (row.peekFirst() == mi) {
							row.addLast(mi);
							row.removeFirst();
						}
						rows.add(row);
						break;
					}
				}
			}
			for (ArrayDeque<Integer> v : rows) {
				System.out.println(v.size());
				for (int x : v) System.out.print(x + " ");
				System.out.println();
			}
		}
	}
}
