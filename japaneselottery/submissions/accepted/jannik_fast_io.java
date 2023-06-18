import java.util.*;
import java.io.*;

public class jannik_fast_io {
	static int n;
	static class Perm {
		int[] p;
		Perm() {
			p = new int[n];
			for (int i = 0; i < n; i++) p[i] = i;
		}
		Perm(int x) {
			this();
			p[p[x+1] = x] = x+1;
		}
		Perm mul(Perm rhs) {
			Perm res = new Perm();
			for (int i = 0; i < n; i++)
				res.p[i] = rhs.p[ p[i] ];
			return res;
		}
		int solve() {
			boolean[] vis = new boolean[n];
			int cycles = 0;
			for (int i = 0; i < n; i++) {
				if (vis[i]) continue;
				cycles++;
				for (int x = i; !vis[x]; x = p[x])
					vis[x] = true;
			}
			return n - cycles;
		}
	}
	static class Tree {
		int h;
		Perm[] s;
		Tree(int h) {
			this.h = h;
			s = new Perm[2*h];
			for (int i = 0; i < 2*h; i++) s[i] = new Perm();
		}
		void update(int i, int x) {
			i += h;
			for (s[i] = s[i].mul(new Perm(x)); (i /= 2) > 0; )
				s[i] = s[i*2].mul( s[i*2+1] );
		}
		Perm query(int b, int e) { // query [b, e)
			Perm ra = new Perm(), rb = ra;
			for (b += h, e += h; b < e; b /= 2, e /= 2) {
				if (b % 2 != 0) ra = ra.mul( s[b++] );
				if (e % 2 != 0) rb = s[--e].mul( rb );
			}
			return ra.mul( rb );
		}
	}
	static int nextInt(StringTokenizer st) {
		return Integer.parseInt(st.nextToken());
	}
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		n = nextInt(st);
		int h = nextInt(st), q = nextInt(st);

		Tree t = new Tree(h);

		while (q-- > 0) {
			st = new StringTokenizer(br.readLine());
			int y = nextInt(st)-1, x1 = nextInt(st)-1, x2 = nextInt(st)-1;
			if (x1 > x2) x1 = x2;

			t.update(y, x1);

			bw.append( t.query(0, h).solve() + "\n" );
		}

		bw.close();
	}
}
