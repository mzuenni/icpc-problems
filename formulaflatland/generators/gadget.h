#include "validate.h"
#include "graph_gen.h"

#ifndef GADGET_H
#define GADGET_H

using EdgeList = std::vector<std::pair<long long, long long>>;

Graph<NoData> toGraph(const std::vector<std::pair<long long, long long>>& edges) {
	long long n = 0;
	for (auto e : edges) {
		n = std::max(n, e.first + 1);
		n = std::max(n, e.second + 1);
	}
	Graph<NoData> res(n);
	for (auto e : edges) {
		res.addEdge(e.first, e.second);
	}
	return res;
}

const Graph<NoData> platon3 = toGraph({{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}});
const Graph<NoData> platon4 = toGraph({{0,1},{0,2},{0,4},{1,3},{1,5},{2,3},{2,6},{3,7},{4,5},{4,6},{5,7},{6,7}});
const Graph<NoData> platon5 = toGraph({{0,1},{1,2},{2,3},{3,4},{4,0},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,5},{15,16},{16,17},{17,18},{18,19},{19,15},{0,5},{1,7},{2,9},{3,11},{4,13},{6,15},{8,16},{10,17},{12,18},{14,19}});

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/make_connected.hpp>
#include <boost/graph/make_biconnected_planar.hpp>
#include <boost/graph/make_maximal_planar.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <boost/graph/planar_canonical_ordering.hpp>
#include <boost/graph/is_straight_line_drawing.hpp>
#include <boost/graph/chrobak_payne_drawing.hpp>

struct coord {
	Integer x, y;
};

using adj = boost::adjacency_list<boost::vecS,
								  boost::vecS,
								  boost::undirectedS,
								  boost::property<boost::vertex_index_t, Integer>,
								  boost::property<boost::edge_index_t, Integer>
								 >;
using vec_t = std::vector<boost::graph_traits<adj>::edge_descriptor>;


void printPlanar(Graph<NoData>& orig) {
	using namespace Generator;
	orig.setMinId(0);
	Integer n = orig.nodeCount();

	using namespace boost;

	adj g(n);
	for (auto e : orig.getEdges()) add_edge(e.from, e.to, g);

	//Initialize the interior edge index
	property_map<adj, edge_index_t>::type e_index = get(edge_index, g);
	graph_traits<adj>::edges_size_type edge_count = 0;
	graph_traits<adj>::edge_iterator ei, ei_end;
	for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
		put(e_index, *ei, edge_count++);
	}
//juryErr << "make connected" << std::endl;
	make_connected(g);
	edge_count = 0;
	for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
		put(e_index, *ei, edge_count++);
	}
//juryErr << "check planarity" << std::endl;
	std::vector<vec_t> embedding(n);
	if (!boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,
									  boyer_myrvold_params::embedding = &embedding[0])) {
		juryErr << "Graph is not planar (Generator Fail)!" << FAIL;
	}
//juryErr << "make biconnecte" << std::endl;
	make_biconnected_planar(g, &embedding[0]);
	edge_count = 0;
	for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
		put(e_index, *ei, edge_count++);
	}
//juryErr << "check planarity" << std::endl;
	boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,
								 boyer_myrvold_params::embedding = &embedding[0]);
//juryErr << "make maximal planar" << std::endl;
	make_maximal_planar(g, &embedding[0]);
	edge_count = 0;
	for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
		put(e_index, *ei, edge_count++);
	}
//juryErr << "check planarity" << std::endl;
	boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,
								 boyer_myrvold_params::embedding = &embedding[0]);
//juryErr << "find ordering" << std::endl;
	// Find a canonical ordering
	std::vector<graph_traits<adj>::vertex_descriptor> ordering;
	planar_canonical_ordering(g, &embedding[0], back_inserter(ordering));

	using straight_line_drawing_t = iterator_property_map<std::vector<coord>::iterator, 
														  property_map<adj, vertex_index_t>::type 
														 >;

	std::vector<coord> straight_line_drawing_storage(n);
	straight_line_drawing_t straight_line_drawing(straight_line_drawing_storage.begin(), 
												  get(vertex_index, g)
												 );
//juryErr << "find straight line" << std::endl;
	// Compute the straight line drawing
	chrobak_payne_straight_line_drawing(g, 
										embedding, 
										ordering.begin(),
										ordering.end(),
										straight_line_drawing
									   );
//juryErr << "verify straight line" << std::endl;//this has precision issues ):
//	if (!is_straight_line_drawing(g, straight_line_drawing)) {
//		juryErr << "Embedding is not straight line (Generator Fail)!" << FAIL;
//	}
//juryErr << "finished" << std::endl;

	orig.setMinId(1);
	testOut << orig.nodeCount() << " " << orig.edgeCount() << std::endl;
	for (int i = 0; i < n; i++) {
		testOut << straight_line_drawing_storage[i].x << " " << straight_line_drawing_storage[i].y << std::endl;
	}
	for (auto e : orig.getEdges()) testOut << e << std::endl;

}

#endif
