#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main() {
	int n; double target; cin >> n >> target;
	vector<pair<double,double>> chems;
	double w = 0, a = 0;
	for (int i = 0; i < n; ++i) {
		double x,y; cin >> x >> y;
		chems.push_back({y,x});
		w += x * y;
		a += x;
	}
	sort(chems.begin(),chems.end());
	double p = w/a;
	int idx = p > target ? chems.size()-1 : 0;
	int dx = p > target ? -1 : 1;
	while (abs(p - target) > 1e-5) {
		double nxtW = w - chems[idx].first * chems[idx].second;
		double nxtA = a - chems[idx].second;
		double nxtP = nxtW / nxtA;
		if ((p > target && nxtP > target) || (p < target && nxtP < target)) {
			p = nxtP;
			w = nxtW;
			a = nxtA;
			idx += dx;
		}
		else {
			a = nxtA + (nxtW - target * nxtA) / (target - chems[idx].first);
			break;
		}
	}
	cout << a << endl;
}
