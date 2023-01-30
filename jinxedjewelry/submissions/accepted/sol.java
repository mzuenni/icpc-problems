import java.util.Scanner;
import java.util.Arrays;
import java.lang.Math;

public class sol {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		int t = s.nextInt();
		for (int i = 0; i < t; i++) {
			int n = s.nextInt();
			long[] in = new long[n];
			for (int j = 0; j < n; j++) {
				in[j] =  s.nextInt();
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
			
			System.out.println(res);
		}
	}

}