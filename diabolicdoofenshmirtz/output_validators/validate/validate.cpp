#include "validate.h"
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

constexpr Integer maxQueryValue = 1'000'000'000'000'000'000;
constexpr Integer maxModValue = 1'000'000'000'000;
const std::regex TYPE_REGEX("[?!]", std::regex_constants::optimize);

constexpr Integer queryLimit(Integer mod) {
	//return log2(mod)+1;
	return 42;
}

int main(int argc, char **argv) {
	using namespace Interactor;
	Interactor::init(argc, argv);

	Integer mod = testIn.integer(1, maxModValue+1);
	vector<Integer> other;
	if (mod - 1 >= 1) other.push_back(mod - 1);
	for (Integer i = 2; i*i <= mod; i++) {
		if (mod % i == 0) {
			other.push_back(mod / i);
			break;
		}
	}
	if (2*mod <= maxModValue) other.push_back(2*mod);
	if (mod + 1 <= maxModValue) other.push_back(mod+1);

	Integer lastValue = -1;
	for (Integer query = 1;; query++) {
		string type = fromTeam.string(TYPE_REGEX);

		if (type == "!") {
			if (!fromTeam.expectInt(mod)) juryOut << "Wrong answer: wrong lap length" << WA;
			if (!other.empty()) juryOut << "Answer is not unique: " << join(all(other)) << WA;
			if (queryLimit(mod) < query) juryOut << "Wrong answer: Too many guesses: " << query << " (which is " << query - queryLimit(mod) << " over)." << WA;
			fromTeam.eof();
			juryOut << "Queries used: " << query << AC;
		} else if (type == "?") {
			Integer value = fromTeam.integer(lastValue + 1, maxQueryValue + 1);
			lastValue = value;
			Integer response = value % mod;
			toTeam << response << endl;
			for (Integer i = 0; i < sz(other);) {
				if (value % other[i] != response) {
					swap(other[i], other.back());
					other.pop_back();
				} else {
					i++;
				}
			}
		} else {
			juryOut << "WHAT?!" << FAIL;
		}
	}
}

