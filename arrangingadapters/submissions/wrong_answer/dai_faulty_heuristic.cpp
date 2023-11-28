#include <bits/stdc++.h>
using namespace std;

int n, w[200010], cnt[3], ans = 0;
long long s, sum = 0;

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 0; i < n; i++) scanf("%d", &w[i]);
    sort(w, w + n);
    for (int i = 0; i < 2 && s > 0 && n > 0; i++) ans++, n--, s--;
    s *= 3;
    for (int i = 0; i < n; i++)
    {
        sum += w[i];
        if (w[i] % 3 == 1)
        {
            if(cnt[1]) cnt[1]--, sum--;
            else if(cnt[2]) cnt[2]--, sum--;
            else cnt[1]++, sum += 2;
        }
        else if (w[i] % 3 == 2)
        {
            if(cnt[1]) cnt[1]--, sum -= 2;
            else cnt[2]++, sum++;
        }
        if (sum <= s) ans++;
        else break;
    }
    printf("%d\n", ans);
}
