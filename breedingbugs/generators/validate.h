//============================================================================//
// validate.h                                                                 //
//============================================================================//
// This header can be used to safely parse team output tokenwise. We support:
// - string tokens (get converted to lowercase)
// - integer tokens in [-2^63, 2^63)
// - float tokens (relative and absolute error of 10^6 is allowed)
// Tokens need to be separated by whitespace (any amount). The follwoing
// command line flags allow stricter checking:
// - case_sensitive: string tokens don't get converted to lowercase
// - space_change_sensitive: tokens need to be separated by the corecct amount
//   of whitespaces
// - FLOAT_{|RELATIVE|ABSOLUTE}_TOLERANCE: allowed relative/absolute error
//
// This header can be used to safely verify input files. In this case tokens are
// case sensitive and all whitespaces have to be checked. Also whitespaces are
// not interchangeable.
//
// This header can be used to generate random numbers in a deterministic and
// reproducable fashion. (The randomness is consistent across compilers and
// machines)
//============================================================================//

#ifndef VALIDATE_H
#define VALIDATE_H

#define DOUBLE_FALLBACK

#include <algorithm>
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


//============================================================================//
// Basic definitions and constants                                            //
//============================================================================//
// default types
using Integer = int64_t;
using Real = long double;

// default flags
constexpr std::string_view CASE_SENSITIVE				= "case_sensitive";
constexpr std::string_view SPACE_SENSITIVE				= "space_change_sensitive";
constexpr std::string_view FLOAT_ABSOLUTE_TOLERANCE		= "float_absolute_tolerance";
constexpr std::string_view FLOAT_RELATIVE_TOLERANCE		= "float_relative_tolerance";
constexpr std::string_view FLOAT_TOLERANCE				= "float_tolerance";

// default files
constexpr std::string_view JUDGE_MESSAGE = "judgemessage.txt";

// internal defaults
constexpr int DEFAULT_PRECISION = 10;
constexpr Real DEFAULT_EPS = 1e-6l;
constexpr char DEFAULT_SEPARATOR						= ' ';
constexpr std::string_view COMMAND_PREFIX				= "--";
constexpr std::string_view EMPTY_COMMAND				= "";
constexpr std::string_view CONSTRAINT_COMMAND			= "--constraints_file";
constexpr std::string_view SEED_COMMAND					= "--seed";
const std::regex INTEGER_REGEX("0|-?[1-9][0-9]*", std::regex_constants::optimize);
const std::regex REAL_REGEX("-?(0|([1-9][0-9]*))(\\.[0-9]*)?([eE][+-]?(0|([1-9][0-9]*)))?", std::regex_constants::optimize);
const std::regex STRICT_REAL_REGEX("-?(0|([1-9][0-9]*))\\.?[0-9]*", std::regex_constants::optimize);


//============================================================================//
// Basic datastructures                                                       //
//============================================================================//
// make usage of std::priority_queue easier...
template<typename T>
using MinPQ = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T>
using MaxPQ = std::priority_queue<T, std::vector<T>, std::less<T>>;

template<typename C, typename K>
bool contains(const C& container, const K& key) {
	return container.find(key) != container.end();
}

//============================================================================//
// Verdicts                                                                   //
//============================================================================//
struct Verdict final {
	int exitCode;

	constexpr Verdict(int exitCode_ = 1) : exitCode(exitCode_) {}

	constexpr operator int() const {
		return exitCode;
	}

	void exit() const {
		//std::quick_exit(exitCode)
		std::exit(exitCode);
	}

	friend void operator<<(std::ostream& str, const Verdict& v) {
		str << std::endl;
		v.exit();
	}
};

// default verdicts (we do not support scoring)
constexpr Verdict AC(42);
constexpr Verdict WA(43);
constexpr Verdict PE = WA;
constexpr Verdict FAIL(1);


//============================================================================//
// Output streams and error handling                                          //
//============================================================================//
void judgeAssert(bool, std::string_view);

class OutputStream final {
	std::ofstream managed;
	std::ostream* os;

	void init() {
		*os << std::boolalpha;
		*os << std::fixed;
		*os << std::setprecision(DEFAULT_PRECISION);
	}

public:
	OutputStream() : managed(), os(nullptr) {}
	OutputStream(std::ostream& os_) : managed(), os(&os_) {init();}
	OutputStream(std::filesystem::path path) : managed(path), os(&managed) {
		judgeAssert(managed.good(), "Could not open File: " + path.string());
		init();
	}

	OutputStream(OutputStream&& other) {
		if (&(other.managed) == other.os) {
			managed = std::move(other.managed);
			os = &managed;
		} else {
			managed = std::move(other.managed);
			os = other.os;
		}
	}
	OutputStream& operator=(OutputStream&& other) {
		if (this != &other) {
			if (&(other.managed) == other.os) {
				managed = std::move(other.managed);
				os = &managed;
			} else {
				managed = std::move(other.managed);
				os = other.os;
			}
		}
		return *this;
	}

	OutputStream(const OutputStream&) = delete;
	OutputStream& operator=(const OutputStream&) = delete;

	template <class T>
	OutputStream& operator<<(T&& x) {
		if (os) *os << std::forward<T>(x);
		return *this;
	}

	OutputStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
		if (os) *os << manip;
		return *this;
	}
};

namespace ValidateBase {
	OutputStream juryErr(std::cerr);
	OutputStream juryOut(std::cout);
}


// this is mainly for debug purpose you should not use it in the final interactor!
// TODO use c++23 stacktrace
#ifdef PRINT_BACKTRACE

#define BOOST_STACKTRACE_USE_ADDR2LINE
#include <boost/stacktrace.hpp>
#include <filesystem>

namespace details {
	void printCaller(OutputStream& os) {
		auto st = boost::stacktrace::stacktrace();
		// st[0] should be boost::stacktrace::stacktrace()
		// st[1] should be printCaller()
		for (size_t i = 2; i < st.size(); i++) {
			if (st[i].source_file() != st[1].source_file()) {
				//this is the failing call to validate.h
				using native_frame_ptr_t = boost::stacktrace::detail::native_frame_ptr_t;
				auto callerAddress = reinterpret_cast<std::uintptr_t>(st[i].address()) - 1;
				boost::stacktrace::frame caller(reinterpret_cast<native_frame_ptr_t>(callerAddress));

				std::string file = caller.source_file();
				std::size_t line = caller.source_line();
				if (std::size_t pos = file.find_last_of('/'); pos != std::string::npos) {
					file = file.substr(pos + 1);
				}
				os << "Call to validate.h: " << file << ":" << line << std::endl;
				return;
			}
		}
	}
}
#else
namespace details {
	inline void printCaller(OutputStream& os) {
		(void)os;
	}
}
#endif


void judgeAssert(bool asserted, std::string_view message = EMPTY_COMMAND) {
	if (!asserted) {
		details::printCaller(ValidateBase::juryErr);
		ValidateBase::juryErr << "Assert failed! " << message << FAIL;
	}
}


//============================================================================//
// Utility                                                                    //
//============================================================================//
// for sequences
template<class RandomIt, typename std::enable_if_t<std::is_integral_v<typename RandomIt::value_type>, bool> = true>
constexpr bool isPerm(RandomIt first, RandomIt last, typename RandomIt::value_type offset = 0) {
	std::vector<typename RandomIt::value_type> tmp(first, last);
	std::sort(tmp.begin(), tmp.end());
	for (std::size_t i = 0; i < tmp.size(); i++, offset++) {
		if (tmp[i] != offset) return false;
	}
	return true;
}

