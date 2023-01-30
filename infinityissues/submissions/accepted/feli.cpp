#include<bits/stdc++.h>

using namespace std;

int main(){
	int n, w;
	cin >> n >> w;
	string t;
	for(int i = 0; i< n; i++){
		string word;
		cin >> word;
		t += word;
		t += " ";
	}
	for(int i = 0; i< t.size(); i+=w){
		cout << t.substr(i,w) << endl;
	}
}
