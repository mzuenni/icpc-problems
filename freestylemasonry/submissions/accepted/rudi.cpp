#include<bits/stdc++.h>
using namespace std;

bool solve(int w, int h){
    int horizontals = 0;
    for(int i=0; i<w; i++){
        int y;
        cin >> y;
        if(horizontals + y > h) return false;
        bool even = (h - y - horizontals) % 2 == 0;
        if(horizontals == 0) horizontals = even ? 0 : 1;
        else horizontals = even ? horizontals - 1 : horizontals + 1;
    }
    return horizontals == 0;
}

int main(){
    int w, h;
    cin >> w >> h;
    if(solve(w, h)) cout << "possible" << endl;
    else cout << "impossible" << endl;

    
}