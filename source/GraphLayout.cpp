#include "graph/GraphLayout.h"
#include "graph/Graph.h"
#include "graph/Node.h"
#include "graph/NodeRank.h"
#include "graph/NodePos.h"
#include "graph/Edge.h"

#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/basic/Logger.h>
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

#include <assert.h>

namespace
{

void begin(const graph::Graph& graph, ogdf::Graph& G, ogdf::GraphAttributes& GA)
{
	std::vector<ogdf::node> o_nodes;

	for (size_t i = 0, n = graph.GetNodesNum(); i < n; ++i)
	{
		auto node = graph.GetNode(i);
		if (node) 
		{
			if (!node->HasComponent<graph::NodePos>()) {
				node->AddComponent<graph::NodePos>(sm::vec2(0, 0));
			}
			auto& pos = node->GetComponent<graph::NodePos>().GetPos();
			auto v = G.newNode(i);
			o_nodes.push_back(v);
			GA.x(v) = pos.x * 1024;
			GA.y(v) = pos.y * 1024;
		}
		else
		{
			auto v = G.newNode(i);
			o_nodes.push_back(v);
		}
	}
	
	auto& edges = graph.GetEdges();
	for (auto& edge : edges)
	{
		auto& key = edge.first;
		G.newEdge(o_nodes[key.first], o_nodes[key.second]);
	}
}

void end(const graph::Graph& graph, const ogdf::Graph& G, const ogdf::GraphAttributes& GA)
{
	ogdf::List<ogdf::node> ogdf_nodes;
	G.allNodes(ogdf_nodes);
	for (ogdf::node v : ogdf_nodes)
	{
		auto node = graph.GetNode(v->index());
		if (!node) {
			continue;
		}

		float x = GA.x(v) / 1024;
		float y = 1.0 - GA.y(v) / 1024;
		node->GetComponent<graph::NodePos>().SetPos({ x, y });
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
	ogdf::Logger::globalLogLevel(ogdf::Logger::Level::Minor);

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
	
	ogdf::NodeArray<int> rank(G);
	//for (int i = 0; i < nodes.size(); ++i) {
	//	rank[i] = nodes[i]->GetRank();
	//}
	int i = 0;
	for (ogdf::node v : G.nodes)
	{
		rank[v] = graph.GetNode(i++)->GetComponent<NodeRank>().GetRank();
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