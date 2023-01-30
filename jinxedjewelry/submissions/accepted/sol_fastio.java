import java.util.Scanner;
import java.util.Arrays;
import java.lang.Math;
import java.io.BufferedReader;
import java.io.BufferedOutputStream;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.IOException;
import java.util.StringTokenizer;

public class sol_fastio {

	public static class FastIO {
		static BufferedReader r	= new BufferedReader(new InputStreamReader(System.in));
		static StringTokenizer tokens = new StringTokenizer("");
		static PrintStream out = new PrintStream(new BufferedOutputStream(System.out), false);
		
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


	public static void main(String[] args) throws IOException {
		int t = FastIO.nextInt();
		for (int i = 0; i < t; i++) {
			int n = FastIO.nextInt();
			long[] in = new long[n];
			for (int j = 0; j < n; j++) {
				in[j] =  FastIO.nextInt();
			}

			Arrays.sort(in); //this is potentially n^2, do we want a tets for this?
			
			long res = n;
			long sum = 0;
			for (int j = 0; j < n; j++) {
				long remain = n-j-1;
				sum += in[j];
				if (sum <= remain) {
					res = Math.min(res, remain);
				} else {
					res = Math.min(res, remain + 1);
					break;
				}
			}
			
			FastIO.out.println(res);
		}
		FastIO.out.close();
	}

}