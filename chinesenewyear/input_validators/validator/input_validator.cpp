#include "validate.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/planar_face_traversal.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include "is_straight_line_drawing.hpp"

using adj = boost::adjacency_list<boost::vecS,
								  boost::vecS,
								  boost::undirectedS,
								  boost::property<boost::vertex_index_t, Integer>,
								  boost::property<boost::edge_index_t, Integer>
								 >;
using vec_t = std::vector<boost::graph_traits<adj>::edge_descriptor>;

struct coord_t {
  Integer x, y;
};

using straight_line_drawing_storage_t = std::vector<coord_t>;
using straight_line_drawing_t = boost::iterator_property_map<straight_line_drawing_storage_t::iterator, 
															 boost::property_map<adj, boost::vertex_index_t>::type
															>;

int main(int argc, char **argv) {
	using namespace InputValidator;
	InputValidator::init(argc, argv);

	Integer n = testIn.integer(4, 100'001);
	testIn.space();
	Integer m = testIn.integer(5, 300'001);
	testIn.newline();

	std::vector<coord_t> pos;
	std::set<std::pair<Integer, Integer>> seenPos;
	for (Integer i = 0; i < n; i++) {
		Integer x = testIn.integer(0, 1000'000'001);
		testIn.space();
		Integer y = testIn.integer(0, 1000'000'001);
		testIn.newline();
		if (seenPos.find({x, y}) != seenPos.end()) juryOut << "Duplicate position: (" << x << "," << y << ")" << WA;
		pos.push_back({x, y});
		seenPos.insert({x, y});
	}


	adj g(n);
	std::vector<Integer> deg(n);
	std::vector<std::pair<Integer, Integer>> edgeList;
	for (Integer i = 0; i < m; i++) {
		Integer a = testIn.integer(1, n+1);
		testIn.space();
		Integer b = testIn.integer(1, n+1);
		testIn.newline();
		if (a == b) juryOut << "Selfloop: " << a << "<->" << a << WA;
		a--;
		b--;
		add_edge(a, b, g);
		deg[a]++;
		deg[b]++;
		if (a < b) std::swap(a, b);
		edgeList.push_back({a, b});
	}
	testIn.eof();

	std::sort(allOf(edgeList));
	for (Integer i = 0; i + 1 < m; i++) {
		if (edgeList[i] == edgeList[i + 1]) juryOut << "Multi-edge: " << edgeList[i].first << "<->" << edgeList[i].second << WA;
	}
	for (Integer i = 0; i < n; i++) {
		if (deg[i] == 0) juryOut << "unused vertex: " << i+1 << WA;
	}

	//Initialize the interior edge index
	using namespace boost;
	property_map<adj, edge_index_t>::type e_index = get(edge_index, g);
	graph_traits<adj>::edges_size_type edge_count = 0;
	graph_traits<adj>::edge_iterator ei, ei_end;
	for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
 		put(e_index, *ei, edge_count++);
	}

	std::vector<vec_t> embedding(n);
	if (!boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,
									  boyer_myrvold_params::embedding = &embedding[0])) {
		juryOut << "Graph not planar!" << WA;
	}

	straight_line_drawing_t straight_line_drawing(pos.begin(), get(vertex_index, g));
	if (!is_straight_line_drawing(g, straight_line_drawing)) {
		juryOut << "Embedding is not straight line!" << WA;
	}
	return AC;

}
