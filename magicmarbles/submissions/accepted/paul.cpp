#include <bits/stdc++.h>
using namespace std;

typedef struct item * pitem;
struct item {
    int prio, color, count, sum;
    pitem l, r;
	item(int color, int count): prio(rand()), color(color), count(count), sum(count), l(0), r(0) {}
};

int size(pitem t) { return t ? t->sum : 0; }

void update(pitem t) {
	if (t) t->sum = size(t->l) + size(t->r) + t->count;
}

pitem first(pitem t) {
	return t && t->l ? first(t->l) : t;
}

pitem last(pitem t) {
	return t && t->r ? last(t->r) : t;
}

void merge(pitem &t, pitem l, pitem r) {
    if (!l || !r) {
		t = l ? l : r;
	} else if (l->prio > r->prio) {
        merge(l->r, l->r, r), t = l;
	} else {
        merge(r->l, l, r->l), t = r;
	}
	update(t);
}

void split(pitem t, pitem &l, pitem &r, int idx) {
    if (!t) { l = r = 0; return; }
    if (idx <= size(t->l)) {
		split(t->l, l, t->l, idx), r = t;
	} else if (idx >= size(t->l) + t->count) {
		split(t->r, t->r, r, idx - size(t->l) - t->count), l = t;
	} else {
		int part = idx - size(t->l);
		pitem s = new item(t->color, part);
		t->count -= part;
		merge(t->l, t->l, s);
		split(t->l, l, t->l, idx), r = t;
	}
    update(l), update(r);
}

int k;

void insert(pitem &t, int idx, int color) {
	if (!t) { t = new item(color, 1); return; }
	pitem l, r;
	split(t, l, r, idx);

	pitem s = new item(color, 1);

	pitem a = last(l), b = first(r);
	if (a && a->color == color) {
		split(l, l, a, size(l) - a->count);
		s->count += a->count;
	}
	if (b && b->color == color) {
		split(r, b, r, b->count);
		s->count += b->count;
	}
	update(s);

	if (s->count < k) {
		merge(r, s, r);
		merge(t, l, r);
		return;
	}
	
	while (l && r) {
		a = last(l), b = first(r);
		split(l, l, a, size(l) - a->count);
		split(r, b, r, b->count);
		if (a->color == b->color) {
			b->count += a->count, a = 0;
			update(b);
		}

		if (b->count < k) {
			merge(l, l, a);
			merge(r, b, r);
			merge(t, l, r);
			return;
		}
	}

	t = l ? l : r; return;
}

int main() {
	int n, q;
	cin >> n >> k >> q;

	pitem root = 0;
	for (int i = 0; i < n; i++) {
		int color; cin >> color;
		insert(root, i, color);
	}

	while (q--) {
		int idx, color;
		cin >> idx >> color;
		insert(root, idx, color);
		cout << size(root) << endl;
	}
}
