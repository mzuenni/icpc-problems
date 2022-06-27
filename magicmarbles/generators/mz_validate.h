#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <memory>
#include <regex>
#include <random>
#include <vector>
#include <typeindex>

using integer_t = long long;
using uinteger_t = unsigned long long;
using real_t = long double;

constexpr int AC = 42;
constexpr int WA = 43;
constexpr int PE = WA;
constexpr int FAIL = 1;

constexpr int DEFAULT_PRECISION = 10;

template<typename T=real_t> auto DEFAULT_EPS = DEFAULT_EPS<T>; //only define this for floats...
template<> constexpr float DEFAULT_EPS<float> = 1e-6f;
template<> constexpr double DEFAULT_EPS<double> = 1e-6;
template<> constexpr long double DEFAULT_EPS<long double> = 1e-6l;

constexpr size_t TESTCASE_SIZE_LIMIT = 10*1024*1024;

const std::string JUDGE_MESSAGE = "judgemessage.txt";
const std::string JUDGE_ERROR = "judgeerror.txt";
const std::string DEFAULT_SEPERATOR = " ";

const std::regex INTEGER_REGEX("0|-?[1-9][0-9]*", std::regex_constants::optimize);
const std::regex REAL_REGEX("-?[0-9]+(\\.[0-9]+)?([eE][+-]?[0-9]+)?", std::regex_constants::optimize);

const std::string COMMAND_PREFIX = "--";
const std::string DEFAULT_COMMAND = "";

template<typename T>
constexpr T getX(const std::complex<T>& t) {
	return t.real();
}

template<typename L, typename R>
constexpr L getX(const std::pair<L, R>& t) {
	return t.first;
}

template<typename T>
constexpr T getY(const std::complex<T>& t) {
	return t.imag();
}

template<typename L, typename R>
constexpr R getY(const std::pair<L, R>& t) {
	return t.second;
}

template<typename T>
constexpr std::pair<T,T> convert(const std::complex<T>& t) {
	return {getX(t), getY(t)};
}

template<typename L, typename R>
constexpr std::complex<typename std::common_type<L, R>::type>
convert(const std::pair<L,R>& t) {
	return {getX(t), getY(t)};
}

template<typename L, typename R>
std::ostream& operator<<(std::ostream& str, const std::pair<L, R>& t) {
	str << t.first << DEFAULT_SEPERATOR << t.second;
	return str;
}

template<class T>
struct outListParams {
	using iterator = T;
	using value_type = typename std::iterator_traits<iterator>::value_type;
	using reference = value_type&;
	using const_reference = const value_type&;

private:
	//c++17 varian would be useful...
	std::vector<value_type> data;
public:
	iterator first, last;
	const std::string seperator;
	outListParams(iterator _first, iterator _last, const std::string& _seperator = DEFAULT_SEPERATOR) : 
			first(_first), last(_last), seperator(_seperator) {}

	outListParams(std::initializer_list<value_type> _data, const std::string& _seperator = DEFAULT_SEPERATOR) : 
			data(_data), first(data.begin()), last(data.end()), seperator(_seperator) {}

	iterator begin() const {return first;}
	iterator end() const {return last;}
};

template<class T>
outListParams<T>
outList(T first, T last, const std::string& seperator = DEFAULT_SEPERATOR) {
	return outListParams<T>(first, last, seperator);
}

template<class T>
outListParams<typename std::vector<T>::iterator>
outList(std::initializer_list<T> in, const std::string& seperator = DEFAULT_SEPERATOR) {
	return outListParams<typename std::vector<T>::iterator>(in, seperator);
}

template<class Iter>
std::ostream& operator<<(std::ostream& str, const outListParams<Iter>& t) {
	for (auto it = t.begin(); it != t.end(); it++) {
		str << *it;
		if (std::next(it) != t.end()) str << t.seperator;
	}
	return str;
}

template<class T>
struct inListParams {
	using iterator = T;
	using value_type = typename std::iterator_traits<iterator>::value_type;
	using reference = value_type&;
	using const_reference = const value_type&;

	iterator first, last;

	constexpr inListParams(iterator _first, iterator _last) : 
			first(_first), last(_last) {}

