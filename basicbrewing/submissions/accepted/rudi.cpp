#include<bits/stdc++.h>
using namespace std;

vector<pair<double, double>> too_few;
vector<pair<double, double>> too_much;
const double eps = 1e-10;

int main(){
    int n;
    double p;
    cin >> n >> p;
    double erg = 0;
    for(int i=0; i<n; i++){
        int l;
        double q;
        cin >> l >> q;
        if(abs(q - p) < eps){
            erg += l;
            continue;
        }
        if(q < p) too_few.push_back({q, l});
        else too_much.push_back({-q, l});
    }

    sort(too_few.begin(), too_few.end());
    sort(too_much.begin(), too_much.end());

    while(!too_few.empty() && !too_much.empty()){
        double p1 = -too_much.back().first;
        double p0 = too_few.back().first;
        double v0 = too_few.back().second;
        double v1 = too_much.back().second;
        double q = (p - p1) / (p0 - p1);
        if(abs(v0 / (v0 + v1) - q) < eps){ // we empty both
            too_few.pop_back();
            too_much.pop_back();
            erg += v0 + v1;
        } else if(v0 / (v0 + v1) < q){ // we empty 0
            double partial = (1-q) / q * v0;
            erg += v0 + partial;
            too_much.back().second -= partial;
            too_few.pop_back();
        } else{ // we empty 1
            double partial = q / (1-q) * v1;
            erg += v1 + partial;
            too_few.back().second -= partial;
            too_much.pop_back();
        }
    }
    cout << fixed << setprecision(6) << erg << endl;
}   