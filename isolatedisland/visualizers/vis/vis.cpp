#include "visualizer_svg.h"
#include <map>
using namespace std;

int main(int argc, char **argv) {
	Visualizer::init();
	using namespace Visualizer;

	Integer n;
	testIn >> n;
	for (Integer i = 0; i < n; i++) {
		Integer a, b, c, d;
		testIn >> a >> b >> c >> d;
		Line l(Point(a, b), Point(c, d));
		l.stroke = Stroke(BLACK, 1, false);
		l.stroke->linecap = Linecap::ROUND;
		image << l << std::endl;
	}
	Real d = std::max(image.dimension.width, image.dimension.height) * 0.01;
	image.origin.x -= d;
	image.origin.y -= d;
	image.dimension.width += 2*d;
	image.dimension.height += 2*d;
}
