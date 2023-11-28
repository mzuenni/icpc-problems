#include "validate.h"

int main(int argc, char **argv) {
	OutputValidator::init(argc, argv);					// initialize streams, rng and parse arguments
	using namespace OutputValidator;

	Integer n = testIn.integer();
	Integer w = testIn.integer();
	auto ws = testIn.integers(n);
	std::sort(ws.begin(), ws.end());
	ws.push_back(LARGE);

	auto check = [&](std::vector<std::vector<Integer>> wall, std::string_view sol, Verdict v){
		for (auto& row : wall) {
			Integer sum = 0;
			for (Integer& brick : row) {
				if (*std::lower_bound(ws.begin(), ws.end(), brick) != brick) {
					juryOut << sol << " solution contains invalid brick: " << brick << v;
				}
				brick += sum;
				sum = brick;
			}
			if (sum != w) {
				juryOut << sol << " solution has invalid row length: " << sum << v;
			}
			row.pop_back();
		}
		Integer a = 0;
		Integer b = 0;
		while(a < wall[0].size() && b < wall[1].size()) {
			if(wall[0][a] < wall[1][b])
				a++;
			else if(wall[0][a] > wall[1][b])
				b++;
			else
				juryOut << sol << " solution is unstable at x=" << wall[0][a] << v;
		}
	};

	auto jury = juryAns.string(std::regex("(impossible|possible)", std::regex::icase));
	auto team = teamAns.string(std::regex("(impossible|possible)", std::regex::icase));
	if (caseSensitive) {
		if(jury != "possible" && jury != "impossible") juryOut << "wrong case" << FAIL;
		if(team != "possible" && team != "impossible") juryOut << "wrong case" << WA;
	}
	toLower(jury);
	toLower(team);
	teamAns.newline();

	if(jury == "possible") {
		Integer rows = 2; //juryAns.integer(1, 11);
		std::vector<std::vector<Integer>> wall(rows);
		for (auto& row : wall) {
			Integer k = juryAns.integer(1, w+1);
			row = juryAns.integers(1, w+1, k);
		}
		check(wall, "jury", FAIL);
	}
	if(team == "possible") {
		Integer rows = 2; //teamAns.integer(1, 11);
		std::vector<std::vector<Integer>> wall(rows);
		for (auto& row : wall) {
			Integer k = teamAns.integer(1, w+1);
			teamAns.newline();
			row = teamAns.integers(1, w+1, k);
			teamAns.newline();
		}
		check(wall, "team", WA);
	}

	if(jury == "possible" && team == "impossible") juryOut << "team found no solution but jury did" << WA;
	if(team == "possible" && jury == "impossible") juryOut << "jury found no solution but team did" << FAIL;

	teamAns.eof();
	return AC;
}
