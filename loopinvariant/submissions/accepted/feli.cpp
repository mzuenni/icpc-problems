#include<bits/stdc++.h>
using namespace std;
	int n;
	string s;
void swapsequences(int i ){
	for(int j = i+1; j< n; j++){
		cout << s[j];
	}
	for(int j = 0; j<= i; j++){
		cout << s[j];
	}
	cout << endl;
}

int main(){
	cin >> s;
	n = s.size();
	int open = 0;
	int close = 0;
	for(int i = 0; i< n; i++){
		if(s[i] == '(') open++;
		if(s[i] == ')') close++;
		if(open == close && open > 0 && close > 0 && i+1 < n){
			if(n%(i+1) != 0){
				swapsequences(i);
				return 0;
			}
			for(int j = 1; j< n/(i+1); j++){
				for(int k = 0; k < min(n-i, i+1); k++){
					if(s[k] != s[j*(i+1)+k]){
						swapsequences(i);
						return 0;
					}
				}
			}
			break;
		}
	}
	cout << "no" << endl;
}
