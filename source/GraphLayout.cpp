#include "graph/GraphLayout.h"
#include "graph/Graph.h"
#include "graph/Node.h"
#include "graph/NodeRank.h"

#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/energybased/StressMinimization.h>
#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/energybased/MultilevelLayout.h>
#include <ogdf/energybased/TutteLayout.h>
#include <ogdf/energybased/NodeRespecterLayout.h>
#include <ogdf/energybased/GEMLayout.h>
#include <ogdf/layered/SugiyamaLayout.h>
#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalHierarchyLayout.h>
#include <ogdf/layered/OptimalRanking.h>

namespace
{

void begin(const graph::Graph& graph, ogdf::Graph& G, ogdf::GraphAttributes& GA)
{
	std::vector<ogdf::node> o_nodes;

	auto& nodes = graph.GetNodes();
	for (int i = 0, n = nodes.size(); i < n; ++i)
	{
		auto& pos = nodes[i]->GetPos();
		auto v = G.newNode(i);
		o_nodes.push_back(v);
		GA.x(v) = (pos.x - 0.5) * 1024;
		GA.y(v) = (pos.y - 0.5) * 1024;
	}

	auto& edges = graph.GetEdges();
	for (auto& edge : edges)
	{
		G.newEdge(o_nodes[edge.first], o_nodes[edge.second]);
	}
}

void end(const graph::Graph& graph, const ogdf::Graph& G, const ogdf::GraphAttributes& GA)
{
	ogdf::List<ogdf::node> ogdf_nodes;
	G.allNodes(ogdf_nodes);
	auto& nodes = graph.GetNodes();
	for (ogdf::node v : ogdf_nodes)
	{
		float x = GA.x(v) / 1024 + 0.5;
		float y = 0.5 - GA.y(v) / 1024;
		nodes[v->index()]->SetPos({ x, y });
	}
}

}

namespace graph
{

void GraphLayout::StressMinimization(const Graph& graph)
{
	ogdf::Graph G;
	ogdf::GraphAttributes GA(G);

	begin(graph, G, GA);

	ogdf::StressMinimization stress;
	stress.call(GA);

	end(graph, G, GA);
}

void GraphLayout::GEM(const Graph& graph)
{
	ogdf::Graph G;
	ogdf::GraphAttributes GA(G);

	begin(graph, G, GA);

	ogdf::GEMLayout gem;
	gem.call(GA);

	end(graph, G, GA);
}

void GraphLayout::NodeRespecter(const Graph& graph)
{
	ogdf::Graph G;
	ogdf::GraphAttributes GA(G);

	begin(graph, G, GA);

	ogdf::NodeRespecterLayout nr;
	nr.call(GA);

	end(graph, G, GA);
}

void GraphLayout::FMMM(const Graph& graph)
{
	ogdf::Graph G;
	ogdf::GraphAttributes GA(G);

	begin(graph, G, GA);

	ogdf::FMMMLayout fmmm;
	fmmm.useHighLevelOptions(true);
	fmmm.unitEdgeLength(15.0);
	fmmm.newInitialPlacement(true);
	fmmm.qualityVersusSpeed(ogdf::FMMMOptions::QualityVsSpeed::GorgeousAndEfficient);
	fmmm.call(GA);

	end(graph, G, GA);
}

void GraphLayout::Multilevel(const Graph& graph)
{
	ogdf::Graph G;
	ogdf::GraphAttributes GA(G);

	begin(graph, G, GA);

	ogdf::MultilevelLayout multi;
	multi.call(GA);

	end(graph, G, GA);
}

void GraphLayout::OptimalHierarchy(const Graph& graph)
{
	ogdf::Graph G;
	ogdf::GraphAttributes GA(G);

	begin(graph, G, GA);

	ogdf::SugiyamaLayout SL;
	SL.setRanking(new ogdf::OptimalRanking);
	SL.setCrossMin(new ogdf::MedianHeuristic);

	ogdf::OptimalHierarchyLayout* ohl = new ogdf::OptimalHierarchyLayout;
	ohl->layerDistance(30.0);
	ohl->nodeDistance(25.0);
	ohl->weightBalancing(1.8);
	SL.setLayout(ohl);

	SL.call(GA);

	end(graph, G, GA);
}

void GraphLayout::HierarchyRanking(const Graph& graph)
{
	ogdf::Graph G;
	ogdf::GraphAttributes GA(G);

	begin(graph, G, GA);
	
	auto& nodes = graph.GetNodes();
	ogdf::NodeArray<int> rank(G);
	//for (int i = 0; i < nodes.size(); ++i) {
	//	rank[i] = nodes[i]->GetRank();
	//}
	int i = 0;
	for (ogdf::node v : G.nodes)
	{
		rank[v] = nodes[i++]->GetComponent<NodeRank>().GetRank();
	}

	ogdf::SugiyamaLayout SL;
	SL.setRanking(new ogdf::OptimalRanking);
	SL.setCrossMin(new ogdf::MedianHeuristic);

	ogdf::OptimalHierarchyLayout* ohl = new ogdf::OptimalHierarchyLayout;
	ohl->layerDistance(30.0);
	ohl->nodeDistance(25.0);
	ohl->weightBalancing(0.7);
	SL.setLayout(ohl);

	SL.call(GA, rank);

	end(graph, G, GA);
}

}