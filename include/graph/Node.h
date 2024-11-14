#pragma once

#include <objcomp/Object.h>

#include <memory>
#include <vector>

namespace graph
{

class Edge;

class Node : public objcomp::Object
{
public:
	Node() {}
	~Node() {}

	void SetName(const std::string& name) { m_name = name; }
	auto& GetName() const { return m_name; }

	void SetValue(int val) { m_value = val; }
	int GetValue() const { return m_value; }

	bool AddEdge(const Edge* edge);
	bool DelEdge(const Edge* edge);
	auto& GetEdges() const { return m_edges; }
	void ClearEdges() { m_edges.clear(); }

private:
	std::string m_name;
	int m_value = -1;

	std::vector<const Edge*> m_edges;

}; // Node

}