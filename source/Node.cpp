#include "graph/Node.h"

namespace graph
{

void Node::AddConnect(const Node* conn)
{
	m_conns.push_back(conn);
}

void Node::DelConnect(const Node* conn)
{
	for (auto itr = m_conns.begin(); itr != m_conns.end(); )
	{
		if (*itr == conn)
			itr = m_conns.erase(itr);
		else
			++itr;
	}
}

}