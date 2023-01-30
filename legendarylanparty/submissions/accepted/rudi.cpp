#include<bits/stdc++.h>
using namespace std;

const int MAXN = 500000;
pair<long long, long long> switches[MAXN];

int main(){
    int n, m;
    cin >> n >> m;

    for(int i=0; i<n; i++) cin >> switches[i].first >> switches[i].second;

    sort(switches, switches + n, [](const pair<long long, long long>& a, const pair<long long, long long>& b){
		return a.second*b.first < b.second*a.first;
	});

    long long res = 0;
    long long len = 1;
    for(int i=0; i<n; i++){
        res += len * switches[i].first;
        len += switches[i].second;
    }

    cout << res << endl;
}