	constexpr iterator begin() const {return first;}
	constexpr iterator end() const {return last;}
};

template<class T>
inListParams<T>
constexpr inList(T first, T last) {
	return inListParams<T>(first, last);
}

template<class Iter>
std::istream& operator>>(std::istream& str, const inListParams<Iter>& t) {
	for (auto it = t.begin(); it != t.end(); it++) {
		str >> *it;
	}
	return str;
}

/* Test two numbers for equality, accounting for +/-INF, NaN and
 * precision. Float f2 is considered the reference value for relative
 * error.
 */
template<class real=real_t>
constexpr bool floatEqual(real f1, 
						  real f2, 
						  real float_abs_tol = DEFAULT_EPS<real>, 
						  real float_rel_tol = DEFAULT_EPS<real>) {
	/* Finite values are compared with some tolerance */
	if (std::isfinite(f1) && std::isfinite(f2)) {
		real absdiff = fabsl(f1-f2);
		real reldiff = fabsl((f1-f2)/f2);
		return !(absdiff > float_abs_tol && reldiff > float_rel_tol);
	}
	/* NaN is equal to NaN */
	if (std::isnan(f1) && std::isnan(f2)) return true;
	/* Infinite values are equal if their sign matches */
	if (std::isinf(f1) && std::isinf(f2)) {
		return std::signbit(f1) == std::signbit(f2);
	}
	/* Values in different classes are always different. */
	return false;
}

constexpr integer_t MZ_SEED = 3141592653589793238ll;
std::mt19937_64 mz_rng;

//random integer from [l, r);
template<typename T=integer_t, bool = std::is_integral<T>::value>
T randomInteger(T l = 0, T r = 2) {
	return std::uniform_int_distribution<T>(l, r - 1)(mz_rng);
}

//random real from [l, r);
template<typename T=real_t, bool = std::is_floating_point<T>::value>
real_t randomReal(T l = 0, T r = 1) {
	return std::uniform_real_distribution<T>(l, r)(mz_rng);
}

bool randomBit() {
	return std::uniform_int_distribution<>(0, 1)(mz_rng);
}

template<class RandomIt>
const typename std::iterator_traits<RandomIt>::value_type&
randomSelect(RandomIt first, RandomIt last) {
	return first[randomInteger<size_t>(0, last - first)];
}

void seedRandom(integer_t seed) {
	mz_rng.seed(seed);
}

template<class RandomIt>
void shuffle(RandomIt first, RandomIt last) {
	//std::shuffle(first, last, mz_rng);
	auto n = last - first;
	for (auto i = n-1; i > 0; --i) {
		std::swap(first[i], first[randomInteger<size_t>(0, i+1)]);
	}
}

template<typename T>
void shuffle(std::pair<T, T>& t) {
	if (randomBit()) std::swap(t.first, t.second);
}

template<typename C>
constexpr bool isPerm(C in, typename C::value_type offset = 0) {
	std::sort(in.begin(), in.end());
	for (auto x : in) {
		if (x != offset) return false;
		offset++;
	}
	return true;
}

namespace mzDetails {
	template<typename T>
	bool tryParse(const std::string& s, T& res, T(*f)(const std::string&, std::size_t*, int)) {
		try {
			res = f(s, nullptr, 0);
			return true;
		} catch(...) {
			return false;
		}
	}

	template<typename T>
	bool tryParse(const std::string& s, T& res, T(*f)(const std::string&, std::size_t*)) {
		try {
			res = f(s, nullptr);
			return true;
		} catch(...) {
			return false;
		}
	}
}

template<typename T>
bool parse(const std::string& s, T& res) = delete;

template<>
bool parse(const std::string& s, int& res) {
	return mzDetails::tryParse(s, res, std::stoi);
}

template<>
bool parse(const std::string& s, long& res) {
	return mzDetails::tryParse(s, res, std::stol);
}

template<>
bool parse(const std::string& s, long long& res) {
	return mzDetails::tryParse(s, res, std::stoll);
}

template<>
bool parse(const std::string& s, unsigned long& res) {
	return mzDetails::tryParse(s, res, std::stoul);
}

template<>
bool parse(const std::string& s, unsigned long long& res) {
	return mzDetails::tryParse(s, res, std::stoull);
}

