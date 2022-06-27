#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

int main()
{
	int h,w; cin >> h >> w;
	vector<vector<bitset<5>>> field(min(h,w)+1, vector<bitset<5>>(max(h,w),0));
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			int a = i; int b = j;
			if (h > w) swap(a,b);
			char c; cin >> c;
			if (c == 'W') field[a][b] = 1;
			else if (c == 'A') field[a][b] = 2;
			else if (c == 'L') field[a][b] = 4;
			else if (c == 'D') field[a][b] = 8;
			else if (c == 'O') field[a][b] = 16;
		}
	}
	if (h > w) swap(h,w);
	vector<vector<bitset<5>>> f = field;
	bool found = false;
	int best = 1e6;
	for (int i = 1; i <= h; ++i)
	{
		for (int j = 0; j + i <= h; ++j)
		{
			vector<int> cnt(5,0);
			int r = 0;
			int l = 0;
			while (r < w)
			{
				while (!found && r < w)
				{
					for (int t = 0; t < 5; ++t) if (f[j][r][t]) cnt[t]++;
					found = cnt[0] && cnt[1] && cnt[2] && cnt[3] && cnt[4];
					r++;
				}

				while (found)
				{
					best = min(best,(r-l)*i);
					for (int t = 0; t < 5; ++t) if (f[j][l][t]) cnt[t]--;
					found = cnt[0] && cnt[1] && cnt[2] && cnt[3] && cnt[4];
					l++;
				}
			}
			for (int k = 0; k < w; ++k) f[j][k] |= field[j+i][k];
		}
	}
	if (best == 1e6) cout << "impossible" << endl;
	else cout << best << endl;
}
