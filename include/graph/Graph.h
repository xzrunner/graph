#pragma once

#include <vector>
#include <memory>

namespace graph
{

class Node;

class Graph
{
public:
	Graph() {}

	void AddNode(const std::shared_ptr<Node>& node);
	void AddEdge(size_t f_node, size_t t_node);

	auto& GetNodes() const { return m_nodes; }

private:
	std::vector<std::shared_ptr<Node>> m_nodes;

}; // Graph

}