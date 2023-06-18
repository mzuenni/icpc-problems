#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
	int w, h;
	cin >> w >> h;
	int heights[w];
	ll empty = 0;
	for(int i = 0; i< w; i++){
		cin >> heights[i];
		empty += h- heights[i];
	}
	if(empty %2) cout << "impossible" << endl;
	else cout << "possible" << endl;
}
