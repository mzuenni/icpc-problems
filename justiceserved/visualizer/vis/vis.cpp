#include "visualizer.h"
#include <map>
using namespace std;

int main(int argc, char **argv) {
	Visualizer::init(argc, argv);
	using namespace Visualizer;

	Integer n;
	testIn >> n;
	if (n < 1000) {
		map<Integer, vector<pair<Integer, Integer>>> in;
		Integer maxans = 0;
		for (Integer i = 0; i < n; i++) {
			Integer l, length, ans;
			testIn >> l >> length;
			testAns >> ans;
			in[ans].push_back({l+length, l});
			maxans = max(maxans, ans);
		}
		Integer y = 0;
		for (auto [ans, v] : in) {
			multimap<Integer, Integer> rows;
			for (auto [r, l] : v) {
				auto it = rows.lower_bound(l);
				if (it == rows.begin()) it = rows.insert({-1, rows.size()});
				else it--;
				Integer row = it->second;
				rows.erase(it);
				rows.insert({r, row});

				Rectangle tmp(l*maxans, (y+row)*n, (r-l)*maxans, 0.5*n);
				tmp.fill = Fill(ans % 2 == 0 ? RED : BLUE);
				image << tmp << std::endl;
			}
			/*Real step = 0.5 / starts.size();
			for (Integer i = 0; i < starts.size(); i++) {
				Rectangle tmp(starts[i], y+step*i, length, 0.5);
				tmp.fill = Fill(RED);
				image << tmp << std::endl;
			}*/
			y += rows.size() + 1;
		}
	}
}