template<>
bool parse(const std::string& s, float& res) {
	return mzDetails::tryParse(s, res, std::stof);
}

template<>
bool parse(const std::string& s, double& res) {
	return mzDetails::tryParse(s, res, std::stod);
}

template<>
bool parse(const std::string& s, long double& res) {
	return mzDetails::tryParse(s, res, std::stold);
}

constexpr bool isSpace(char c) {
	return (c == ' ') || 
		   (c == '\t') ||
		   (c == '\v') ||
		   (c == '\f');
}

constexpr bool isWhiteSpace(char c) {
	return isSpace(c) ||
		   (c == '\r') ||
		   (c == '\n');
}

constexpr char lowerCase(char c) {
	if (c >= 'A' && c <= 'Z') {
		c -= 'A';
		c += 'a';
	}
	return c;
}

std::string lowerCase(std::string s) {
	for (char& c : s) c = lowerCase(c);
	return s;
}

constexpr char upperCase(char c) {
	if (c >= 'a' && c <= 'z') {
		c -= 'a';
		c += 'A';
	}
	return c;
}

std::string upperCase(std::string s) {
	for (char& c : s) c = upperCase(c);
	return s;
}

struct OutStream : std::ostream {
private:
	std::unique_ptr<std::ostream> owning = nullptr;
	std::ostream* managed = nullptr;

public:
	OutStream() : std::ostream{nullptr} {}
	OutStream(const std::string& file) : 
			owning{new std::ofstream(file)}, 
			managed{owning.get()} {
		rdbuf(managed->rdbuf());
		*this << std::fixed << std::setprecision(DEFAULT_PRECISION);
	}
	OutStream(std::ostream& file) : 
			managed{std::addressof(file)} {
		rdbuf(managed->rdbuf());
		*this << std::fixed << std::setprecision(DEFAULT_PRECISION);
	}

	OutStream(OutStream&& other) :
			std::ostream{other.managed ? other.managed->rdbuf() : nullptr},
			owning{std::move(other.owning)},
			managed{other.managed} {
		other.managed = nullptr;
	}

	OutStream& operator=(OutStream&& other) {
		owning = std::move(other.owning);
		managed = std::move(other.managed);
		other.managed = nullptr;
		if (managed) {
			rdbuf(managed->rdbuf());
		} else {
			rdbuf(nullptr);
		}
		return *this;
	}
};

OutStream pout;
OutStream jout;
OutStream jerr;

struct NullStream : public std::ostream {
private:
	struct NullBuffer : public std::streambuf {
		std::array<char, 512> buffer;
		NullBuffer() {
			setp(buffer.begin(), buffer.end());
		}
	protected:
		virtual std::streambuf::int_type overflow(std::streambuf::int_type c) override {
			setp(buffer.begin(), buffer.end());
			return c;
		}
	};
	NullBuffer buffer;
public:
	NullStream() : std::ostream(&buffer) {}
};

NullStream nullStream;

struct ifTrue {
	const bool condition;
	constexpr ifTrue(bool _condition) : condition(_condition) {}
};

std::ostream& operator<<(std::ostream& str, const ifTrue& t) {
	if (t.condition) return str;
	else return nullStream;
}

struct close {
	const int verdict;
	constexpr close(int _verdict = FAIL) : verdict(_verdict) {}
};

std::ostream& operator<<(std::ostream& str, const close& t) {
	str << std::endl;
	if (std::type_index(typeid(str)) != std::type_index(typeid(NullStream))) {
		std::exit(t.verdict);
	}
	return str;
}

struct LineCountingStreamBuffer : public std::streambuf {
private:
	integer_t lineNumber = 1;
	std::streambuf* managed = nullptr;

public:
	LineCountingStreamBuffer() {}
	LineCountingStreamBuffer(std::streambuf* _managed) :
			managed(_managed) {
	}

	integer_t getLineNumber() {
		return lineNumber;
	}
	char myBuffer;
protected:
	virtual std::streambuf::int_type underflow() override {
		if (!managed) return traits_type::eof();
		return managed->sgetc();
	}

