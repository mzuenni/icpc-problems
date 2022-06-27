#pragma once

#include "mz_validate.h"
#include <cassert>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

struct marble {
	integer_t color, pos, runLength;
};

struct marbleRun : char_producer<marble> {
private:
	integer_t color, runLength;
public:
	marbleRun(integer_t _color, integer_t _runLength) : color(_color), runLength(_runLength) {}
	marbleRun() : marbleRun(0, 0) {}

	virtual void operator()(size_t start_pos, size_t len, marble* buffer) {
		for (integer_t i = 0; i < len; i++) {
			buffer[i] = {color, (integer_t)start_pos + i, runLength};
		}
	}
};

constexpr integer_t qLim = 200000;
constexpr integer_t updatesPerQuery = 7;
marbleRun runMemory[qLim * updatesPerQuery];
integer_t nextRun = 0;
struct marbles {
private:
	rope<marble> generateRun(integer_t color, integer_t runLength = 1) {
		assert(nextRun < qLim * updatesPerQuery);
		runMemory[nextRun] = marbleRun(color, runLength);
		rope<marble> res(&runMemory[nextRun], runLength, false);
		nextRun++;
		return res;
	}

	rope<marble> state;
	const integer_t maxRun = 0;
public:
	marbles(integer_t _maxRun) : maxRun(_maxRun) {
		state.append({-1, 0, 1});//guard
	}

	integer_t size() {
		return (integer_t)state.size() - 1;
	}

	void erase(integer_t pos) {
		if (pos < 0 || pos > size()) return;
		if (state[pos].runLength < maxRun) return;
		integer_t runLength = state[pos].runLength;
		pos -= state[pos].pos;
		state.erase(pos, runLength);
		if (pos > 0 && pos < size() && state[pos].color == state[pos-1].color) {
			//combine
			integer_t color = state[pos].color;
			runLength = state[pos].runLength + state[pos-1].runLength;
			pos = pos - 1 - state[pos - 1].pos;
			state.erase(pos, runLength);
			auto tmp = generateRun(color, runLength);
			state.insert(pos, tmp);
			erase(pos);
		}
	}

	void add(integer_t pos, integer_t color) {
		assert(pos >= 0 && pos <= size());

		if (pos > 0 && state[pos-1].color == color) pos--;

		integer_t otherLeft = state[pos].pos;
		integer_t otherPos = pos - otherLeft;
		integer_t otherlength = state[pos].runLength;
		integer_t otherColor = state[pos].color;

		state.erase(otherPos, otherlength);
		if (color == otherColor) {
			//append
			auto tmp = generateRun(color, otherlength + 1);
			state.insert(otherPos, tmp);
		} else {
			//split
			auto l = generateRun(otherColor, otherLeft);
			auto m = generateRun(color, 1);
			auto r = generateRun(otherColor, otherlength - otherLeft);
			state.insert(otherPos, r);
			state.insert(otherPos, m);
			state.insert(otherPos, l);
		}
		erase(pos);
	}

	integer_t operator[](integer_t p) {
		return state[p].color;
	}
};
