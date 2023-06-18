#include "validate.h"

bool isValid(const std::string& s) {
	Integer cur = 0;
	for (char c : s) {
		if (c == '(') cur++;
		else if (c == ')') cur--;
		else return false;
		if (cur < 0) return false;
	}
	return cur == 0;
}

std::vector<Integer> kmpPreprocessing(const std::string& sub) {
	std::vector<Integer> b(sub.size() + 1);
	b[0] = -1;
	for (Integer i = 0, j = -1; i < sub.size();) {
		while (j >= 0 && sub[i] != sub[j]) j = b[j];
		b[++i] = ++j;
	}
	return b;
}

bool kmpSearch(const std::string& s, const std::string& sub) {
	std::vector<Integer> pre = kmpPreprocessing(sub);
	for (Integer i = 0, j = 0; i < s.size();) {
		while (j >= 0 && s[i] != sub[j]) j = pre[j];
		i++; j++;
		if (j == sub.size()) return true;
	}
	return false;
}


int main(int argc, char *argv[]) {
	OutputValidator::init(argc, argv);
	using namespace OutputValidator;

	std::string s = testIn.string();
	const Integer n = s.size();

	if (stringEqual(juryAns.string(), "no")) {
		teamAns.expectString("no");
		teamAns.newline();
		teamAns.eof();
		juryOut << "OK no" << AC;
	} else {
		std::string ans = teamAns.string(n, n+1);
		teamAns.newline();
		teamAns.eof();
		if (!isValid(ans)) juryOut << "solution is not a valid bracket sequence!" << WA;
		if (!kmpSearch(s+s, ans)) juryOut << "solution is not formed by rotation!" << WA;
		if (ans == s) juryOut << "solution is not rotated!" << WA;
		juryOut << "OK possible" << AC;
	}
}