	virtual std::streambuf::int_type uflow() override {
		if (!managed) return traits_type::eof();
		int_type ch = managed->sbumpc();

		if (traits_type::eq_int_type(ch, traits_type::to_int_type('\n'))) {
			lineNumber++;
		}

		return ch;
	}

	std::streambuf::int_type pbackfail(std::streambuf::int_type ch) override {
		if (!managed) return traits_type::eof();

		if (traits_type::eq_int_type(ch, traits_type::to_int_type('\n'))) {
			--lineNumber;
		}

		if (ch != traits_type::eof()) {
			return managed->sputbackc(traits_type::to_char_type(ch));  
		} else {
			return managed->sungetc();
		}
	}
};

struct InStream : public std::istream {
private:
	std::unique_ptr<std::istream> owning = nullptr;
	std::istream* managed = nullptr;
	LineCountingStreamBuffer filter;
	int failVerdict = PE;
	bool strict;

public:
	InStream() : std::istream{nullptr} {}
	InStream(const std::string& file, int _failVerdict, bool _strict = false) : 
			owning{std::make_unique<std::ifstream>(file)}, 
			managed{owning.get()},
			filter(managed->rdbuf()),
			failVerdict(_failVerdict),
			strict(_strict) {
		rdbuf(&filter);
	}
	InStream(std::istream& file, int _failVerdict, bool _strict = false) : 
			managed{std::addressof(file)},
			filter(managed->rdbuf()),
			failVerdict(_failVerdict),
			strict(_strict) {
		rdbuf(&filter);
	}

	InStream(InStream&& other) :
			owning{std::move(other.owning)},
			managed{other.managed},
			filter{std::move(other.filter)},
			failVerdict(other.failVerdict),
			strict(other.strict) {
		other.managed = nullptr;
		rdbuf(&filter);
	}

	InStream& operator=(InStream&& other) {
		owning = std::move(other.owning);
		managed = std::move(other.managed);
		other.managed = nullptr;
		filter = std::move(other.filter);
		failVerdict = other.failVerdict;
		strict = other.strict;
		rdbuf(&filter);
		return *this;
	}

private:	
	struct lineReporter {
		const integer_t line;
		constexpr lineReporter(integer_t _line) : line(_line) {}
	};

	friend std::ostream& operator<<(std::ostream& str, const lineReporter& t) {
		str << " (in Line: " << t.line << ") ";
		return str;
	}

	lineReporter reportLine() {
		return lineReporter(this->lineNumber());
	}

	void reportFail() {
		jout << "input failed" << reportLine() << close(failVerdict);
	}

	void checkFail() {
		if (this->fail()) reportFail();
	}

	void isNotWhitespace() {
		if (strict) {
			auto c = this->peek();
			checkFail();
			if (isWhiteSpace(traits_type::to_char_type(c))) jout << "invalid whitespace found" << reportLine() << close(failVerdict);
		}
	}

	void strictModeWarning(const std::string& caller) {
		if (!strict) {
			jerr << "WARNING: \"" << caller << "\" called on non strict input stream (call ignored)" << std::endl;
		}
	}

public:
	integer_t lineNumber() {
		return filter.getLineNumber();
	}

	std::string readToken() {
		isNotWhitespace();
		std::string token;
		(*this) >> token;
		checkFail();
		return token;
	}

	std::string readToken(const std::regex& pattern) {
		std::string token = readToken();
		if (!std::regex_match(token, pattern)) {
			jout << "Token: '" << token << "' does not match pattern" << reportLine() << close(failVerdict);
		}
		return token;
	}

	std::string readToken(const std::string& pattern) {
		return readToken(std::regex(pattern));
	}

	integer_t readInteger() {
		std::string token = readToken(INTEGER_REGEX);
		integer_t integer;
		if (!parse(token, integer)) reportFail();
		return integer;
	}

	integer_t readInteger(integer_t l, integer_t r) {
		integer_t res = readInteger();
		if (res < l || res >= r) {
			jout << "Integer " << res << " out of range [" << l << ", " << r << ")" << reportLine() << close(failVerdict);
		}
		return res;
	}

	real_t readReal() {
		std::string token = readToken(REAL_REGEX);
		real_t real;
		if (!parse(token, real)) reportFail();
		return real;
	}

