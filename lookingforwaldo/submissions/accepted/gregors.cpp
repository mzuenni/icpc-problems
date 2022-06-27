#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main()
{
	int h,w; cin >> h >> w;
	vector<vector<int>> field(min(h,w)+1, vector<int>(max(h,w),-1));
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
	vector<vector<set<int>>> s(h, vector<set<int>>(w));
	for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) 
		if (field[i][j] != -1) s[i][j].insert(field[i][j]);
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
					for (int k : s[j][r]) cnt[k]++;
					found = cnt[0] && cnt[1] && cnt[2] && cnt[3] && cnt[4];
					r++;
				}

				while (found && l < r)
				{
					best = min(best,(r-l)*i);
					for (int k : s[j][l]) cnt[k]--;
					found = cnt[0] && cnt[1] && cnt[2] && cnt[3] && cnt[4];
					l++;
				}
			}
			for (int k = 0; k < w; ++k) 
				if (field[j+i][k] != -1) 
					s[j][k].insert(field[j+i][k]);
		}
	}
	if (best == 1e6) cout << "impossible" << endl;
	else cout << best << endl;
}