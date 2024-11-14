#include "graph/Graph.h"
#include "graph/Node.h"
#include "graph/Edge.h"

#include <assert.h>

namespace graph
{

void Graph::AddNode(const std::shared_ptr<Node>& node)
{
	m_nodes.push_back(node);
}

std::shared_ptr<Edge> Graph::AddEdge(size_t f_node, size_t t_node)
{
	assert(f_node < m_nodes.size() && t_node < m_nodes.size());

	size_t n0 = f_node, n1 = t_node;
	if (!m_directed && n0 > n1) {
		std::swap(n0, n1);
	}

	EdgeKey key(n0, n1);
	auto itr = m_edges.find(key);
	if (itr != m_edges.end()) {
		return itr->second;
	}

	auto edge = std::make_shared<Edge>(m_nodes[n0].get(), m_nodes[n1].get());
	m_nodes[n0]->AddEdge(edge.get());
	m_nodes[n1]->AddEdge(edge.get());
	m_edges.insert({ key, edge });

	return edge;
}

const std::shared_ptr<Node> Graph::GetNode(size_t node) const
{
	return node >= m_nodes.size() ? nullptr : m_nodes[node];
}

void Graph::RemoveNode(size_t node)
{
	assert(node < m_nodes.size());

	m_nodes[node] = nullptr;
}

void Graph::RemoveEdge(size_t f_node, size_t t_node)
{
	assert(f_node < m_nodes.size() && t_node < m_nodes.size());

	auto itr = m_edges.find({f_node, t_node});
	if (itr == m_edges.end())
		return;

	auto edge = itr->second;
	const_cast<Node*>(edge->GetFromNode())->DelEdge(edge.get());
	const_cast<Node*>(edge->GetToNode())->DelEdge(edge.get());

	m_edges.erase(itr);
}

void Graph::ClearEdges(size_t node)
{
	assert(node < m_nodes.size());

	for (auto edge : m_nodes[node]->GetEdges())
	{
		int node2 = -1;
		for (int i = 0, n = m_nodes.size(); i < n; ++i)
		{
			if (m_nodes[i].get() == edge->GetToNode())
			{
				node2 = i;
				break;
			}
		}
		assert(node2 >= 0);

		auto itr = m_edges.find({node, node2});
		assert(itr != m_edges.end());
		m_edges.erase(itr);
	}

	m_nodes[node]->ClearEdges();
}

}