	real_t readReal(real_t l, real_t r) {
		real_t res = readReal();
		if (std::isnan(res) || res < l || res >= r) {
			jout << "Real " << res << " out of range [" << l << ", " << r << ")" << reportLine() << close(failVerdict);
		}
		return res;
	}

	void readSpace() {
		if (!strict) {
			strictModeWarning("readSpace()");
		} else {
			char c;
			this->get(c);
			checkFail();
			if (c != ' ') jout << "missing space" << reportLine() << close(failVerdict);
		}
	}

	void readEOL() {
		if (!strict) {
			strictModeWarning("readEOL()");
		} else {
			char c;
			this->get(c);
			checkFail();
			if (c != '\n') jout << "missing EOL" << reportLine() << close(failVerdict);
		}
	}

	void readEOF() {
		if (!strict) {
			strictModeWarning("readEOF()");
		} else {
			if (this->peek() != EOF) jout << "missing EOF" << reportLine() << close(failVerdict);
		}
	}

	void readDirt() {
		if (strict) {
			readEOF();
		} else {
			std::string token;
			bool foundToken = false;
			while ((*this) >> token) foundToken = true;
			if (foundToken) jout << "Dirt found" << close(failVerdict);
		}
	}
};

InStream tin;
InStream jans;
InStream pans;

namespace mzDetails {
	std::ostringstream mzTestcaseBuffer;
	OutStream mzTestcaseOut;

	void writeTestcaseBuffer() {
		std::string data = mzTestcaseBuffer.str();
		if (data.empty()) {
			jerr << "WARNING: Testcase is empty." << std::endl;
		} else {
			bool lf = false;
			bool crlf = false;
			bool invalidChar = false;
			bool weirdSpace = false;
			bool consecutive = false;

			char last = '\n';
			for (char c : data) {
				if (c < '\t' || (c > '\r' && c < ' ') || c > '~') invalidChar = true;
				if (c == '\t' || c == '\v' || c == '\f') weirdSpace = true;
				if (last == '\r' && c != '\n') weirdSpace = true;
				if (last != '\r' && c == '\n') lf = true;
				if (last == '\r' && c == '\n') crlf = true;
				if (isSpace(last) && isWhiteSpace(c)) consecutive = true;
				if (isWhiteSpace(last) && isSpace(c)) consecutive = true;
				consecutive = false;
				last = c;
			}
			if (invalidChar) jerr << "WARNING: Testcase contains non printable characters." << std::endl;
			if (weirdSpace) jerr << "WARNING: Testcase contains non typical whitespace." << std::endl;

			if (consecutive) jerr << "WARNING: Testcase contains consecutive whitespaces." << std::endl;

			if (lf && crlf) jerr << "WARNING: Testcase contains Lf and CRLF." << std::endl;
			else if (lf) jerr << "Testcase contains LF." << std::endl;
			else if (crlf) jerr << "WARNING: Testcase contains CRLF." << std::endl;

			if (last != '\n') jerr << "WARNING: Testcase ends without newline." << std::endl;

			if (data.size() > TESTCASE_SIZE_LIMIT) jerr << "WARNING: Testcase is really big." << std::endl;
		}
		mzTestcaseOut << data << std::flush;
	}

	void checkJerr() {
		if (!jerr.good()) std::cerr << "Could not open error stream" << close(FAIL);
	}

	void checkJout() {
		if (!jout.good()) jerr << "Could not open judge output" << close(FAIL);
	}

	void checkPout() {
		if (!pout.good()) jerr << "Could not open participants output" << close(FAIL);
	}

	void checkTin() {
		if (!tin.good()) jerr << "Could not read test case" << close(FAIL);
	}

	void checkJans() {
		if (!jans.good()) jerr << "Could not read jury answer" << close(FAIL);
	}

	void checkPans() {
		if (!pans.good()) jerr << "Could not read participants answer" << close(FAIL);
	}
}

namespace mzDetails {
	bool startsWith(const std::string& a, const std::string& b) {
		if (a.size() < b.size()) return false;
		for (size_t i = 0; i < b.size(); i++) {
			if (a[i] != b[i]) return false;
		}
		return true;
	}
};

