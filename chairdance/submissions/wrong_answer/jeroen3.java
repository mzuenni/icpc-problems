import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.*;
import java.util.*;

public class jeroen3 {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		String[] ps = in.readLine().split(" ");
		long n = Integer.valueOf(ps[0]);
		long q = Integer.valueOf(ps[1]);

		char[] qc = new char[(int)q];
		long[] qx = new long[(int)q];
		for(int i = 0; i < q; i++) {
			ps = in.readLine().split(" ");
			qc[i] = ps[0].charAt(0);
			qx[i] = Long.valueOf(ps[1]);
		}

		// For each chair, which person is sitting there
		int[] person = new int[(int)n];
		person[0] = (int)n;
		for(int i = 1; i < n; i++)
			person[i] = i;

		// Handle queries, and only if the amount of people remaining
		// changes we update the person list
		long plus = 0;
		long mult = 1;
		long factor = 1; // how much shorter did the list become
		for(int i = 0; i < q; i++) {
			switch(qc[i]) {
			case '+': // accumulate these
				plus += qx[i];
				plus %= n;
				break;
			case '*':
				if(gcd(qx[i], person.length) == 1) {
					// Same people remain, so we can accumulate
					//plus *= qx[i];
					//plus %= n;
					mult *= qx[i];
					mult %= n;
				} else {
					// There are some overlaps, so we now simulate, and make
					// a new list with only the remaining 
					long newlen = person.length / gcd(qx[i], person.length);
					long prevfactor = factor;
					factor = n / newlen;
					int[] person2 = new int[(int)newlen];
					long[] dist = new long[(int)newlen];
					long newplus = 0;
					for(int j = 0; j < newlen; j++)
						dist[j] = -1;
					for(long j = 0; j < person.length; j++) {
						long jscaled = j * prevfactor;
						long to = (jscaled * mult + plus) % n;
						long to2 = (to * qx[i]) % n;
						long d = (to2 - to + n) % n;
						newplus = to2 % factor;
						to2 /= factor;
						if(dist[(int)to2] == -1 || d < dist[(int)to2]) {
							person2[(int)to2] = person[(int)j];
							dist[(int)to2] = d;
						}
					}
					plus = newplus;
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

	static long gcd(long a, long b) {
		return b == 0 ? a : gcd(b, a % b);
	}

	// Yay, let's abuse the Java standard library
	static long modInv(long a, long n) {
		return new BigInteger(String.valueOf(a)).modInverse(new BigInteger(String.valueOf(n))).longValue();
	}
}
