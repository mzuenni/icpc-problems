import java.util.Scanner;
import java.util.Arrays;
import java.lang.Long;

public class simplified {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		int n = s.nextInt();
		int m = s.nextInt();
		long[][] in = new long[n][2];
		for (int i = 0; i < n; i++) {
			in[i][0] =  s.nextInt();
			in[i][1] =  s.nextInt();
		}
		s.close();

		Arrays.sort(in, (a, b) -> Long.compare(a[1]*b[0], b[1]*a[0]));
		
		long cost = 1;
		long res = 0;
		for (long[] e : in) {
			res += cost * e[0];
			cost += e[1];
		}
		
		System.out.println(res);
	}

}