struct CommandParser {
private:
	std::vector<std::string> raw;
	std::map<std::string, std::pair<integer_t, integer_t>> commands;
public:
	CommandParser() {}
	CommandParser(int argc, char **argv) : raw(argc) {
		if (argc <= 0) return;
		std::string command = DEFAULT_COMMAND;
		integer_t first = 0;
		integer_t count = 0;
		for (int i = 0; i < argc; i++) {
			raw[i] = std::string(argv[i]);
			if (mzDetails::startsWith(raw[i], COMMAND_PREFIX)) {
				commands.insert({command, {first, count}});
				if (commands.count(raw[i]) != 0) jout << "Duplicated argument: " << raw[i] << close(FAIL);
				command = raw[i];
				first = i+1;
				count = 0;
			} else {
				count++;
			}
		}
		commands.insert({command, {first, count}});
	}
	struct Paramater {
	private:
		const std::string* token;
	public:
		Paramater(const std::string* _token) : token(_token) {}

		const std::string& asString() {
			if (token == nullptr) jout << "accessed invalid parameter" << close(FAIL);
			return *token;
		}

		const std::string& asString(const std::string& defaultValue) {
			if (token == nullptr) return defaultValue;
			return asString();
		}

		integer_t asInteger() {
			if (token == nullptr) jout << "accessed invalid parameter" << close(FAIL);
			integer_t res;
			if (!parse(asString(), res)) jout << "parameter is not an integer: " << asString() << close(FAIL);
			return res;
		}

		integer_t asInteger(integer_t defaultValue) {
			if (token == nullptr) return defaultValue;
			return asInteger();
		}

		real_t asReal() {
			if (token == nullptr) jout << "accessed invalid parameter" << close(FAIL);
			real_t res;
			if (!parse(asString(), res)) jout << "parameter is not a real: " << asString() << close(FAIL);
			return res;
		}

		real_t asReal(integer_t defaultValue) {
			if (token == nullptr) return defaultValue;
			return asReal();
		}
	};
	struct Command : Paramater {
		private:
		const std::vector<std::string>& raw;
		integer_t first, count;
		public:
		Command(const std::vector<std::string>& _raw, integer_t _first, integer_t _count)
			: Paramater(_count > 0 ? &_raw[_first] : nullptr), raw(_raw), first(_first), count(_count) {}

		bool exists() const {
			return count >= 0;
		}

		operator bool() const {return exists();}

		integer_t parameterCount() const {
			return count;
		}

		Paramater operator[](integer_t i) {
			if (i >= 0 && i < count) return Paramater(&raw[first + i]);
			return Paramater(nullptr);
		}
	};
	Command operator[](const std::string& command) const {
		auto it = commands.find(command);
		if (it == commands.end()) {
			return Command(raw, 0, -1);
		} else {
			return Command(raw, it->second.first, it->second.second);
		}
	}
	Command getRaw() const {
		return Command(raw, 0, raw.size());
	}
};

CommandParser commands;

void init_io(int argc, char **argv) {
	if (argc != 4) std::cerr << "Wrong number of arguments: " << argc << ", expected 4" << close(FAIL);

	std::string feedbackDir(argv[3]);
	if (!feedbackDir.empty() && feedbackDir.back() != '/') feedbackDir.push_back('/');
	
	jerr = OutStream(feedbackDir + JUDGE_ERROR);
	mzDetails::checkJerr();

	jout = OutStream(feedbackDir + JUDGE_MESSAGE);
	mzDetails::checkJout();

	pout = OutStream(std::cout);
	mzDetails::checkPout();

	tin = InStream(std::string(argv[1]), FAIL);
	mzDetails::checkTin();

	jans = InStream(std::string(argv[2]), FAIL);
	mzDetails::checkJans();

	pans = InStream(std::cin, WA);
	mzDetails::checkPans();
	commands = CommandParser(argc, argv);
}

void init_gen(int argc, char **argv) {
	jerr = OutStream(std::cerr);
	mzDetails::checkJerr();

	jout = OutStream(mzDetails::mzTestcaseBuffer);
	mzDetails::checkJout();

	mzDetails::mzTestcaseOut = OutStream(std::cout);
	if (!mzDetails::mzTestcaseOut.good()) jerr << "Could not open output stream" << close(FAIL);

	jans = InStream(std::cin, FAIL);
	mzDetails::checkJans();

	if (argc >= 2) seedRandom(std::hash<std::string>()(std::string(argv[1])));

	std::atexit(mzDetails::writeTestcaseBuffer);
	commands = CommandParser(argc, argv);
}

