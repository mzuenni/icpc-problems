#include <ext/rope>
#include "validate.h"

int main(int argc, char** argv) {
	using namespace Generator;
	Generator::init(argc, argv);

	Integer suits = 4;

	auto arg = arguments["--n"];
	std::string chars = "chds";
	Random::shuffle(chars.begin(), chars.end());

	std::vector<Integer> numbers;

	for(Integer i = 0; i < suits; i++) numbers.push_back(arg[i].asInteger());
	Integer moves = arg[suits].asInteger();

	__gnu_cxx::rope<char> s;
	for(Integer i = 0; i < suits; i++) {
		for(Integer j = 0; j < numbers[i]; j++) s.push_back(chars[i]);
	}

	__gnu_cxx::rope<char> tmp;

	Integer r;
	for(Integer i = 0; i < moves; i++) {
		r = Random::integer(0, s.size());
		tmp.push_back(s[r]);
		s.erase(r, 1);
		r = Random::integer(0, s.size());
		s.insert(s.mutable_begin() + r, tmp);
		tmp.pop_back();
	}

	std::string res = "";
	for(char x : s) res += x;
	testOut << res << std::endl;
}
