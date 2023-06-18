#include<bits/stdc++.h>
using namespace std;

string seq;
vector<int> divisions;

int solve(){
    cin >> seq;
    int open = 0;
    int len = 0;
    int last = 0;
    for(int i=0; i<seq.size(); i++){
        if(seq[i] == '(') open++;
        else open--;
        if(len != 0 && seq[i] != seq[i % len]) return last;
        if(open == 0){
            if(len == 0) len = i + 1;
            else if(i - last + 1 != len) return last;
            last = i + 1;
        } 
    }
    return -1;
}

int main(){
    int division = solve();
    if(division < 0) cout << "no" << endl;
    else{
        for(int i=division; i < seq.size(); i++) cout << seq[i];
        for(int i=0; i < division; i++) cout << seq[i];
        cout << endl;
    }
}
