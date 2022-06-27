#include "validate.h"

int main(int argc, char** argv) {
    using namespace Generator;
    Generator::init(argc, argv);

    Integer n = arguments["--n"].asInteger(Random::integer(1, 100001));

    std::string s = "";
    std::string chars = "cdhs";
    for(Integer i = 0; i < (n + 3) / 4; i++) {
        Random::shuffle(chars.begin(), chars.end());
        s += chars;
    }
    while(s.size() > n) s.pop_back();

    testOut << s << std::endl;
}
