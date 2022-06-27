#include <iostream>
#include <cassert>

using namespace std;

int run;

struct Node {
	virtual int size() const = 0;
	virtual int height() const = 0;
	virtual ~Node() = default;
};
struct Leaf : public Node {
	pair<int, int> c;
	int size() const override { return c.second; }
	int height() const override { return 1; }
	Leaf(int cc, int cnt) : c(cc,cnt) {}
	Leaf(int cc) : Leaf(cc,1) {}
};
struct Inner : public Node {
	Node* const left, * const right;
	const int sz, h;
	int size() const override { return sz; }
	int height() const override { return h; }
	Inner(Node*l, Node*r)
		: left(l)
		, right(r)
		, sz(l->size() + r->size())
		, h(1 + max(l->height(), r->height())) {
	}
};

Inner* rotateLeft(Inner* n) {
	Inner* r = static_cast<Inner*>(n->right);
	auto tmp = r->right;
	return new (n) Inner(new (r) Inner (n->left, r->left), tmp);
}
Inner* rotateRight(Inner* n) {
	Inner* l = static_cast<Inner*>(n->left);
	auto tmp = l->left;
	return new (n) Inner(tmp, new (l) Inner(l->right, n->right));
}

int balanceFactor(const Inner& l) {
	return l.left->height() - l.right->height();
}
int balanceFactor(Node* n) {
	if (Inner* l = dynamic_cast<Inner*>(n)) return balanceFactor(*l);
	return 0;
}

Node* balance(Node* n) {
	Inner* i = dynamic_cast<Inner*>(n);
	if (!i) return n;
	const int bf = balanceFactor(*i);
	if (bf > 1) {
		if (balanceFactor(i->left) < 0) {
			auto lf = static_cast<Inner*>(i->left);
			auto rf = i->right;
			return rotateRight(new (i) Inner(rotateLeft(lf), rf));
		}
		return rotateRight(i);
	} else if(bf < -1) {
		if (balanceFactor(i->right) > 0) {
			auto rf = static_cast<Inner*>(i->right);
			auto lf = i->left;
			return rotateLeft(new (i) Inner(lf, rotateRight(rf)));
		}
		return rotateLeft(i);
	} else
		return n;
}

Leaf* getMin(Node* n) {
	if (Inner* l = dynamic_cast<Inner*>(n)) return getMin(l->left);
	else return static_cast<Leaf*>(n);
}
Leaf* getMax(Node* n) {
	if (Inner* l = dynamic_cast<Inner*>(n)) return getMax(l->right);
	else return static_cast<Leaf*>(n);
}
Node* updateMin(Node* n) {
	if (Inner* l = dynamic_cast<Inner*>(n))
		return new (l) Inner(updateMin(l->left), l->right);
	return n;
}

Node* eraseMin(Node* n) {
	if (Inner* l = dynamic_cast<Inner*>(n)) {
		if (auto t = eraseMin(l->left)) 
			return balance(new (l) Inner(t, l->right));
		else {
			auto other = l->right;
			delete l;
			return other;
		}
	}
	delete n;
	return nullptr;
}
Node* eraseMax(Node* n) {
	if (Inner* l = dynamic_cast<Inner*>(n)) {
		if (auto t = eraseMax(l->right))
			return balance(new (l) Inner(l->left, t));
		else {
			auto other = l->left;
			delete l;
			return other;
		}
	}
	delete n;
	return nullptr;
}
Node* rm(Node *n) {
	if (!n) return n;
	if (Leaf* l = dynamic_cast<Leaf*>(n)) {
		if(l->c.second >= run) {
			delete l;
			l = nullptr;
		}
		return l;
	}
	Inner* l = static_cast<Inner*>(n);

	while (true) {
		auto a = getMin(l->right), b = getMax(l->left);
		if (a->c.first == b->c.first) {
			a->c.second += b->c.second;
			auto lf = eraseMax(l->left), ri = l->right;
			if (a->c.second >= run) {
				ri = eraseMin(ri);
				if (!lf && !ri) {
					delete l;
					return nullptr;
				} else if (!ri) {
					return balance(lf);
				}
			} else {
				ri = updateMin(ri);
			}
			if (!lf) {
				delete l;
				return balance(ri);
			}
			lf = balance(lf), ri = balance(ri);
			const auto bf = lf->height() - ri->height();
			if (bf > 1) {
				Inner* lff = static_cast<Inner*>(lf);
				const auto tmp = lff->left;
				ri = rm(new (lff) Inner(lff->right, ri));
				if (!ri) return tmp;
				else l = new (l) Inner(tmp, ri);
			} else if (bf < -1) {
				Inner* rii = static_cast<Inner*>(ri);
				const auto tmp = rii->right;
				lf = rm(new (rii) Inner(lf, rii->left));
				if (!lf) return tmp;
				else l = new (l) Inner(lf, tmp);
			} else {
				l = new (l) Inner(lf, ri);
			}
		} else
			return balance(l);
	}
}

Node* insert(Node* n, int i, int c) { // insert after i
	if (!n) return new Leaf(c);
	if (Leaf* l = dynamic_cast<Leaf*>(n)) {
		if (l->c.first == c) {
			l->c.second++;
			if (l->c.second >= run) {
				delete l;
				l = nullptr;
			}
			return l;
		} else {
			if (i < 0) return new Inner(new Leaf(c), l);
			else if (i + 1 >= l->c.second) return new Inner(l, new Leaf(c));
			else {
				Leaf* fst = new Leaf(l->c.first, i+1);
				Leaf* endd = new (l) Leaf(l->c.first, l->c.second - (i+1));
				return new Inner(new Inner(fst, new Leaf(c)), endd);
			}
		}
	}
	Inner* l = static_cast<Inner*>(n);
	const auto ls = l->left->size();
	if (i >= ls) {
		auto other = l->left;
		auto tmp = insert(l->right, i - ls, c);
		if (!tmp) { delete l; return other; }
		l = new (l) Inner(other, tmp);
	} else {
		auto other = l->right;
		auto tmp = insert(l->left, i, c);
		if (!tmp) { delete l; return other; }
		l = new (l) Inner(tmp, other);
	}
	return balance(rm(l));
}

int main(){
	ios::sync_with_stdio(false), cin.tie(nullptr);
	Node* tree = nullptr;
	int n,q;
	cin >> n >> run >> q;

	for (int i = 0; i < n; i++) {
		int m; cin >> m;
		tree = insert(tree, n, m);
		assert(tree->size() == i+1);
	}

	while (q-- > 0) {
		int p, m;
		cin >> p >> m;
		tree = insert(tree, p-1, m);
		cout << (tree ? tree->size() : 0) << '\n';
	}
	return 0;
}
