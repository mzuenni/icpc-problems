#include "validate.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/planar_face_traversal.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include "is_straight_line_drawing.hpp"
using namespace std;

using namespace ctd;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

using adj = boost::adjacency_list<boost::vecS,
								  boost::vecS,
								  boost::undirectedS,
								  boost::property<boost::vertex_index_t, Integer>,
								  boost::property<boost::edge_index_t, Integer>
								 >;
using vec_t = vector<boost::graph_traits<adj>::edge_descriptor>;

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

	Integer n, m;
	testIn >> INT(4, 100001, n) >> SPACE >> INT(6, 300001, m) >> NEWLINE;
	vector<coord_t> pos;
	set<pair<Integer, Integer>> seenPos;
	for (Integer i = 0; i < n; i++) {
		Integer x, y;
		testIn >> INT(0, 1000000001, x) >> SPACE >> INT(0, 1000000001, y) >> NEWLINE;
		if (x == y) 
		if (seenPos.find({x, y}) != seenPos.end()) juryOut << "Duplicate position: (" << x << "," << y << ")" << WA;
		pos.push_back({x, y});
		seenPos.insert({x, y});
	}


	adj g(n);
	vector<Integer> deg(n);
	vector<pair<Integer, Integer>> edgeList;
	for (Integer i = 0; i < m; i++) {
		Integer a, b;
		testIn >> INT(1, n+1, a) >> SPACE >> INT(1, n+1, b) >> NEWLINE;
		if (a == b) juryOut << "Selfloop: " << a << "<->" << a << WA;
		a--;
		b--;
		add_edge(a, b, g);
		deg[a]++;
		deg[b]++;
		if (a < b) swap(a, b);
		edgeList.push_back({a, b});
	}
	testIn >> ENDFILE;
	sort(all(edgeList));
	for (Integer i = 0; i + 1 < m; i++) {
		if (edgeList[i] == edgeList[i + 1]) juryOut << "Multi-edge: " << edgeList[i].first << "<->" << edgeList[i].second << WA;
	}
	for (Integer i = 0; i < n; i++) {
		if (deg[i] <= 2) juryOut << "Min-degree too small: " << i+1 << WA;
	}

	//Initialize the interior edge index
	using namespace boost;
	property_map<adj, edge_index_t>::type e_index = get(edge_index, g);
	graph_traits<adj>::edges_size_type edge_count = 0;
	graph_traits<adj>::edge_iterator ei, ei_end;
	for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
 		put(e_index, *ei, edge_count++);
	}

	vector<vec_t> embedding(n);
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
