#include "graph/Node.h"

namespace graph
{

void Node::AddConnect(const std::shared_ptr<Node>& conn)
{
	m_conns.push_back(conn);
}

}