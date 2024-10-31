#pragma once

#include <SM_Vector.h>

#include <memory>

namespace graph
{

class Graph;
class Node;

class GraphTools
{
public:
	static const std::shared_ptr<Node> QueryNode(const Graph& graph, const sm::vec2& pos);

}; // GraphTools

}