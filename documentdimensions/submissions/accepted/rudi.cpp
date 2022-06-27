#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> pref;

int main(){
    cin >> n;
    pref.push_back(0);
    for(int i=1; i<=n; i++){
        string s;
        cin >> s;
        pref.push_back(s.size());
    }

    int maxlen = -1;
    for(int i=1; i<=n; i++) maxlen = max(maxlen, pref[i]);
    for(int i=1; i<=n; i++) pref[i] += pref[i-1];
    pref.push_back(5000000);

    int output = 5000000;
    for(int linewidth = maxlen; linewidth <= pref[n]; linewidth++){
        int nlines = 0;
        int i = 1;
        while(i <= n && linewidth + nlines <= output + 1){
            nlines++;
            int hi = n+1;
            int lo = i;
            while(hi - lo > 1){
                int mid = (hi + lo) / 2;
                int len = pref[mid] - pref[i-1] + (mid - i);
                if(len <= linewidth) lo = mid;
                else hi = mid;
            }
            i = lo+1;
        }
        output = min(output, linewidth + nlines);
    }
    cout << output << endl;
 
}