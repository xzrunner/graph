#include "graph/Node.h"

namespace graph
{

bool Node::AddEdge(const Edge* edge)
{
	for (auto e : m_edges)
	{
		if (e == edge)
			return false;
	}

	m_edges.push_back(edge);

	return true;
}

bool Node::DelEdge(const Edge* edge)
{
	for (auto itr = m_edges.begin(); itr != m_edges.end(); ++itr)
	{
		if (*itr == edge)
		{
			m_edges.erase(itr);
			return true;
		}
	}

	return false;
}

}