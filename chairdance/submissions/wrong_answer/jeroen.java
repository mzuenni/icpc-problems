import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.*;
import java.util.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	
	public static void main(String[] args) throws Exception {
		// Read input
		String[] ps = in.readLine().split(" ");
		int n = Integer.valueOf(ps[0]);
		int q = Integer.valueOf(ps[1]);

		char[] qc = new char[q];
		int[] qx = new int[q];
		for(int i = 0; i < q; i++) {
			ps = in.readLine().split(" ");
			qc[i] = ps[0].charAt(0);
			qx[i] = Integer.valueOf(ps[1]);
		}

		// For each chair, which person is sitting there
		int[] person = new int[n];
		person[0] = n;
		for(int i = 1; i < n; i++)
			person[i] = i;

		// Handle queries, and only if the amount of people remaining
		// changes we update the person list
		long plus = 0;
		long mult = 1;
		int factor = 1; // how much shorter did the list become
		for(int i = 0; i < q; i++) {
			switch(qc[i]) {
			case '+': // accumulate these
				plus += qx[i];
				plus %= n;
				break;
			case '*':
				if(gcd(qx[i], person.length) == 1) {
					// Same people remain, so we can accumulate
					plus *= qx[i];
					plus %= n;
					mult *= qx[i];
					mult %= n;
				} else {
					// There are some overlaps, so we now simulate, and make
					// a new list with only the remaining 
					int newlen = person.length / gcd(qx[i], person.length);
					int prevfactor = factor;
					factor = n / newlen;
					int[] person2 = new int[newlen];

					int[] dist = new int[newlen];
					for(int j = 0; j < newlen; j++)
						dist[j] = person2[j] = -1;
					for(int j = 0; j < person.length; j++) {
						int jscaled = j * prevfactor;
						int to = (int)(((long)jscaled * mult + plus) % n);
						int to2 = (int)(((long)to * qx[i]) % n);
						int d = (to2 - to + n) % n;
						to2 /= factor;
						if(dist[to2] == -1 || d < dist[to2]) {
							person2[to2] = person[j];
							dist[to2] = d;
						}
					}
					plus = 0;
					mult = 1;
					person = person2;
				}
				break;
			case '?':
				// A query, so we have to apply the accumulated plus/times
				// backwards
				long j = qx[i];
				j += n - plus;
				j %= n;
				if(j % factor != 0)
					System.out.println("-1");
				else {
					j /= factor;
					j *= modInv(mult, person.length);
					j %= person.length;
					System.out.println(person[(int)j]);
				}
				break;
			default:
				throw new Exception("Unexpected query " + qc[i]);
			}
		}
	}

	static int gcd(int a, int b) {
		return b == 0 ? a : gcd(b, a % b);
	}

	// Yay, let's abuse the Java standard library
	static long modInv(long a, long n) {
		return new BigInteger(String.valueOf(a)).modInverse(new BigInteger(String.valueOf(n))).longValue();
	}
}
