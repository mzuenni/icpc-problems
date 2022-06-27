import java.util.Scanner;
import java.lang.Math;

public class chris_v3 {

	public static class Node {
		int col;
		int prio = (int)(Math.random() * 0x3FFFFFFF);
		Node left = null;
		Node right = null;
		int size = 1;

		int lcol;
		int rcol;
		int lrun=1;
		int rrun=1; // stats
		Node (int _col) {
			col = _col;
			lcol = _col;
			rcol = _col;
		}
	}

	public static int size(Node t) { return t != null ? t.size : 0; }
	public static int col(Node t) { return t != null ? t.col : -1; }
	public static int lcol(Node t) { return t != null ? t.lcol : -1; }
	public static int rcol(Node t) { return t != null ? t.rcol : -1; }
	public static int lrun(Node t) { return t != null ? t.lrun : 0; }
	public static int rrun(Node t) { return t != null ? t.rrun : 0; }

	public static void update(Node t) {
		t.size = 1 + size(t.left) + size(t.right);
		t.lcol = t.left != null ? t.left.lcol : t.col;
		t.lrun = lrun(t.left);
		t.rcol = t.right != null ? t.right.rcol : t.col;
		t.rrun = rrun(t.right);
		if (t.lrun == size(t.left) && t.col == t.lcol) {
			t.lrun++;
			if (t.lcol == lcol(t.right)) t.lrun += lrun(t.right);
		}
		if(t.rrun == size(t.right) && t.col == t.rcol) {
			t.rrun++;
			if(t.rcol == rcol(t.left)) t.rrun += rrun(t.left);
		}
	}

	public static Node merge(Node left, Node right) { // merges two treaps (order is important)
		if (left == null || right == null) return left != null ? left : right;
		if (left.prio < right.prio) {
			left.right = merge(left.right, right);
			update(left);
			return left;
		} else {
			right.left = merge(left, right.left);
			update(right);
			return right;
		}
	}

	public static Node[] split_size(Node t, int num) {
		Node[] res = new Node[2];
		if (t == null) return res;
		if (1 + size(t.left) <= num) {
			res = split_size(t.right, num - 1 - size(t.left));
			t.right = res[0];
			update(t);
			res[0] = t;
			return res;
		} else {
			res = split_size(t.left, num);
			t.left = res[1];
			update(t);
			res[1] = t;
			return res;
		}
	}

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);//dont do this...
		int n = s.nextInt();
		int k = s.nextInt();
		int q = s.nextInt();
		
		Node root = null;
		for (int i = 0; i < n; i++) {
			int mi = s.nextInt();
			root = merge(root, new Node(mi));
		}
		for (int qq = 0; qq < q; qq++) {
			int p = s.nextInt();
			int mx = s.nextInt();
			Node[] todo = split_size(root, p);
			Node l = todo[0];
			Node r = todo[1];
			Node m = new Node(mx);

			if (col(m) == lcol(r)) {
				Node[] tmp = split_size(r, lrun(r));
				r = tmp[1];
				m = merge(m, tmp[0]);
			}
			if (col(m) == rcol(l)) {
				Node[] tmp = split_size(l, size(l)-rrun(l));
				l = tmp[0];
				m = merge(tmp[1], m);
			}

			if (size(m) < k) {
				root = merge(l, merge(m, r));
				System.out.println(size(root));
				continue;
			}

			// merge same in the middle
			while (rcol(l) == lcol(r) && rrun(l) + lrun(r) >= k) {
				l = split_size(l, size(l) - rrun(l))[0];
				r = split_size(r, lrun(r))[1];
			}

			root = merge(l, r);
			System.out.println(size(root));
		}
		s.close();
	}

}