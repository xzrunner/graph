#pragma once

#include <objcomp/Object.h>

#include <vector>
#include <map>
#include <memory>

namespace graph
{

class Node;
class Edge;

class Graph : public objcomp::Object
{
public:
	Graph() {}

	void AddNode(const std::shared_ptr<Node>& node);
	std::shared_ptr<Edge> AddEdge(size_t f_node, size_t t_node);

	auto& GetEdges() const { return m_edges; }

	size_t GetNodesNum() const { return m_nodes.size(); }
	const std::shared_ptr<Node> GetNode(size_t node) const;

	void RemoveNode(size_t node);

	void RemoveEdge(size_t f_node, size_t t_node);
	void ClearEdges(size_t node);

	void SetDirected(bool d) { m_directed = d; }
	bool IsDirected() const { return m_directed; }

private:
	std::vector<std::shared_ptr<Node>> m_nodes;

	using EdgeKey = std::pair<size_t, size_t>;
	std::map<EdgeKey, std::shared_ptr<Edge>> m_edges;
	
	bool m_directed = true;

}; // Graph

}