template<class RandomIt, class BinaryPredicate>
constexpr bool anyAdjacent(RandomIt first, RandomIt last, BinaryPredicate p) {
	return std::adjacent_find(first, last, p) != last;
}

template<class RandomIt, class BinaryPredicate>
constexpr bool noneAdjacent(RandomIt first, RandomIt last, BinaryPredicate p) {
	return std::adjacent_find(first, last, p) == last;
}

template<class RandomIt, class BinaryPredicate>
constexpr bool allAdjacent(RandomIt first, RandomIt last, BinaryPredicate p) {
	return std::adjacent_find(first, last, std::not_fn(p)) == last;
}

template<class RandomIt>
constexpr bool isUnique(RandomIt first, RandomIt last) {
	using T = typename RandomIt::value_type;
	std::vector<T> tmp(first, last);
	std::sort(tmp.begin(), tmp.end());
	return allAdjacent(tmp.begin(), tmp.end(), std::not_equal_to<T>());
}

template<class RandomIt>
constexpr bool isIncreasing(RandomIt first, RandomIt last) {
	using T = typename RandomIt::value_type;
	return allAdjacent(first, last, std::less<T>());
}

template<class RandomIt>
constexpr bool isNonDecreasing(RandomIt first, RandomIt last) {
	using T = typename RandomIt::value_type;
	return allAdjacent(first, last, std::less_equal<T>());
}

template<class RandomIt>
constexpr bool isDecreasing(RandomIt first, RandomIt last) {
	using T = typename RandomIt::value_type;
	return allAdjacent(first, last, std::greater<T>());
}

template<class RandomIt>
constexpr bool isNonIncreasing(RandomIt first, RandomIt last) {
	using T = typename RandomIt::value_type;
	return allAdjacent(first, last, std::greater_equal<T>());
}


// for strings (cctype functions are not safe to use with char...)
char toLower(char c) {
	return static_cast<char>(tolower(static_cast<unsigned char>(c)));
}

char toUpper(char c) {
	return static_cast<char>(toupper(static_cast<unsigned char>(c)));
}

void toLower(std::string& s) {
	std::transform(s.begin(), s.end(), s.begin(), [](char c){return toLower(c);});
}

void toUpper(std::string& s) {
	std::transform(s.begin(), s.end(), s.begin(), [](char c){return toUpper(c);});
}

bool isLower(char c) {
	return std::islower(static_cast<unsigned char>(c));
}

bool isUpper(char c) {
	return std::isupper(static_cast<unsigned char>(c));
}

bool isDigit(char c) {
	return std::isdigit(static_cast<unsigned char>(c));
}

bool isLower(std::string_view s) {
	return std::all_of(s.begin(), s.end(), [](char c){return isLower(c);});
}

bool isUpper(std::string_view s) {
	return std::all_of(s.begin(), s.end(), [](char c){return isUpper(c);});
}

bool isDigits(std::string_view s) {
	return std::all_of(s.begin(), s.end(), [](char c){return isDigit(c);});
}


// allow using std::pair and std::complex similiar
// (may be useful for geometric problem)
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
	str << t.first << DEFAULT_SEPARATOR << t.second;
	return str;
}


// allow printing colletions as:
// join(begin(), end(), [sep])
template<class T>
struct Join final {
	using iterator = T;
	using value_type = typename std::iterator_traits<iterator>::value_type;
	using reference = value_type&;
	using const_reference = const value_type&;

private:
	std::optional<std::vector<value_type>> data;

public:
	const iterator first;
	const iterator last;
	const char separator;

	Join(iterator first_, iterator last_, char separator_ = DEFAULT_SEPARATOR)
	     : first(first_), last(last_), separator(separator_) {}

	Join(std::initializer_list<value_type> data_, char separator_ = DEFAULT_SEPARATOR)
	     : data(data_), first(data->begin()), last(data->end()), separator(separator_) {}

	Join(const Join&) = delete;
	Join(Join&&) = delete;
	Join& operator=(const Join&) = delete;
	Join& operator=(Join&&) = delete;

	const iterator begin() const {return first;}
	const iterator end() const {return last;}

	friend std::ostream& operator<<(std::ostream& str, const Join<T>& t) {
		for (auto it = t.begin(); it != t.end(); it++) {
			str << *it;
			if (std::next(it) != t.end()) str << t.separator;
		}
		return str;
	}

	std::string asString() const {
		std::ostringstream os;
		os << *this;
		return os.str();
	}
};

template<class T>
Join<T> join(T first, T last, char separator = DEFAULT_SEPARATOR) {
	return Join<T>(first, last, separator);
}

template<class T>
Join<typename std::vector<T>::iterator>
join(std::initializer_list<T> in, char separator = DEFAULT_SEPARATOR) {
	return Join<typename std::vector<T>::iterator>(in, separator);
}

namespace details {
	// Test two numbers for equality, accounting for +/-INF, NaN and precision.
	// Real expected is considered the reference value for relative error.
	bool floatEqual(Real given, Real expected, Real floatAbsTol, Real floatRelTol) {
		// Finite values are compared with some tolerance
		if (std::isfinite(given) && std::isfinite(expected)) {
			Real absDiff = fabsl(given-expected);
			Real relDiff = fabsl((given-expected)/expected);
			return absDiff <= floatAbsTol || relDiff <= floatRelTol;
		}
		// NaN is equal to NaN (-NaN is also euqal NaN)
		if (std::isnan(given) && std::isnan(expected)) {
			return true;
		}
		// Infinite values are equal if their sign matches
		if (std::isinf(given) && std::isinf(expected)) {
			return std::signbit(given) == std::signbit(expected);
		}
		// Values in different classes are always different.
		return false;
	}

	template<typename T>
	bool parse(std::string_view s, T& res) {
		auto begin = s.data();
		auto end = s.data() + s.size();
		auto [ptr, ec] = std::from_chars(begin, end, res);
		return ptr == end && ec == std::errc();
	}
	#ifdef DOUBLE_FALLBACK
	template<>
	bool parse(std::string_view s, Real& res) {
		try {
			std::size_t pos = 0;
			res = std::stold(std::string(s), &pos);
			return pos == s.size();
		} catch(...) {
			return false;
		}
	}
	#endif

}

//============================================================================//
// Random                                                                     //
//============================================================================//
namespace Random {
	// You should not rely on the implementation in details!
	// Especially you should never use rng on your own. there is no function in
	// c++ which uses a random engine and is not implementation defined.
	namespace details {
		constexpr uint64_t DEFAULT_SEED = 3141592653589793238ull;
		constexpr Real PI = 3.141592653589793238462643383279502884l;

