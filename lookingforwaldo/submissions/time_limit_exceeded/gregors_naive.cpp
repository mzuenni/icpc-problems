#include <iostream>
#include <vector>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int h,w; cin >> h >> w;
	vector<vector<int>> field(min(h,w), vector<int>(max(h,w),5));
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			int a = i; int b = j;
			if (h > w) swap(a,b);
			char c; cin >> c;
			if (c == 'W') field[a][b] = 0;
			else if (c == 'A') field[a][b] = 1;
			else if (c == 'L') field[a][b] = 2;
			else if (c == 'D') field[a][b] = 3;
			else if (c == 'O') field[a][b] = 4;
		}
	}
	if (h > w) swap(h,w);
	bool found = false;
	int best = 1e6;
	for (int i = 1; i <= h; ++i)
	{
		for (int j = 0; j + i <= h; ++j)
		{
			vector<int> cnt(6,0);
			int r = 0;
			int l = 0;
			while (r < w)
			{
				while (!found && r < w)
				{
					for (int k = j; k < j+i; ++k) cnt[field[k][r]]++;
					found = cnt[0] && cnt[1] && cnt[2] && cnt[3] && cnt[4];
					r++;
				}

				while (found && l < r)
				{
					best = min(best,(r-l)*i);
					for (int k = j; k < j+i; ++k) cnt[field[k][l]]--;
					found = cnt[0] && cnt[1] && cnt[2] && cnt[3] && cnt[4];
					l++;
				}
			}
		}
	}
	if (best == 1e6) cout << "impossible" << endl;
	else cout << best << endl;
}