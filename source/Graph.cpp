#include "graph/Graph.h"
#include "graph/Node.h"
#include "graph/Edge.h"

namespace graph
{

void Graph::AddNode(const std::shared_ptr<Node>& node)
{
	m_nodes.push_back(node);
}

void Graph::AddEdge(size_t f_node, size_t t_node)
{
	assert(f_node < m_nodes.size() && t_node < m_nodes.size());

	size_t n0 = f_node, n1 = t_node;
	if (!m_directed && n0 > n1) {
		std::swap(n0, n1);
	}

	auto range = m_edges.equal_range(n0);
	for (auto itr = range.first; itr != range.second; ++itr)
	{
		if (itr->second == n1)
			return;
	}

	m_edges.insert({ n0, n1 });
	m_nodes[n0]->AddConnect(m_nodes[n1]);
	m_nodes[n1]->AddConnect(m_nodes[n0]);
}

}