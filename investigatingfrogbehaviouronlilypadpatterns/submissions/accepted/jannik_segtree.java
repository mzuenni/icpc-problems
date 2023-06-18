import java.util.*;

public class jannik_segtree {
	static final int oo = 0x3f3f3f3f;
	static class Tree {
		int f(int a, int b) { return Math.min(a, b); } // any associative function
		int[] s;
		public int n;
		public Tree(int n) {
			this.n = n;
			s = new int[2*n];
		}
		public void update(int i, int val) {
			for(s[i += n] = val; (i /= 2) > 0; )
				s[i] = f(s[i*2], s[i*2+1]);
		}
		public int query(int b, int e) { // query [b, e)
			int ra = oo, rb = oo;
			for(b += n, e += n; b < e; b /= 2, e /= 2) {
				if(b % 2 != 0) ra = f(ra, s[b++]);
				if(e % 2 != 0) rb = f(s[--e], rb);
			}
			return f(ra, rb);
		}
	}
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int n = in.nextInt();
		int[] pos = new int[n];

		Tree tree = new Tree((int) 2.1e6);
		for (int i = 0; i < tree.n; i++)
			tree.update(i, i);

		for (int i = 0; i < n; i++) {
			pos[i] = in.nextInt();
			tree.update(pos[i], oo);
		}

		for (int q = in.nextInt(); q-- > 0; ) {
			int i = in.nextInt() - 1;

			tree.update(pos[i], pos[i]);
			pos[i] = tree.query(pos[i]+1, tree.n);
			tree.update(pos[i], oo);
			System.out.println(pos[i]);
		}
	}
}
