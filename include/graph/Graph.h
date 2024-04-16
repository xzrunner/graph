#pragma once

#include <objcomp/Object.h>

#include <vector>
#include <map>
#include <memory>

namespace graph
{

class Node;

class Graph : public objcomp::Object
{
public:
	Graph() {}

	void AddNode(const std::shared_ptr<Node>& node);
	void AddEdge(size_t f_node, size_t t_node);

	auto& GetNodes() const { return m_nodes; }
	auto& GetEdges() const { return m_edges; }

	void RemoveEdge(size_t f_node, size_t t_node);
	void ClearEdges(size_t node);

	void SetDirected(bool d) { m_directed = d; }
	bool IsDirected() const { return m_directed; }

private:
	std::vector<std::shared_ptr<Node>> m_nodes;
	std::multimap<size_t, size_t> m_edges;

	bool m_directed = true;

}; // Graph

}