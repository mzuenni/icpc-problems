#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
	ll w, h;
	cin >> w >> h;
	ll heights[w];
	for(int i = 0; i< w; i++){
		cin >> heights[i];
		if(heights[i]> h){
			cout << "impossible" << endl;
			return 0;
		}
	}
	bool hor = false;
	for(int i = 0; i< w; i++){
		if((h-heights[i])%2){
			if(hor == true){//maybe possible, continue
				hor = false;
			}
			else{
				hor = true;
			}
		}
		else{
			if(hor == true){
				cout << "impossible" << endl;
				return 0;
			}
		}
	}
	if(hor == true){
		cout << "impossible" << endl;
	}
	else{
		cout << "possible" << endl;
	}
}
