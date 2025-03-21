#include <bits/stdc++.h>
#include "visualizer_svg.h"
using namespace Visualizer;

int main(int argc, char** argv) {
	Visualizer::init(argc, argv);

	Integer n, m;
	testIn >> n >> m;
	std::vector<Point> positions(n, {0, 0});
	for (auto& [x, y] : positions) testIn >> x >> y;

	Integer ps;
	testAns >> ps;
	for (Integer i = 0; i < ps; i++) {
		Integer k;
		testAns >> k;
		Polyline p;
		p.stroke = Stroke(lerp(RED, GREEN, i / (Real)std::max<Integer>(1, ps - 1)), 0.1);
		for (Integer j = 0; j < k; j++) {
			Integer x;
			testAns >> x;
			p.points.push_back(positions[x - 1]);
		}
		image << p << std::endl;
	}

	for (auto p : positions) {
		Circle c(p, 0.5);
		c.fill = Fill(BLUE);
		image << c << std::endl;
	}
}
