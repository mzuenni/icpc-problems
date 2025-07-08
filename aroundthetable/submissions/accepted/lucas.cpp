#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
	ll l, r;
	cin >> l >> r;
	ll n = l+r;
	ll ans = 4;
	if(2*r == n) ans = 3;
	if(2*r+1 == n) ans = 2;
	if(2*r+2 == n) ans = 3;
	ans = ans * n / 2;
	cout << ans << "\n";
}