#include "bits/stdc++.h"
using namespace std;

const long long M  = 1e9 + 7;
int n, q;

long long modMult(long long a, long long b){
    return (a * b) % M;
}

long long modSum(long long a, long long b){
    return (a + b) % M;
}

long long modPow(long long a, long long b) {
	long long res = 1;
	while (b > 0) {
		if (b % 2) res = modMult(res, a);
		a = modMult(a, a);
		b /= 2;
	}
	return res;
}

long long modInv(long long a){
    return modPow(a, M - 2);
}

long long modDiv(long long a, long long b){
    return modMult(a, modInv(b));
}

struct SegNode{
    int from, to;
    long long value;
    SegNode * leftChild;
    SegNode * rightChild;

    SegNode(int from, int to): from(from), to(to), value(0){}

    bool is_leaf(){
        return from == to;
    }

    int mid(){
        return this ->from + (this -> to - this -> from ) / 2;
    }

    void update(int from, int to, long long delta){
        if(this->from > to || this->to < from) return;
        if(from <= this->from && this->to <= to){
            value = modSum(value, delta);
            return;
        }
        this->leftChild->update(from, to, delta);
        this->rightChild->update(from, to, delta);
    }

    long long query(int pos){
        assert(from <= pos && pos <= to);
        if(this->is_leaf()) return value;
        if(pos <= this->mid()) return modSum(value, this->leftChild->query(pos));
        else return modSum(value, this->rightChild->query(pos));
    }
};

long long powers_of_p[1000000];
long long inv_powers_of_p[1000000];

long long getBrightnessFromLeft(int pos, SegNode * tree){
    long long value = tree->query(pos);
    return modMult(value, powers_of_p[pos]);
}

void addBrightness(int pos, long long brightnss, SegNode * tree, bool exclude_start){
    // at i = pos, we want to have an effective delta of brightness.
    // so we need to add (p^pos)^(-1) * brightness
    if(pos == n && exclude_start) return;
    long long delta = modMult(brightnss, inv_powers_of_p[pos]);
    tree->update(exclude_start ? pos + 1 : pos, n, delta);

}

int mirror_pos(int pos){
    return n - pos + 1;
}

SegNode * build_segTree(int from, int to){
    SegNode * node = new SegNode(from, to);
    if(!node -> is_leaf()){
        node -> leftChild = build_segTree(from, node->mid());
        node -> rightChild = build_segTree(node->mid() + 1, to);
    }
    return node;
}

void addToTree(int pos, long long brightness){

}

int main(){
    string str_in;
    cin >> n >> q >> str_in;

    long long shifted = stol(str_in.substr(2)); // e.g. 0.33 -> 33
    long long modP = modSum(1, M - modDiv(shifted, modPow(10, str_in.size() - 2)));

    long long invP = modInv(modP);

    assert(modMult(modP, invP) == 1);
    powers_of_p[0] = 1;
    inv_powers_of_p[0] = 1;
    for(int i=1; i<1000000; i++){
        powers_of_p[i]  = modMult(powers_of_p[i-1], modP);
        inv_powers_of_p[i] = modMult(inv_powers_of_p[i-1], invP);
        assert(modMult(powers_of_p[i], inv_powers_of_p[i]) == 1);
    }

    SegNode * normal = build_segTree(1, n);
    SegNode * mirrored = build_segTree(1, n);

    for(int i=0; i<q; i++){
        char c;
        int pos;
        cin >> c;
        if(c == '+' || c == '-'){
            long long b;
            cin >> b >> pos;

            addBrightness(pos, c == '+' ? b : modMult(b, M - 1), normal, false);
            addBrightness(mirror_pos(pos), c == '+' ? b : modMult(b, M - 1), mirrored, true);
        } else{
            int pos;
            cin >> pos;

            long long brightness_from_left = getBrightnessFromLeft(pos, normal);
            long long brightness_from_right = getBrightnessFromLeft(mirror_pos(pos), mirrored);

            cout << modSum(brightness_from_left, brightness_from_right) << endl;
        }
    }
}