void init_val(int argc, char **argv) {
	jerr = OutStream(std::cerr);
	mzDetails::checkJerr();

	jout = OutStream(std::cout);
	mzDetails::checkJout();

	tin = InStream(std::cin, FAIL, true);
	mzDetails::checkTin();
	commands = CommandParser(argc, argv);
}

template<class T>
void ForEachTest(const T& function) {
	integer_t t = tin.readInteger();
	tin.readEOL();
	for (integer_t i = 1; i <= t; i++) {
		function(i);
	}
	tin.readEOF();
}

namespace mzDetails {
	template<class F>
	struct istreamReader {
		F callable;
		istreamReader(F _callable) : callable(_callable) {}
		friend InStream& operator>>(InStream& str, const istreamReader& reader) {
			reader.callable(str);
			return str;
		}
	};

	template<class F>
	istreamReader<F> buildReader(F f) {
		return istreamReader<F>(f);
	}
}

namespace validator {
	auto SPACE = mzDetails::buildReader([](InStream& str){str.readSpace();});
	auto NEWLINE = mzDetails::buildReader([](InStream& str){str.readEOL();});
	auto ENDFILE = mzDetails::buildReader([](InStream& str){str.readEOF();});

	auto INT() {
		return mzDetails::buildReader([=](InStream& str){
			return str.readInteger();
		});
	}
	auto INT(integer_t& x) {
		return mzDetails::buildReader([&x](InStream& str){
			x = str.readInteger();
		});
	}
	auto INT(integer_t l, integer_t r) {
		return mzDetails::buildReader([=](InStream& str){
			return str.readInteger(l, r);
		});
	}
	auto INT(integer_t l, integer_t r, integer_t& x) {
		return mzDetails::buildReader([=,&x](InStream& str){
			x = str.readInteger(l, r);
		});
	}

	auto REAL() {
		return mzDetails::buildReader([=](InStream& str){
			return str.readReal();
		});
	}
	auto REAL(real_t& x) {
		return mzDetails::buildReader([&x](InStream& str){
			x = str.readReal();
		});
	}
	auto REAL(real_t l, real_t r) {
		return mzDetails::buildReader([=](InStream& str){
			return str.readReal(l, r);
		});
	}
	auto REAL(real_t l, real_t r, real_t& x) {
		return mzDetails::buildReader([=,&x](InStream& str){
			x = str.readReal(l, r);
		});
	}

	auto TOKEN() {
		return mzDetails::buildReader([=](InStream& str){
			return str.readToken();
		});
	}
	auto TOKEN(std::string& x) {
		return mzDetails::buildReader([&x](InStream& str){
			x = str.readToken();
		});
	}
	auto TOKEN(const std::regex& pattern) {
		return mzDetails::buildReader([=](InStream& str){
			return str.readToken(pattern);
		});
	}
	auto TOKEN(const std::regex& pattern, std::string& x) {
		return mzDetails::buildReader([=,&x](InStream& str){
			x = str.readToken(pattern);
		});
	}

	template<typename RandomIt, class F, class G>
	auto LIST(RandomIt first, RandomIt last, 
			  mzDetails::istreamReader<F> x,
			  mzDetails::istreamReader<G> y) {
		return mzDetails::buildReader([=](InStream& str){
			for (auto it = first; it != last; it++) {
				*it = x.callable(str);
				if (next(it) != last) y.callable(str);
			}
		});
	}

	template<typename RandomIt, class F>
	auto LIST(RandomIt first, RandomIt last, 
			  mzDetails::istreamReader<F> x) {
		return LIST(first, last, x, SPACE);
	}

}

namespace mzDetails {
	struct InitGuard{
		~InitGuard(){
			if (commands.getRaw().parameterCount() == 0) {
				std::cerr << "You should call either \'init_io\', \'init_gen\' or \'init_val\' to use mz_validate" << std::endl;
			}
		}
	} initGuard;
}
