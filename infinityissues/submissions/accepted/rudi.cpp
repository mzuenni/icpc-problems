#include<bits/stdc++.h>
using namespace std;

int n, w, margin;
string word;

void print(string & word){

    int used = 0;
    while(used < word.size()){
        
        int next = min((int) word.size() - used, margin);
        cout << word.substr(used, next);
        margin -= next;
        used += next;
        if(margin == 0){
            cout << endl;
            margin = w;
        }
    }
}

int main(){
    cin >> n >> w;
    margin = w;
    string space = " ";
    for(int i=0; i<n; i++){
        cin >> word;
        print(word);
        if(i < n - 1) print(space);
    }
}