#include <algorithm>
#include <array>
#include <bitset>
#include <cctype>
#include <cmath>
#include <charconv>
#include <complex>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <string>
#include <string_view>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

constexpr int AC = 42;
constexpr int WA = 43;

std::vector<std::string> readAns(std::istream& in) {
	std::vector<std::string> res;
	std::string line;
	while (std::getline(in, line)) {
		while(!line.empty() && line.back() == ' ') line.pop_back();//trim spaces at end of line
		res.push_back(line);
	}
	while (!res.empty() && res.back().empty()) res.pop_back();//trim newlines at end of file
	return res;
}

int main(int argc, char** argv) {
	std::ofstream juryOut{std::filesystem::path(argv[3]) / "judgemessage.txt"};
	std::ifstream juryAns{std::filesystem::path(argv[2])};
	std::istream& teamAns = std::cin;

	auto jury = readAns(juryAns);
	auto team = readAns(teamAns);
	if (jury != team) {
		if (jury.size() != team.size()) {
			juryOut << "Team printed: " << team.size() << " lines, Jury printed: " << jury.size() << " lines." << std::endl;
		} else {
			for (int i = 0; i < jury.size(); i++) {
				if (jury[i] != team[i]) {
					juryOut << "Line " << i+1 << " differs." << std::endl;
					break;
				}
			}
		}
		return WA;
	} else {
		return AC;
	}
} 
