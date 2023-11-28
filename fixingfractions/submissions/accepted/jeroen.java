import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;
import java.math.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		String[] ps = in.readLine().split(" ");
		String sa = ps[0];
		String sb = ps[1];
		long a = Long.valueOf(sa);
		long b = Long.valueOf(sb);
		BigInteger c = new BigInteger(ps[2]);
		BigInteger d = new BigInteger(ps[3]);

		// Brute force taking a subset of digits from 'a'
		int len = sa.length();
		for(long i = 1; i < (1L << len); i++) {
			// Construct the number with digits removed
			int[] removed = new int[10];
			long a2 = 0;
			for(int j = 0; j < len; j++) {
				if((i & (1L << j)) > 0) {
					// Prevent leading zeroes
					if(a2 == 0 && sa.charAt(j) == '0') {
						a2 = -1;
						break;
					}
					a2 *= 10;
					a2 += sa.charAt(j) - '0';
				} else {
					removed[sa.charAt(j) - '0']++;
				}
			}

			// What should 'b' be in this case, check if we
			// could make it.
			// a * d / c
			BigInteger ba2 = new BigInteger(String.valueOf(a2));
			BigInteger b2 = ba2.multiply(d).divide(c);
			if(!ba2.multiply(d).equals(c.multiply(b2))) continue;
			
			String sb2 = b2.toString();
			int k = 0;
			boolean ok = true;
			int[] removedb = new int[10];
			for(int j = 0; j < sb2.length(); j++) {
				while(k < sb.length() && sb.charAt(k) != sb2.charAt(j)) {
					removedb[sb.charAt(k) - '0']++;
					k++;
				}
				if(k == sb.length()) {
					ok = false;
					break;
				}
				k++;
			}
			while(k < sb.length()) {
				removedb[sb.charAt(k) - '0']++;
				k++;
			}

			for(int j = 0; j < 10; j++)
				ok &= removed[j] == removedb[j];
			if(ok) {
				System.out.println("possible");
				System.out.println(a2 + " " + b2);
				return;
			}
		}
		System.out.println("impossible");
	}
}
