import java.util.*;

public class jannik_avl {

	static int run;

	static interface Node {
		public int size();
		public int height();
	}
	static class Leaf implements Node {
		public int ch;
		public int count;
		public int size() { return count; }
		public int height() { return 1; }
		public Leaf(int cc, int cnt) {
			ch = cc;
			count = cnt;
		}
		public Leaf(int cc) {
			this(cc,1);
		}
	}
	static class Inner implements Node {
		public final Node left, right;
		public final int sz, h;
		public int size() { return sz; }
		public int height() { return h; }
		public Inner(Node l, Node r) {
			left = l;
			right = r;
			sz = l.size() + r.size();
			h = 1 + Math.max(l.height(), r.height());
		}
	}

	static Inner rotateLeft(Inner n) {
		Inner r = (Inner) (n.right);
		return new Inner(new Inner (n.left, r.left), r.right);
	}
	static Inner rotateRight(Inner n) {
		Inner l = (Inner) (n.left);
		return new Inner(l.left, new Inner(l.right, n.right));
	}

	static int balanceFactor(Inner l) {
		return l.left.height() - l.right.height();
	}
	static int balanceFactor(Node n) {
		if (n instanceof Inner) return balanceFactor((Inner) n);
		return 0;
	}

	static Node balance(Node n) {
		if (!(n instanceof Inner)) return n;
		Inner i = (Inner) n;
		final int bf = balanceFactor(i);
		if (bf > 1) {
			if (balanceFactor(i.left) < 0) {
				Inner lf = (Inner) (i.left);
				Node rf = i.right;
				return rotateRight(new Inner(rotateLeft(lf), rf));
			}
			return rotateRight(i);
		} else if(bf < -1) {
			if (balanceFactor(i.right) > 0) {
				Inner rf = (Inner) (i.right);
				Node lf = i.left;
				return rotateLeft(new Inner(lf, rotateRight(rf)));
			}
			return rotateLeft(i);
		} else
			return n;
	}

	static Leaf getMin(Node n) {
		if (n instanceof Inner) return getMin(((Inner) n).left);
		else return (Leaf) n;
	}
	static Leaf getMax(Node n) {
		if (n instanceof Inner) return getMax(((Inner) n).right);
		else return (Leaf) n;
	}
	static Node updateMin(Node n) {
		if (n instanceof Inner) {
			Inner l = (Inner) n;
			return new Inner(updateMin(l.left), l.right);
		}
		return n;
	}

	static Node eraseMin(Node n) {
		if (n instanceof Inner) {
			Inner l = (Inner) n;
			Node t = eraseMin(l.left);
			if (t != null)
				return balance(new Inner(t, l.right));
			else
				return l.right;
		}
		return null;
	}
	static Node eraseMax(Node n) {
		if (n instanceof Inner) {
			Inner l = (Inner) n;
			Node t = eraseMax(l.right);
			if (t != null)
				return balance(new Inner(l.left, t));
			else
				return l.left;
		}
		return null;
	}
	static Node rm(Node n) {
		if (n == null) return null;
		if (n instanceof Leaf) {
			Leaf l = (Leaf) n;
			if (l.count >= run)
				l = null;
			return l;
		}
		Inner l = (Inner) n;

		while (true) {
			Leaf a = getMin(l.right), b = getMax(l.left);
			if (a.ch == b.ch) {
				a.count += b.count;
				Node lf = eraseMax(l.left), ri = l.right;
				if (a.count >= run) {
					ri = eraseMin(ri);
					if (lf == null && ri == null) {
						return null;
					} else if (ri == null) {
						return balance(lf);
					}
				} else {
					ri = updateMin(ri);
				}
				if (lf == null) {
					return balance(ri);
				}
				l = new Inner(lf, ri);
			} else
				return l;
		}
	}

	static Node insert(Node n, int i, int c) { // insert after i
		if (n == null) return new Leaf(c);
		if (n instanceof Leaf) {
			Leaf l = (Leaf) n;
			if (l.ch == c) {
				l.count++;
				if (l.count >= run)
					l = null;
				return l;
			} else {
				if (i < 0) return new Inner(new Leaf(c), l);
				else if (i + 1 >= l.count) return new Inner(l, new Leaf(c));
				else {
					Leaf fst = new Leaf(l.ch, i+1);
					Leaf endd = new Leaf(l.ch, l.count - (i+1));
					return new Inner(new Inner(fst, new Leaf(c)), endd);
				}
			}
		}
		Inner l = (Inner) n;
		int ls = l.left.size();
		if (i >= ls) {
			Node other = l.left;
			Node tmp = insert(l.right, i - ls, c);
			if (tmp == null) return balance(other);
			l = new Inner(other, tmp);
		} else {
			Node other = l.right;
			Node tmp = insert(l.left, i, c);
			if (tmp == null) return balance(other);
			l = new Inner(tmp, other);
		}
		return balance(rm(l));
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		Node tree = null;
		int n = in.nextInt();
		run = in.nextInt();
		int q = in.nextInt();

		for (int i = 0; i < n; i++) {
			int m = in.nextInt();
			tree = insert(tree, n, m);
		}

		while (q-- > 0) {
			int p = in.nextInt(), m = in.nextInt();
			tree = insert(tree, p-1, m);
			System.out.println(tree != null ? tree.size() : 0);
		}
	}
}
