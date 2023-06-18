import java.util.*;
import java.io.*;

public class jannik_ptr {
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
		Perm p;
		Tree l, r;
		Tree(int h) {
			this.h = h;
			p = new Perm();
			if (h != 1) {
				l = new Tree((h+1)/2);
				r = new Tree(h/2);
			}
		}
		void update(int i, int x) {
			if (l == null) {
				p = p.mul(new Perm(x));
			} else {
				if (i < (h+1)/2)
					l.update(i, x);
				else
					r.update(i - (h+1)/2, x);
				p = l.p.mul(r.p);
			}
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

			bw.append( t.p.solve() + "\n" );
		}

		bw.close();
	}
}
