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
	if (f_node < m_nodes.size() && t_node < m_nodes.size()) 
	{
		m_nodes[f_node]->AddConnect(m_nodes[t_node]);
	}
}

}