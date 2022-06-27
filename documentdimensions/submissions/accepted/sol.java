import java.util.Scanner;
import java.lang.Math;

public class sol {

	public static int solve(int[] in) {
		int[] pref = new int[in.length + 1];
		int ma = 1;
		for (int i = 0; i < in.length; i++) {
			pref[i+1] = pref[i] + in[i] + 1;
			ma = Math.max(ma, in[i] + 1);
		}
		int[] inv = new int[2*pref[in.length] + 5];
		for (int i = 0; i < pref.length; i++) inv[pref[i]] = i;
		for (int i = 1; i < inv.length; i++) {
			inv[i] = Math.max(inv[i], inv[i - 1]);
		}
		int res = 0x3FFFFFFF;
		for (int l = ma; l <= pref[in.length]; l++) {
			int rows = 0;
			for (int i = 0; i < in.length; rows++) {
				int lim = pref[i] + l;
				i = inv[lim];
			}
			res = Math.min(res, l - 1 + rows);
		}
		return res;
	}

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);//dont do this...
		int n = s.nextInt();
		int[] in = new int[n];
		for (int i = 0; i < n; i++) {
			String tmp = s.next();
			in[i] = tmp.length();
		}
		s.close();
		System.out.println(solve(in));
	}

}