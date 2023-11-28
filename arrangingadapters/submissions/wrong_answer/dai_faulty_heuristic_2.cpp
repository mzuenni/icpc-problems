#include <bits/stdc++.h>
using namespace std;

int n, w[200010], pairing[3][3], ans = 0;
long long s, sum = 0, raw_length = 0;

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 0; i < n; i++) scanf("%d", &w[i]);
    sort(w, w + n);
    for (int i = 0; i < 2 && s > 0 && n > 0; i++) ans++, n--, s--;
    s *= 3;
    for (int i = 0; i < n; i++)
    {
        sum += w[i];
        raw_length += w[i] / 3;
        if (w[i] % 3 == 1)
        {
            if (pairing[2][2])
        	{
        		pairing[2][2]--;
        		pairing[1][2]++;
        		pairing[0][2]++;
        		sum -= 2;
        	}
        	else if (pairing[0][2])
        	{
        		pairing[0][2]--;
                pairing[1][2]++;
				sum--;
        	}
        	else if (pairing[0][1])
        	{
        		pairing[0][1]--;
        		pairing[1][1]++;
        		sum--;
        	}
        	else 
        	{
        		pairing[0][1]++;
        		sum += 2;
        	}
        }
        else if (w[i] % 3 == 2)
        {
            if (pairing[1][1])
        	{
        		pairing[1][1]--;
        		pairing[1][2]++;
        		pairing[0][1]++;
                sum++;
        	}
        	else if (pairing[0][1])
        	{
        		pairing[0][1]--;
				sum -= 2;
        	}
        	else if (pairing[0][2])
        	{
        		pairing[0][2]--;
        		pairing[2][2]++;
        		sum++;
        	}
        	else 
        	{
        		pairing[0][2]++;
        		sum++;
        	}
        }
        else pairing[0][0]++;
        //cout << sum << ' ' << pairing[0][0] << ' ' << pairing[0][1] << ' ' << pairing[0][2] << ' ' << pairing[1][1] << ' ' << pairing[1][2] << ' ' << pairing[2][2] << endl;
        //assert(sum == raw_length*3 + pairing[0][1]*3 + pairing[0][2]*3 + pairing[1][1]*3 + pairing[2][2]*6);
        if (sum <= s) ans++;
        else break;
    }
    printf("%d\n", ans);
}
