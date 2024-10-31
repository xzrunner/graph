#include "graph/GraphTools.h"
#include "graph/Graph.h"
#include "graph/Node.h"
#include "graph/NodePos.h"

#include <SM_Calc.h>

namespace graph
{

const std::shared_ptr<Node> GraphTools::QueryNode(const Graph& graph, const sm::vec2& pos)
{
	for (size_t i = 0, n = graph.GetNodesNum(); i < n; ++i)
	{
		auto node = graph.GetNode(i);
		float dist = sm::dis_pos_to_pos(pos, node->GetComponent<NodePos>().GetPos());
		if (dist < FLT_EPSILON)
		{
			return node;
		}
	}

	return nullptr;
}

}