#include "validate.h"
using namespace std;

struct event {
	Integer x, y1, y2, type, id;
	bool operator<(const event& o) const {
		if(x != o.x) return x < o.x;
		return type < o.type;
	}
};

struct seg {
	Integer y, type, id;
	bool operator<(const seg& o) const {
		if(y != o.y) return y < o.y;
		return type < o.type;
	}
};

int main(int argc, char** argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;

	Integer n = testIn.integer(1, 200001, constraint["n"]);
	testIn.newline();

	vector<event> events;
	for(Integer i = 0; i < n; i++) {
		Integer x1 = testIn.integer(0, 1000000000, constraint["x1"]);
		testIn.space();
		Integer y1 = testIn.integer(0, 1000000000, constraint["y1"]);
		testIn.space();
		Integer x2 = testIn.integer(1, 1000000001, constraint["x2"]);
		testIn.space();
		Integer y2 = testIn.integer(1, 1000000001, constraint["y2"]);
		testIn.newline();
		if(x1 >= x2) juryOut << "invalid corners i=" << i << WA;
		if(y1 >= y2) juryOut << "invalid corners i=" << i << WA;

		events.push_back({x1, y1, y2, 1, i});
		events.push_back({x2, y1, y2, -1, i});
	}
	testIn.eof();
	sort(events.begin(), events.end());
	set<seg> active;
	for(auto e : events) {
		seg lower = {e.y1, 1, e.id};
		seg upper = {e.y2, -1, e.id};
		if(e.type < 0) {
			active.erase(lower);
			active.erase(upper);
		} else {
			auto l = active.find(lower);
			auto r = active.find(upper);
			if(l != active.end()) juryOut << "intersection: " << e.id << " " << l->id << WA;
			if(r != active.end()) juryOut << "intersection: " << e.id << " " << r->id << WA;
			l = active.insert(lower).first;
			r = active.insert(upper).first;
			if(next(l) != r) juryOut << "intersection: " << e.id << " " << next(l)->id << WA;
			if (l != active.begin() && next(r) != active.end() && prev(l)->id == next(r)->id)
				juryOut << "intersection: " << e.id << " " << prev(l)->id << WA;
		}
	}
	return AC;
}
