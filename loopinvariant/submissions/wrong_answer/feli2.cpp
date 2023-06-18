#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin >> s;
	int n = s.size();
	int open = 0;
	int close = 0;
	for(int i = 0; i< n; i++){
		if(s[i] == '(') open++;
		if(s[i] == ')') close++;
		if(open == close && open > 0 && close > 0 && i+1 < n){
			for(int k = 0; k < min(n-i, i+1); k++){
				if(s[k] != s[i+k+1]){
					for(int j = i+1; j< n; j++){
						cout << s[j];
					}
					for(int j = 0; j<= i; j++){
						cout << s[j];
					}
					cout << endl;
					return 0;
				}
			}
			break;
		}
	}
	cout << "no" << endl;
}
