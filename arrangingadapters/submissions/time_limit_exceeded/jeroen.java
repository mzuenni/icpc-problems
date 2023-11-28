import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	static int[] w;

	public static void main(String[] args) throws Exception {
		// Read input
		String[] ps = in.readLine().split(" ");
		int n = Integer.valueOf(ps[0]);
		int s = Integer.valueOf(ps[1]);
		w = new int[n];
		ps = in.readLine().split(" ");
		for(int i = 0; i < n; i++)
			w[i] = Integer.valueOf(ps[i]);

		// Sort and plug in both ends first
		Arrays.sort(w);
		if (n == 1 || s == 1) {
			System.out.println("1");
			return;
		}
		int res = 2;
		n -= 2;
		s -= 2;

		// Now fill from small to big, and if we make gaps
		// we keep that info so that we can swap in some
		// other adaptor later. We only need to keep that
		// info modulo 3.
		for(int i = 0; i < n; i += 2) {
			// Get the adapter, see if we can swap it into
			// an earlier gap, and count the number of sockets
			int c1 = swapAdapter(i);
			int s1 = (c1 + 2) / 3;

			// Check if this plug still fits
			if(s1 > s) break;
			res++;
			s -= s1;

			// Now place the next one opposite
			if(i + 1 < n) {
				int c2 = swapAdapter(i+1);
				int s2 = (c1 + c2 + 2) / 3 - s1;

				if(s2 > s) break;
				s -= s2;
				res++;
			}
		}
		System.out.println(res);
	}

	static int swapAdapter(int i) {
		// Linear search for gaps
		int gap10 = 0;
		int gap11 = 0;
		int gap20 = 0;
		int gap22 = 0;
		for(int j = i - (i%2) - 2; j >= 0; j -= 2) {
			int c1 = w[j];
			int c2 = w[j+1];

			if((c1 % 3) + (c2 % 3) == 2) {
				if((c1 % 3) == 0 || (c2 % 3) == 0) {
					if(w[i] % 3 == 1) {
						w[j] += 1;
						w[i] -= 1;
						return w[i];
					}
				}
				else {
					if(w[i] % 3 == 2) {
						w[j] += 1;
						w[i] -= 1;
						return w[i];
					}
				}
			} else if((c1 % 3) + (c2 % 3) == 1) {
				if(w[i] % 3 == 2) {
					w[j] += 2;
					w[i] -= 2;
					return w[i];
				}
			} else if((c1 % 3) + (c2 % 3) == 4) {
				if(w[i] % 3 == 1) {
					w[j] += 2;
					w[i] -= 2;
					return w[i];
				}
			}
		}
		return w[i];
	}
}
