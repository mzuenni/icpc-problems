// Same as run_time_error/Paul.java, but all complex number arithmetic has been inlined.
import java.util.*;

public class PaulOptimized {
	// Based on https://cp-algorithms.com/algebra/fft.html
	void fft(double[] a, double[] b, int sign) {
		int n = a.length;
		for (int i = 1, j = 0; i < n; i++) {
			int bit = n/2;
			for (; (j & bit) > 0; bit /= 2) j ^= bit;
			j ^= bit;

			if (i < j) {
				double h;
				h = a[i]; a[i] = a[j]; a[j] = h;
				h = b[i]; b[i] = b[j]; b[j] = h;
			}
		}

		for (int len = 2; len <= n; len *= 2) {
			double ang = 2*sign*Math.PI / len;
			double cos = Math.cos(ang), sin = Math.sin(ang);
			for (int i = 0; i < n; i += len) {
				double x = 1, y = 0;
				for (int j = 0; j < len/2; j++) {
					int p = i+j, q = i+j+len/2;
					double ux = a[p], uy = b[p];
					double vx = a[q]*x - b[q]*y;
					double vy = a[q]*y + b[q]*x;

					a[p] = ux + vx; b[p] = uy + vy;
					a[q] = ux - vx;	b[q] = uy - vy;
					
					double nx = x*cos - y*sin;
					double ny = x*sin + y*cos;
					x = nx; y = ny;
				}
			}
		}

		if (sign < 0) {
			for (int i = 0; i < n; i++) {
				a[i] /= n; b[i] /= n;
			}
		}
	}

	final int K = 26;
	int decode(char c) { return c-'a'; }

	void reverse(double[] a, int from, int to) {
		to--;
		while (from < to) {
			double h = a[from]; a[from] = a[to]; a[to] = h;
			from++; to--;
		}
	}

	void solve() {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		String a = sc.next();
		String b = sc.next();

		int m = 1;
		while (m < 4*K*n) m *= 2;

		double[] px = new double[m];
		double[] py = new double[m];
		double[] qx = new double[m];
		double[] qy = new double[m];
		
		for (int i = 0; i < n; i++) {
			int c = decode(a.charAt(i)), d = decode(b.charAt(i));
			px[2*i*K + c] = 1;
			qx[2*i*K + d] = 1;
			qx[(2*i+1)*K + d] = 1;
		}
		reverse(qx, 0, 2*K*n);
		reverse(qy, 0, 2*K*n);

		fft(px, py, 1);
		fft(qx, qy, 1);

		double[] pqx = new double[m];
		double[] pqy = new double[m];
		for (int i = 0; i < m; i++) {
			pqx[i] = px[i]*qx[i] - py[i]*qy[i];
			pqy[i] = px[i]*qy[i] + py[i]*qx[i];
		}

		fft(pqx, pqy, -1);

		int[] r = new int[2*K*n];
		for (int i = 0; i < m; i++) {
			r[i%(2*K*n)] += Math.round(pqx[i]);
		}

		int best = 0;
		for (int i = 0; i < 2*K*n; i++) {
			if (i%(2*K) >= K) best = Math.max(best, r[i]);
		}

		System.out.println(n-best);
	}

	public static void main(String[] args) {
		new PaulOptimized().solve();
	}
}
