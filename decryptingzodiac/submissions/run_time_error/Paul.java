import java.util.*;

public class Paul {
	class Complex {
		double real, imag;

		Complex(double real, double imag) {
			this.real = real;
			this.imag = imag;
		}

		Complex add(Complex c) {
			return new Complex(real+c.real, imag+c.imag);
		}

		Complex subtract(Complex c) {
			return new Complex(real-c.real, imag-c.imag);
		}

		Complex multiply(Complex c) {
			return new Complex(real*c.real - imag*c.imag, real*c.imag + imag*c.real);
		}
	}

	// Based on https://cp-algorithms.com/algebra/fft.html
	void fft(Complex[] a, int sign) {
		int n = a.length;
		for (int i = 1, j = 0; i < n; i++) {
			int bit = n/2;
			for (; (j & bit) > 0; bit /= 2) j ^= bit;
			j ^= bit;

			if (i < j) {
				Complex c = a[i];
				a[i] = a[j];
				a[j] = c;
			}
		}

		for (int len = 2; len <= n; len *= 2) {
			double ang = 2*sign*Math.PI / len;
			Complex wlen = new Complex(Math.cos(ang), Math.sin(ang));
			for (int i = 0; i < n; i += len) {
				Complex w = new Complex(1, 0);
				for (int j = 0; j < len/2; j++) {
					Complex u = a[i+j], v = a[i+j+len/2].multiply(w);
					a[i+j] = u.add(v);
					a[i+j+len/2] = u.subtract(v);
					w = w.multiply(wlen);
				}
			}
		}

		if (sign < 0) for (Complex c: a) {
			c.real /= n;
			c.imag /= n;
		}
	}

	final int K = 26;
	int decode(char c) { return c-'a'; }

	void solve() {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		String a = sc.next();
		String b = sc.next();

		int m = 1;
		while (m < 4*K*n) m *= 2;

		Complex[] p = new Complex[m];
		Complex[] q = new Complex[m];
		for (int i = 0; i < m; i++) {
			p[i] = new Complex(0, 0);
			q[i] = new Complex(0, 0);
		}
		
		for (int i = 0; i < n; i++) {
			int c = decode(a.charAt(i)), d = decode(b.charAt(i));
			p[2*i*K + c].real = 1;
			q[2*i*K + d].real = 1;
			q[(2*i+1)*K + d].real = 1;
		}
		Collections.reverse(Arrays.asList(q).subList(0,2*K*n));

		fft(p,1);
		fft(q,1);

		Complex[] pq = new Complex[m];
		for (int i = 0; i < m; i++) {
			pq[i] = p[i].multiply(q[i]);
		}

		fft(pq,-1);

		int[] r = new int[2*K*n];
		for (int i = 0; i < m; i++) {
			r[i%(2*K*n)] += Math.round(pq[i].real);
		}

		int best = 0;
		for (int i = 0; i < 2*K*n; i++) {
			if (i%(2*K) >= K) best = Math.max(best, r[i]);
		}

		System.out.println(n-best);
	}

	public static void main(String[] args) {
		new Paul().solve();
	}
}