		std::mt19937_64 rng(DEFAULT_SEED);
		static_assert(std::mt19937_64::max() == 0xFFFF'FFFF'FFFF'FFFFull, "Random Engine should produce 64bit of randomness");
		static_assert(std::mt19937_64::min() == 0ull, "Random Engine should produce 64bit of randomness");
		static_assert(-1 == static_cast<Integer>(0xFFFF'FFFF'FFFF'FFFFull), "Two's complement signed numbers are required" );

		constexpr uint64_t bitMask(uint64_t x) {
			x |= x >> 1;
			x |= x >> 2;
			x |= x >> 4;
			x |= x >> 8;
			x |= x >> 16;
			x |= x >> 32;
			return x;
		}
	}

	void seed(uint64_t seed) {
		details::rng.seed(seed);
	}

	//========================================================================//
	// Distributions and generators                                           //
	//========================================================================//
	bool bit() {// in {0, 1}
		return std::bitset<64>(details::rng()).count() & 1;
	}

	Integer integer() {// in [-2^63, 2^63)
		return details::rng();
	}
	Integer integer(Integer lower, Integer upper) {// in [lower, upper)
		judgeAssert(lower < upper, "Lower must be less than upper!");
		uint64_t ul = static_cast<uint64_t>(lower);
		uint64_t uu = static_cast<uint64_t>(upper);
		uint64_t mask = details::bitMask(uu - ul - 1u);
		uint64_t res;
		do {
			res = details::rng() & mask;
		} while (res >= uu - ul);
		return static_cast<Integer>(res + ul);
	}
	Integer integer(Integer upper) {// in [0, upper)
		return integer(0, upper);
	}
	std::function<Integer()> integerGenerator(Integer lower, Integer upper) {
		return [=](){return integer(lower, upper);};
	}

	Real real() {// in [0, 1)
		Real res = details::rng() / 0x1.0p64l;
		res += details::rng() / 0x1.0p128l;
		judgeAssert(res < 1.0l, "Generated real() was outside of range!");
		return res;
	}
	Real real(Real upper) {// in [0, upper)
		judgeAssert(upper > 0, "Upper must be greater than zero!");
		return real()*upper;
	}
	Real real(Real lower, Real upper) {// in [lower, upper)
		judgeAssert(lower < upper, "Lower must be less than upper!");
		return real(upper - lower) + lower;
	}
	std::function<Real()> realGenerator(Real lower, Real upper) {
		return [=](){return real(lower, upper);};
	}

	Real normal(Real lower, Real upper, Real mean, Real stddev) {// in [lower, upper)
		judgeAssert(lower < upper, "Lower must be less than upper!");
		Real res;
		while (true) {
			Real u1 = real();
			Real u2 = real();
			// Box-Muller-Methode
			// https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
			res = std::sqrt(-2.0l * std::log(u1)) * std::cos(2.0l * details::PI * u2);
			res = std::sqrt(stddev) * res + mean;
			if (lower <= res && res < upper) break;
			res = std::sqrt(-2.0l * std::log(u1)) * std::sin(2.0l * details::PI * u2);
			res = std::sqrt(stddev) * res + mean;
			if (lower <= res && res < upper) break;
		}
		return res;
	}
	std::function<Real()> normalGenerator(Real lower, Real upper, Real mean, Real stddev) {
		return std::bind(normal, lower, upper, mean, stddev);
	}

	Real exponential(Real lower, Real upper, Real lambda) {// in [lower, upper)
		judgeAssert(lower < upper, "Lower must be less than upper!");
		while (true) {
			Real res = lower - std::log(real()) / lambda;
			if (res < upper) return res;
		}
	}
	std::function<Real()> exponentialGenerator(Real lower, Real upper, Real lambda) {
		return std::bind(exponential, lower, upper, lambda);
	}

	Integer geometric(Integer lower, Integer upper, Real p) {// in [lower, upper)
		judgeAssert(lower < upper, "Lower must be less than upper!");
		while (true) {
			// https://en.wikipedia.org/wiki/Geometric_distribution
			// "The exponential distribution is the continuous analogue of the geometric distribution[...]"
			Integer res = lower + static_cast<Integer>(std::floor(std::log(real()) / std::log1p(-p)));
			if (res < upper) return res;
		}
	}
	std::function<Integer()> geometricGenerator(Integer lower, Integer upper, Real p) {
		return std::bind(geometric, lower, upper, p);
	}

	Integer binomial(Integer lower, Integer upper, Integer n, Real p) {// in [lower, upper)
		judgeAssert(lower < upper, "Lower must be less than upper!");
		// this will be slow for large n
		// (a faster implementation requires efficient poisson sampling)
		while (true) {
			Integer res = 0;
			for (Integer i = 0; i < n; i++) {
				res += real() < p ? 1 : 0;
			}
			if (lower <= res && res < upper) return res;
		}
	}
	std::function<Integer()> binomialGenerator(Integer lower, Integer upper, Integer n, Real p) {
		return std::bind(binomial, lower, upper, n, p);
	}

	//========================================================================//
	// utility                                                                //
	//========================================================================//
	template<class RandomIt>
	const typename std::iterator_traits<RandomIt>::value_type&
	select(RandomIt first, RandomIt last) {
		return first[integer(0, last - first)];
	}

	template<typename T>
	T select(const std::pair<T, T>& t) {
		return bit() ? getX(t) : getY(t);
	}

	template<typename T>
	T select(const std::complex<T>& t) {
		return bit() ? getX(t) : getY(t);
	}

	template<class RandomIt>
	void shuffle(RandomIt first, RandomIt last) {
		auto n = last - first;
		for (auto i = n-1; i > 0; --i) {
			std::swap(first[i], first[integer(0, i+1)]);
		}
	}

	template<typename T>
	void shuffle(std::pair<T, T>& t) {
		if (bit()) std::swap(t.first, t.second);
	}

	template<typename T>
	void shuffle(std::complex<T>& t) {
		if (bit()) t = {getY(t), getX(t)};
	}

} // namespace Random


//============================================================================//
// args parser                                                                //
//============================================================================//
class ParamaterBase {
	friend class Command;
	friend class Paramater;

	std::optional<std::string_view> token;

	template<typename T>
	T parse(std::string_view s) const {
		T res = {};
		judgeAssert(details::parse<T>(s, res), "Could not parse args");
		return res;
	}

	ParamaterBase() {}
	ParamaterBase(std::string_view token_) : token(token_) {}

public:
	bool exists() const {
		return token.has_value();
	}

	explicit operator bool() const {
		return token.has_value();
	}

	std::string asString() const {
		return std::string(token.value());
	}

	std::string asString(std::string_view defaultValue) const {
		return std::string(token.value_or(defaultValue));
	}

	Integer asInteger() const {
		return parse<Integer>(token.value());
	}

	Integer asInteger(Integer defaultValue) const {
		if (token) return asInteger();
		return defaultValue;
	}

	Real asReal() const {
		return parse<Real>(token.value());
	}

	Real asReal(Real defaultValue) const {
		if (token) return asReal();
		return defaultValue;
	}
};

class Paramater final : public ParamaterBase {
public:
	Paramater() : ParamaterBase() {}
	Paramater(std::string_view token_) : ParamaterBase(token_) {}
};

class Command final : public ParamaterBase {
	const std::vector<std::string>& raw;
	const Integer first, count;
public:
	Command(const std::vector<std::string>& raw_) : raw(raw_), first(0), count(0) {}
	Command(const std::vector<std::string>& raw_, Integer first_, Integer count_)
	        : ParamaterBase(count_ == 0 ? ParamaterBase(EMPTY_COMMAND) : ParamaterBase(raw_[first_])), 
	          raw(raw_), first(first_), count(count_) {
		judgeAssert(count >= 0, "Invalid command in args!");
	}

	Integer parameterCount() const {
		return count;
	}

	Paramater operator[](Integer i) const {
		if (i >= 0 && i < count) return Paramater(raw[first + i]);
		return Paramater();
	}

	std::vector<std::string> asStrings() const {
		std::vector<std::string> res;
		std::transform(raw.begin() + first,
		               raw.begin() + first + count,
		               std::back_inserter(res), [](const std::string& value){
			return std::string(value);
		});
		return res;
	}

	std::vector<Integer> asIntegers() const {
		std::vector<Integer> res;
		std::transform(raw.begin() + first,
		               raw.begin() + first + count,
		               std::back_inserter(res), [this](const std::string& value){
			return parse<Integer>(value);
		});
		return res;
	}

	std::vector<Real> asReals() const {
		std::vector<Real> res;
		std::transform(raw.begin() + first,
		               raw.begin() + first + count,
		               std::back_inserter(res), [this](const std::string& value){
			return parse<Real>(value);
		});
		return res;
	}

};

class CommandParser final {
	std::vector<std::string> raw;
	std::map<std::string_view, std::pair<Integer, Integer>> commands;
	std::map<std::string_view, Integer> tokens;

	bool isCommand(std::string_view s) {
		return s.size() > 2 && s.substr(0, 2) == COMMAND_PREFIX;
	}
	void addCommand(std::string_view command, Integer first, Integer count = 0) {
		judgeAssert(commands.count(command) == 0, "Duplcated command in args!");
		commands.insert({command, {first, count}});
	}

public:
	CommandParser() {}
	CommandParser(int argc, char** argv) {
		raw.assign(argc, {});
		std::string_view command = EMPTY_COMMAND;
		Integer first = 0;
		Integer count = 0;
		for (int i = 0; i < argc; i++) {
			raw[i] = std::string(argv[i]);
			tokens.emplace(raw[i], i+1);
			if (isCommand(raw[i])) {
				addCommand(command, first, count);
				command = raw[i];
				first = i+1;
				count = 0;
			} else {
				count++;
			}
		}
		addCommand(command, first, count);
	}
	CommandParser(CommandParser&&) = default;
	CommandParser& operator=(CommandParser&&) = default;

	CommandParser(const CommandParser&) = delete;
	CommandParser& operator=(const CommandParser&) = delete;

	std::string_view operator[](Integer t) const {
		judgeAssert(t >= 0 && t < static_cast<Integer>(raw.size()), "Index out of args!");
		return raw[t];
	}
	Command operator[](std::string_view command) const {
		auto it = commands.find(command);
		if (it == commands.end()) return Command(raw);
		return Command(raw, it->second.first, it->second.second);
	}
	Command getRaw(std::string_view s) const {
		auto it = tokens.find(s);
		if (it == tokens.end()) return Command(raw);
		return Command(raw, it->second, raw.size() - it->second);
	}
	Command getRaw() const {
		return Command(raw, 0, raw.size());
	}
};


//============================================================================//
// Constraints                                                                //
//============================================================================//
template<typename T>
class Bounds final {
	T min, max;				// range of seen values
	T lower, upper;			// bounds for value
	bool hadMin, hadMax;	// was value==lower/upper at some point
public:
	constexpr Bounds(T lower_, T upper_, T value_) :
	                 min(value_), max(value_),
	                 lower(lower_), upper(upper_),
	                 hadMin(false), hadMax(false) {
		update(lower_, upper_, value_);
	}

	void update(T lower_, T upper_, T value_) {
		min = std::min(min, value_);
		max = std::max(max, value_);
		lower = std::min(lower, lower_);
		upper = std::max(upper, upper_);
		if constexpr (std::is_same_v<T, Real>) {
			hadMin |= details::floatEqual(value_, lower_, DEFAULT_EPS, DEFAULT_EPS);
			hadMax |= details::floatEqual(value_, upper_, DEFAULT_EPS, DEFAULT_EPS);
		} else {
			hadMin |= value_ == lower_;
			hadMax |= value_ == upper_;
		}
	}

	void write(std::ostream& os) const {
		os << hadMin << " " << hadMax << " ";
		os << lower << " " << upper << " ";
		os << min << " " << max << " ";
	}
};

namespace details {
	//using typeIndex = std::type_index;
	using typeIndex = void*;

	template<class T>
	typeIndex getTypeIndex() {
		//return std::type_index(type id(T));
		static T* uniqueTypeIndex = NULL;
		return &uniqueTypeIndex;
	}
}

class Constraint final {
	friend class ConstraintsLogger;
	std::variant<
		std::monostate,		// uninitialized
		Bounds<Integer>,	// Integer or container bound
		Bounds<Real>		// Real bound
	> bound;
	std::optional<details::typeIndex> type;

	template<typename T, typename X = T>
	void update(T lower, T upper, T value) {
		if constexpr(std::is_integral_v<T>) {
			upper--; // for BAPCtools the range is closed but we use half open ranges!
		}
		if (!type) {
			type = details::getTypeIndex<X>();
			bound = Bounds<T>(lower, upper, value);
		}
		judgeAssert(type == details::getTypeIndex<X>(), "Constraint changed Type!");
		std::get<Bounds<T>>(bound).update(lower, upper, value);
	}
public:
	Constraint() = default;
	Constraint(const Constraint&) = delete;
	Constraint& operator=(const Constraint&) = delete;

	template<typename V, typename std::enable_if_t<std::is_integral_v<V>, bool> = true>
	void log(Integer lower, Integer upper, V value) {
		update<Integer>(lower, upper, value);
	}

	template<typename V, typename std::enable_if_t<std::is_floating_point_v<V>, bool> = true>
	void log(Real lower, Real upper, V value) {
		update<Real>(lower, upper, value);
	}

	template<typename C, typename std::enable_if_t<!std::is_arithmetic_v<C>, bool> = true>
	void log(Integer lower, Integer upper, const C& container) {
		update<Integer, C>(lower, upper, static_cast<Integer>(std::size(container)));
	}
};

class ConstraintsLogger final {
	std::optional<std::string> fileName;
	std::map<std::string, std::size_t> byName;
	std::vector<std::unique_ptr<Constraint>> constraints;
public:
	ConstraintsLogger() {}
	ConstraintsLogger(std::string_view fileName_) : fileName(fileName_) {}
	ConstraintsLogger(ConstraintsLogger&&) = default;
	ConstraintsLogger& operator=(ConstraintsLogger&&) = default;

	ConstraintsLogger(const ConstraintsLogger&) = delete;
	ConstraintsLogger& operator=(const ConstraintsLogger&) = delete;

	Constraint& operator[](const std::string& name) {
		judgeAssert(name.find(' ') == std::string::npos, "Constraint changed Type!");
		auto res = byName.try_emplace(name, constraints.size());
		if (res.second) constraints.emplace_back(std::make_unique<Constraint>());
		return *(constraints[res.first->second]);
	}

	void write() const {
		if (!fileName) return;
		std::ofstream os(*fileName);
		os << std::noboolalpha;
		os << std::fixed;
		os << std::setprecision(DEFAULT_PRECISION);
		for (auto& [name, id] : byName) {
			const Constraint& c = *(constraints[id]);
			if (c.type) {
				os << "LocationNotSupported:??? " << name << " ";
				if (c.bound.index() == 1) std::get<1>(c.bound).write(os);
				if (c.bound.index() == 2) std::get<2>(c.bound).write(os);
				os << std::endl;
			}
		}
	}

	~ConstraintsLogger() {
		write();
	}
};

//============================================================================//
// custom input stream                                                        //
//============================================================================//
class InputStream final {
	std::ifstream managed;
	std::istream* in;
	bool space_sensitive, case_sensitive;
	Verdict onFail;
	Real floatAbsTol = DEFAULT_EPS;
	Real floatRelTol = DEFAULT_EPS;

	void init() {
		if (space_sensitive) *in >> std::noskipws;
		else *in >> std::skipws;
	}

	void checkIn() {
		judgeAssert(in != nullptr, "InputStream is not initialized!");
	}

public:
	InputStream() {}
	InputStream(std::filesystem::path path,
	            bool space_sensitive_,
	            bool case_sensitive_,
	            Verdict onFail_,
	            Real floatAbsTol_ = DEFAULT_EPS,
	            Real floatRelTol_ = DEFAULT_EPS) :
	            managed(path),
	            in(&managed),
	            space_sensitive(space_sensitive_),
	            case_sensitive(case_sensitive_),
	            onFail(onFail_),
	            floatAbsTol(floatAbsTol_),
	            floatRelTol(floatRelTol_) {
		judgeAssert(managed.good(), "Could not open File: " + path.string());
		init();
	}
	InputStream(std::istream& in_,
	            bool space_sensitive_,
	            bool case_sensitive_,
	            Verdict onFail_,
	            Real floatAbsTol_ = DEFAULT_EPS,
	            Real floatRelTol_ = DEFAULT_EPS) :
				managed(),
	            in(&in_),
	            space_sensitive(space_sensitive_),
	            case_sensitive(case_sensitive_),
	            onFail(onFail_),
	            floatAbsTol(floatAbsTol_),
	            floatRelTol(floatRelTol_) {
		init();
	}

	InputStream(InputStream&& other) {
		if (&(other.managed) == other.in) {
			managed = std::move(other.managed);
			in = &managed;
		} else {
			managed = std::move(other.managed);
			in = other.in;
		}
		space_sensitive = other.space_sensitive;
		case_sensitive = other.case_sensitive;
		onFail = other.onFail;
		floatAbsTol = other.floatAbsTol;
		floatRelTol = other.floatRelTol;
	}
	InputStream& operator=(InputStream&& other) {
		if (this != &other) {
			if (&(other.managed) == other.in) {
				managed = std::move(other.managed);
				in = &managed;
			} else {
				managed = std::move(other.managed);
				in = other.in;
			}
			space_sensitive = other.space_sensitive;
			case_sensitive = other.case_sensitive;
			onFail = other.onFail;
			floatAbsTol = other.floatAbsTol;
			floatRelTol = other.floatRelTol;
		}
		return *this;
	}

	InputStream(const InputStream&) = delete;
	InputStream& operator=(const InputStream&) = delete;

	void eof() {
		checkIn();
		if (!space_sensitive) *in >> std::ws;
		if (in->peek() != std::char_traits<char>::eof()) {
			ValidateBase::juryOut << "Missing EOF! ";
			fail();
		}
	}

	void space() {
		checkIn();
		if (space_sensitive && in->get() != std::char_traits<char>::to_int_type(' ')) {
			ValidateBase::juryOut << "Missing space! ";
			fail();
		}
	}

	void newline() {
		checkIn();
		if (space_sensitive && in->get() != std::char_traits<char>::to_int_type('\n')) {
			ValidateBase::juryOut << "Missing newline! ";
			fail();
		}
	}

private:
	inline void check(const std::string& token, const std::regex& pattern) {
		if (!std::regex_match(token, pattern)) {
			ValidateBase::juryOut << "Token: '" << token << "' does not match pattern! ";
			fail();
		}
	}

	inline std::function<void()> checkSeparator(char separator) {
		if (separator == ' ') return [this](){space();};
		if (separator == '\n') return [this](){newline();};
		judgeAssert(false, "Separator must be ' '  or '\n'!");
		return [](){};
	}

	template<typename T>
	T parse(const std::string& s) {
		T res = {};
		if (!details::parse<T>(s, res)) {
			ValidateBase::juryOut << "Could not parse token: " << s << " ";
			fail();
		}
		return res;
	}

public:
	std::string string() {
		checkIn();
		if (space_sensitive) {
			if (!std::isgraph(in->peek())) {
				ValidateBase::juryOut << "Invalid whitespace! ";
				fail();
			}
		}
		std::string res;
		*in >> res;
		if (res.empty()) {
			ValidateBase::juryOut << "Could not read token! ";
			fail();
		}
		if (!case_sensitive) toLower(res);
		return res;
	}

	std::string string(Integer lower, Integer upper) {
		std::string t = string();
		Integer length = static_cast<Integer>(t.size());
		if (length < lower || length >= upper) {
			ValidateBase::juryOut << "String length " << length << " out of range [" << lower << ", " << upper << ") ";
			fail();
		}
		return t;
	}

	std::string string(Integer lower, Integer upper, Constraint& constraint) {
		std::string res = string(lower, upper);
		constraint.log(lower, upper, res);
		return res;
	}

	std::string string(const std::regex& pattern) {
		std::string t = string();
		check(t, pattern);
		return t;
	}

	std::string string(const std::regex& pattern, Integer lower, Integer upper) {
		std::string t = string(lower, upper);
		check(t, pattern);
		return t;
	}

	std::string string(const std::regex& pattern, Integer lower, Integer upper, Constraint& constraint) {
		std::string res = string(pattern, lower, upper);
		constraint.log(lower, upper, res);
		return res;
	}

	template<typename... Args>
	std::vector<std::string> strings(Args... args, Integer count, char separator) {
		auto sepCall = checkSeparator(separator);
		std::vector<std::string> res(count);
		for (Integer i = 0; i < count; i++) {
			res[i] = string(args...);
			if (i + 1 < count) sepCall();
		}
		return res;
	}

	std::vector<std::string> strings(Integer count, char separator = DEFAULT_SEPARATOR) {
		return strings<>(count, separator);
	}

	std::vector<std::string> strings(Integer lower, Integer upper, 
	                                 Integer count, char separator = DEFAULT_SEPARATOR) {
		return strings<Integer, Integer>(lower, upper, count, separator);
	}

	std::vector<std::string> strings(Integer lower, Integer upper, Constraint& constraint,
	                                 Integer count, char separator = DEFAULT_SEPARATOR) {
		return strings<Integer, Integer, Constraint&>(lower, upper, constraint, count, separator);
	}

	std::vector<std::string> strings(const std::regex& pattern,
	                                 Integer count, char separator = DEFAULT_SEPARATOR) {
		return strings<const std::regex&>(pattern, count, separator);
	}

	std::vector<std::string> strings(const std::regex& pattern, Integer lower, Integer upper,
	                                 Integer count, char separator = DEFAULT_SEPARATOR) {
		return strings<const std::regex&, Integer, Integer>(pattern, lower, upper, count, separator);
	}

	std::vector<std::string> strings(const std::regex& pattern, Integer lower, Integer upper, Constraint& constraint,
	                                 Integer count, char separator = DEFAULT_SEPARATOR) {
		return strings<const std::regex&, Integer, Integer, Constraint&>(pattern, lower, upper, constraint, count, separator);
	}

	Integer integer() {
		return parse<Integer>(string(INTEGER_REGEX));
	}

	Integer integer(Integer lower, Integer upper) {
		Integer res = integer();
		if (res < lower || res >= upper) {
			ValidateBase::juryOut << "Integer " << res << " out of range [" << lower << ", " << upper << ") ";
			fail();
		}
		return res;
	}

	Integer integer(Integer lower, Integer upper, Constraint& constraint) {
		Integer res = integer(lower, upper);
		constraint.log(lower, upper, res);
		return res;
	}

	template<typename... Args>
	std::vector<Integer> integers(Args... args, Integer count, char separator) {
		auto sepCall = checkSeparator(separator);
		std::vector<Integer> res(count);
		for (Integer i = 0; i < count; i++) {
			res[i] = integer(args...);
			if (i + 1 < count) sepCall();
		}
		return res;
	}

	std::vector<Integer> integers(Integer count, char separator = DEFAULT_SEPARATOR) {
		return integers<>(count, separator);
	}

	std::vector<Integer> integers(Integer lower, Integer upper,
	                              Integer count, char separator = DEFAULT_SEPARATOR) {
		return integers<Integer, Integer>(lower, upper, count, separator);
	}

	std::vector<Integer> integers(Integer lower, Integer upper, Constraint& constraint,
	                              Integer count, char separator = DEFAULT_SEPARATOR) {
		return integers<Integer, Integer, Constraint&>(lower, upper, constraint, count, separator);
	}

	// this does not allow NaN or Inf!
	// However, those should never be desired.
	Real real() {
		return parse<Real>(string(INTEGER_REGEX));
	}

	// we dont use EPS for bound checking! (this is supposed for input validation anyway)
	Real real(Real lower, Real upper) {
		Real res = real();
		if (std::isnan(res) || res < lower || res >= upper) {
			ValidateBase::juryOut << "Real " << res << " out of range [" << lower << ", " << upper << ") ";
			fail();
		}
		return res;
	}

	Real real(Real lower, Real upper, Constraint& constraint) {
		Real res = real(lower, upper);
		constraint.log(lower, upper, res);
		return res;
	}

	Real real(Real lower, Real upper, Integer minDecimals, Integer maxDecimals) {
		std::string t = string(STRICT_REAL_REGEX);
		auto dot = t.find('.');
		Integer decimals = dot == std::string::npos ? 0 : t.size() - dot - 1;
		if (decimals < minDecimals || decimals >= maxDecimals) {
			ValidateBase::juryOut << "Real " << t << " has wrong amount of decimals! ";
			fail();
			return 0;
		}
		try {
			Real res = parse<Real>(t);
			if (std::isnan(res) || res < lower || res >= upper) {
				ValidateBase::juryOut << "Real " << res << " out of range [" << lower << ", " << upper << ") ";
				fail();
			}
			return res;
		} catch(...) {
			ValidateBase::juryOut << "Could not parse token as real: " << t << " ";
			fail();
			return 0;
		}
	}

	Real real(Real lower, Real upper, Integer minDecimals, Integer maxDecimals, Constraint& constraint) {
		Real res = real(lower, upper, minDecimals, maxDecimals);
		constraint.log(lower, upper, res);
		return res;
	}

	template<typename... Args>
	std::vector<Real> reals(Args... args, Integer count, char separator) {
		auto sepCall = checkSeparator(separator);
		std::vector<Real> res(count);
		for (Integer i = 0; i < count; i++) {
			res[i] = real(args...);
			if (i + 1 < count) sepCall();
		}
		return res;
	}

	std::vector<Real> reals(Integer count, char separator = DEFAULT_SEPARATOR) {
		return reals<>(count, separator);
	}

	std::vector<Real> reals(Real lower, Real upper,
	                        Integer count, char separator = DEFAULT_SEPARATOR) {
		return reals<Real, Real>(lower, upper, count, separator);
	}

	std::vector<Real> reals(Real lower, Real upper, Constraint& constraint,
	                        Integer count, char separator = DEFAULT_SEPARATOR) {
		return reals<Real, Real, Constraint&>(lower, upper, constraint, count, separator);
	}

	std::vector<Real> reals(Real lower, Real upper, Integer minDecimals, Integer maxDecimals,
	                        Integer count, char separator = DEFAULT_SEPARATOR) {
		return reals<Real, Real, Integer, Integer>(lower, upper, minDecimals, maxDecimals, count, separator);
	}

	std::vector<Real> reals(Real lower, Real upper, Integer minDecimals, Integer maxDecimals, Constraint& constraint,
	                        Integer count, char separator = DEFAULT_SEPARATOR) {
		return reals<Real, Real, Integer, Integer, Constraint&>(lower, upper, minDecimals, maxDecimals, constraint, count, separator);
	}

	bool expectString(std::string_view expected_) {
		std::string seen = string();
		std::string expected = std::string(expected_);
		if (!case_sensitive) toLower(expected);
		return seen == expected;
	}

	bool expectInt(Integer expected) {
		Integer seen = integer();
		return seen == expected;
	}

	bool expectedReal(Real expected) {
		Real seen = real();
		return details::floatEqual(seen, expected, floatAbsTol, floatRelTol);
	}
private:
	void fail() {
		details::printCaller(ValidateBase::juryOut);
		//try to find input position...
		int line = 1, col = 0;
		in->clear();
		auto originalPos = in->tellg();
		in->seekg(0);
		if(originalPos >= 0 && in) {
			char c;
			while((in->tellg() < originalPos) && in->get(c)) {
				if(c == '\n') {
					line++;
					col = 0;
				} else {
					col++;
				}
			}
			ValidateBase::juryOut << "Input position: [" << line << "," << col << "]";
		}
		ValidateBase::juryOut << onFail;
	}
};


//============================================================================//
// Validators and stuff                                                       //
//============================================================================//
namespace ValidateBase {
	//OutputStream juryOut(std::cout);
	//OutputStream juryErr(std::cerr);
	CommandParser arguments;
	Real floatAbsTol = DEFAULT_EPS;
	Real floatRelTol = DEFAULT_EPS;

	// Real r2 is considered the reference value for relative error.
	bool floatEqual(Real given,
	                Real expected,
	                Real floatAbsTol_ = floatAbsTol,
	                Real floatRelTol_ = floatRelTol) {
		return details::floatEqual(given, expected, floatAbsTol_, floatRelTol_);
	}

	namespace details {
		void init(int argc, char** argv) {
			static bool initialized = false;
			judgeAssert(!initialized, "init(argc, argv) was called twice!");
			initialized = true;

			arguments = std::move(CommandParser(argc, argv));
			if (auto seed = arguments[SEED_COMMAND]) Random::seed(seed.asInteger());
			// parse default flags manually, since they dont use '--' prefix
			auto eps = arguments.getRaw(FLOAT_TOLERANCE);
			floatAbsTol = eps.asReal(floatAbsTol);
			floatRelTol = eps.asReal(floatRelTol);
			floatAbsTol = arguments.getRaw(FLOAT_ABSOLUTE_TOLERANCE).asReal(floatAbsTol);
			floatRelTol = arguments.getRaw(FLOAT_RELATIVE_TOLERANCE).asReal(floatRelTol);
		}
	}

} // namespace ValidateBase

//called as ./validator [arguments] < inputfile
namespace InputValidator {
	using namespace ValidateBase;

	InputStream testIn;
	ConstraintsLogger constraint;

	void init(int argc, char** argv) {
		ValidateBase::details::init(argc, argv);
		juryOut = std::move(OutputStream(std::cout));

		testIn = InputStream(std::cin, true, true, WA, floatAbsTol, floatRelTol);
		if (auto file = arguments[CONSTRAINT_COMMAND]) {
			constraint = std::move(ConstraintsLogger(file.asString()));
		}
	}

} // namespace InputValidator

//called as ./validator input judgeanswer feedbackdir < teamoutput
namespace OutputValidator {//TODO read floats with fixed width?
	using namespace ValidateBase;

	InputStream testIn;
	InputStream juryAns;
	InputStream teamAns;

	void init(int argc, char** argv) {
		ValidateBase::details::init(argc, argv);
		juryOut = std::move(OutputStream(std::filesystem::path(arguments[3]) / JUDGE_MESSAGE));
		
		testIn = std::move(InputStream(std::filesystem::path(arguments[1]), false, false, FAIL));
		juryAns = std::move(InputStream(std::filesystem::path(arguments[2]), false, false, FAIL));
		teamAns = std::move(InputStream(std::cin, !!arguments.getRaw(SPACE_SENSITIVE), !!arguments.getRaw(CASE_SENSITIVE), WA));
	}

} // namespace OutputValidator

//called as ./interactor input judgeanswer feedbackdir <> teamoutput
namespace Interactor {
	using namespace ValidateBase;

	OutputStream toTeam;
	InputStream testIn;
	InputStream fromTeam;

	void init(int argc, char** argv) {
		ValidateBase::details::init(argc, argv);
		juryOut = std::move(OutputStream(std::filesystem::path(arguments[3]) / JUDGE_MESSAGE));
		toTeam = std::move(OutputStream(std::cout));

		testIn = std::move(InputStream(std::filesystem::path(arguments[1]), false, false, FAIL));
		fromTeam = std::move(InputStream(std::cin, !!arguments.getRaw(SPACE_SENSITIVE), !!arguments.getRaw(CASE_SENSITIVE), WA));
	}

} // namespace Interactor

//called as ./generator [arguments]
namespace Generator {
	using namespace ValidateBase;

	OutputStream testOut;

	void init(int argc, char** argv) {
		ValidateBase::details::init(argc, argv);
		juryOut = std::move(OutputStream(std::cerr));
		testOut = std::move(OutputStream(std::cout));
	}

} // namespace Generator

//============================================================================//
// ctd like syntax...                                                         //
//============================================================================//
namespace ctd {
	namespace details {
		template<typename C, typename... Args>
		class TempReader final {
			C callable;
			std::tuple<Args...> args;
		public:
			constexpr TempReader(C callable_, Args... args_) : callable(callable_), args(args_...) {}

			TempReader(const TempReader&) = delete;
			TempReader(TempReader&&) = delete;
			TempReader& operator=(const TempReader&) = delete;
			TempReader& operator=(TempReader&&) = delete;

			friend InputStream& operator>>(InputStream& str, const TempReader& reader) {
				std::apply(reader.callable, std::tuple_cat(std::tie(str), reader.args));
				return str;
			}
		};

		template<typename... Args>
		constexpr auto integer(Args... args) {
			auto f = [](InputStream& str, auto... curArgs) {
				str.integer(curArgs...);
			};
			return details::TempReader(f, args...);
		}

		template<typename... Args>
		auto integerStore(Integer& res, Args... args) {
			auto f = [&res](InputStream& str, auto... curArgs) {
				res = str.integer(curArgs...);
			};
			return details::TempReader(f, args...);
		}

		template<typename... Args>
		constexpr auto real(Args... args) {
			auto f = [](InputStream& str, auto... curArgs) {
				str.real(curArgs...);
			};
			return details::TempReader(f, args...);
		}

		template<typename... Args>
		auto realStore(Real& res, Args... args) {
			auto f = [&res](InputStream& str, auto... curArgs) {
				res = str.real(curArgs...);
			};
			return details::TempReader(f, args...);
		}

		template<typename... Args>
		constexpr auto string(Args... args) {
			auto f = [](InputStream& str, auto... curArgs) {
				str.string(curArgs...);
			};
			return details::TempReader(f, args...);
		}

		template<typename... Args>
		auto stringStore(std::string& res, Args... args) {
			auto f = [&res](InputStream& str, auto... curArgs) {
				res = str.string(curArgs...);
			};
			return details::TempReader(f, args...);
		}

		template<typename... Args>
		constexpr auto integers(Args... args) {
			auto f = [](InputStream& str, auto... curArgs) {
				str.integers(curArgs...);
			};
			return details::TempReader(f, args...);
		}

		template<typename... Args>
		auto integersStore(std::vector<Integer>& res, Args... args) {
			auto f = [&res](InputStream& str, auto... curArgs) {
				res = str.integers(curArgs...);
			};
			return details::TempReader(f, args...);
		}

		template<typename... Args>
		constexpr auto reals(Args... args) {
			auto f = [](InputStream& str, auto... curArgs) {
				str.reals(curArgs...);
			};
			return details::TempReader(f, args...);
		}

		template<typename... Args>
		auto realsStore(std::vector<Real>& res, Args... args) {
			auto f = [&res](InputStream& str, auto... curArgs) {
				res = str.reals(curArgs...);
			};
			return details::TempReader(f, args...);
		}

		template<typename... Args>
		constexpr auto strings(Args... args) {
			auto f = [](InputStream& str, auto... curArgs) {
				str.strings(curArgs...);
			};
			return details::TempReader(f, args...);
		}

		template<typename... Args>
		auto stringsStore(std::vector<std::string>& res, Args... args) {
			auto f = [&res](InputStream& str, auto... curArgs) {
				res = str.strings(curArgs...);
			};
			return details::TempReader(f, args...);
		}
	}

	constexpr auto SPACE = details::TempReader([](InputStream& str){str.space();});
	constexpr auto NEWLINE = details::TempReader([](InputStream& str){str.newline();});
	constexpr auto ENDFILE = details::TempReader([](InputStream& str){str.eof();});

	constexpr auto INT() {
		return details::integer();
	}
	constexpr auto INT(Integer lower, Integer upper) {
		return details::integer(lower, upper);
	}
	auto INT(Integer lower, Integer upper, Constraint& constraint) {
		return details::integer(lower, upper, std::ref(constraint));
	}
	auto INT(Integer& res) {
		return details::integerStore(res);
	}
	auto INT(Integer lower, Integer upper, Integer& res) {
		return details::integerStore(res, lower, upper);
	}
	auto INT(Integer lower, Integer upper, Integer& res, Constraint& constraint) {
		return details::integerStore(res, lower, upper, std::ref(constraint));
	}

	constexpr auto REAL() {
		return details::real();
	}
	constexpr auto REAL(Real lower, Real upper) {
		return details::real(lower, upper);
	}
	constexpr auto REAL(Real lower, Real upper, Integer minDecimals, Integer maxDecimals) {
		return details::real(lower, upper, minDecimals, maxDecimals);
	}
	auto REAL(Real lower, Real upper, Constraint& constraint) {
		return details::real(lower, upper, std::ref(constraint));
	}
	auto REAL(Real lower, Real upper, Integer minDecimals, Integer maxDecimals, Constraint& constraint) {
		return details::real(lower, upper, minDecimals, maxDecimals, std::ref(constraint));
	}
	auto REAL(Real& res) {
		return details::realStore(res);
	}
	auto REAL(Real lower, Real upper, Real& res) {
		return details::realStore(res, lower, upper);
	}
	auto REAL(Real lower, Real upper, Integer minDecimals, Integer maxDecimals, Real& res) {
		return details::realStore(res, lower, upper, minDecimals, maxDecimals);
	}
	auto REAL(Real lower, Real upper, Real& res, Constraint& constraint) {
		return details::realStore(res, lower, upper, std::ref(constraint));
	}
	auto REAL(Real lower, Real upper, Integer minDecimals, Integer maxDecimals, Real& res, Constraint& constraint) {
		return details::realStore(res, lower, upper, minDecimals, maxDecimals, std::ref(constraint));
	}

	constexpr auto STRING() {
		return details::string();
	}
	constexpr auto STRING(Integer lower, Integer upper) {
		return details::string(lower, upper);
	}
	auto STRING(Integer lower, Integer upper, Constraint& constraint) {
		return details::string(lower, upper, std::ref(constraint));
	}
	auto STRING(const std::regex& pattern) {
		return details::string(std::cref(pattern));
	}
	auto STRING(const std::regex& pattern, Integer lower, Integer upper) {
		return details::string(std::cref(pattern), lower, upper);
	}
	auto STRING(const std::regex& pattern, Integer lower, Integer upper, Constraint& constraint) {
		return details::string(std::cref(pattern), lower, upper, std::ref(constraint));
	}
	auto STRING(std::string& res) {
		return details::stringStore(res);
	}
	auto STRING(Integer lower, Integer upper, std::string& res) {
		return details::stringStore(res, lower, upper);
	}
	auto STRING(Integer lower, Integer upper, std::string& res, Constraint& constraint) {
		return details::stringStore(res, lower, upper, std::ref(constraint));
	}
	auto STRING(const std::regex& pattern, std::string& res) {
		return details::stringStore(res, std::cref(pattern));
	}
	auto STRING(const std::regex& pattern, Integer lower, Integer upper, std::string& res) {
		return details::stringStore(res, std::cref(pattern), lower, upper);
	}
	auto STRING(const std::regex& pattern, Integer lower, Integer upper, std::string& res, Constraint& constraint) {
		return details::stringStore(res, std::cref(pattern), lower, upper, std::ref(constraint));
	}

	constexpr auto INTS(Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::integers(count, separator);
	}
	constexpr auto INTS(Integer lower, Integer upper, Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::integers(lower, upper, count, separator);
	}
	auto INTS(Integer lower, Integer upper, Constraint& constraint, Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::integers(lower, upper, std::ref(constraint), count, separator);
	}
	auto INTS(std::vector<Integer>& res, Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::integersStore(res, count, separator);
	}
	auto INTS(Integer lower, Integer upper, std::vector<Integer>& res, Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::integersStore(res, lower, upper, count, separator);
	}
	auto INTS(Integer lower, Integer upper, std::vector<Integer>& res, Constraint& constraint,
	          Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::integersStore(res, lower, upper, std::ref(constraint), count, separator);
	}

	constexpr auto REALS(Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::reals(count, separator);
	}
	constexpr auto REALS(Real lower, Real upper, Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::reals(lower, upper, count, separator);
	}
	constexpr auto REALS(Real lower, Real upper, Integer minDecimals, Integer maxDecimals,
	                     Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::reals(lower, upper, minDecimals, maxDecimals, count, separator);
	}
	auto REALS(Real lower, Real upper, Constraint& constraint, Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::reals(lower, upper, std::ref(constraint), count, separator);
	}
	auto REALS(Real lower, Real upper, Integer minDecimals, Integer maxDecimals, Constraint& constraint, Integer count,
	           char separator = DEFAULT_SEPARATOR) {
		return details::reals(lower, upper, minDecimals, maxDecimals, std::ref(constraint), count, separator);
	}
	auto REALS(std::vector<Real>& res, Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::realsStore(res, count, separator);
	}
	auto REALS(Real lower, Real upper, std::vector<Real>& res, Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::realsStore(res, lower, upper, count, separator);
	}
	auto REALS(Real lower, Real upper, Integer minDecimals, Integer maxDecimals, std::vector<Real>& res,
	           Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::realsStore(res, lower, upper, minDecimals, maxDecimals, count, separator);
	}
	auto REALS(Real lower, Real upper, std::vector<Real>& res, Constraint& constraint,
	           Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::realsStore(res, lower, upper, std::ref(constraint), count, separator);
	}
	auto REALS(Real lower, Real upper, Integer minDecimals, Integer maxDecimals, std::vector<Real>& res, Constraint& constraint,
	           Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::realsStore(res, lower, upper, minDecimals, maxDecimals, std::ref(constraint), count, separator);
	}

	constexpr auto STRINGS(Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::strings(count, separator);
	}
	constexpr auto STRINGS(Integer lower, Integer upper, Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::strings(lower, upper, count, separator);
	}
	auto STRINGS(Integer lower, Integer upper, Constraint& constraint,
	             Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::strings(lower, upper, std::ref(constraint), count, separator);
	}
	auto STRINGS(const std::regex& pattern, Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::strings(std::cref(pattern), count, separator);
	}
	auto STRINGS(const std::regex& pattern, Integer lower, Integer upper,
	             Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::strings(std::cref(pattern), lower, upper, count, separator);
	}
	auto STRINGS(const std::regex& pattern, Integer lower, Integer upper, Constraint& constraint,
	             Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::strings(std::cref(pattern), lower, upper, std::ref(constraint), count, separator);
	}
	auto STRINGS(std::vector<std::string>& res, Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::stringsStore(res, count, separator);
	}
	auto STRINGS(Integer lower, Integer upper, std::vector<std::string>& res,
	             Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::stringsStore(res, lower, upper, count, separator);
	}
	auto STRINGS(Integer lower, Integer upper, std::vector<std::string>& res, Constraint& constraint,
	             Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::stringsStore(res, lower, upper, std::ref(constraint), count, separator);
	}
	auto STRINGS(const std::regex& pattern, std::vector<std::string>& res,
	             Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::stringsStore(res, std::cref(pattern), count, separator);
	}
	auto STRINGS(const std::regex& pattern, Integer lower, Integer upper, std::vector<std::string>& res,
	             Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::stringsStore(res, std::cref(pattern), lower, upper, count, separator);
	}
	auto STRINGS(const std::regex& pattern, Integer lower, Integer upper, std::vector<std::string>& res, Constraint& constraint,
	             Integer count, char separator = DEFAULT_SEPARATOR) {
		return details::stringsStore(res, std::cref(pattern), lower, upper, std::ref(constraint), count, separator);
	}

} // namespace ctd

#endif
