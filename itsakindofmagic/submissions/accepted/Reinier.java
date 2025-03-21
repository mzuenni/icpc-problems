import java.util.*;
import java.io.*;

public class Reinier {
	public static void main(String[] args) {
		int m = 1000000;
		long[] A = new long[m+1], B = new long[m+1], C = new long[m+1], D = new long[m+1];
		Arrays.fill(A, 1);
		Arrays.fill(B, 1);
		Arrays.fill(C, 1);
		Arrays.fill(D, 1);
		boolean[] isPrime = new boolean[m+1];
		Arrays.fill(isPrime, true);
		isPrime[0] = false;
		isPrime[1] = false;
		
		for (int i = 1; i <= m; i++) {
			if (!isPrime[i]) continue;
			long c = 0, pow = 1;
			while (pow*i <= m) {
				c++;
				pow *= i;
			}
			while (c > 0) {
				for (int j = (int) pow; j <= m; j += pow) {
					if (j%(pow*i) == 0) continue;
					isPrime[j] = false;
					A[j] *= 2*c*c+2*c+1;
					B[j] *= 2*(c/3)+1;
					C[j] *= 2*(c/2)+1;
					D[j] *= 2*c+1;
				}
				pow /= i;
				c--;
			}
			isPrime[i] = true;
		}
		
		for (int i = 1; i <= m; i++) {
			B[i] -= 1;
			C[i] -= 1;
			D[i] -= 1;
			A[i] -= 4*B[i] + 2*C[i] + 2*D[i] + 1;
		}
		
		long[] R = new long[m+1];
		for (int i = 1; i <= m; i++) {
			R[i] = R[i-1] + A[i];
		}

		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		for (int i = 0; i < t; i++) {
			long n = sc.nextLong();
			long c = (long) Math.cbrt(n);
			while ((c+1)*(c+1)*(c+1) <= n) c++;
			while (c*c*c > n) c--;
			System.out.println(R[(int) c]);
		}
	}
}
