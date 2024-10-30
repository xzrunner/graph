#include "graph/GraphTools.h"
#include "graph/Graph.h"
#include "graph/Node.h"
#include "graph/NodePos.h"

#include <SM_Calc.h>

namespace graph
{

std::shared_ptr<Node> GraphTools::QueryNode(const Graph& graph, const sm::vec2& pos)
{
	auto& nodes = graph.GetNodes();
	for (auto& node : nodes)
	{
		float dist = sm::dis_pos_to_pos(pos, node->GetComponent<NodePos>().GetPos());
		if (dist < FLT_EPSILON)
		{
			return node;
		}
	}

	return nullptr;
}

}