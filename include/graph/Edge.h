#pragma once

#include <objcomp/Object.h>

namespace graph
{

class Node;

class Edge : public objcomp::Object
{
public:
	Edge() {}
	Edge(const Node* from, const Node* to)
		: m_from(from), m_to(to) {}

	auto GetFromNode() const { return m_from; }
	auto GetToNode() const { return m_to; }

private:
	const Node* m_from = nullptr;
	const Node* m_to = nullptr;

}; // Edge

}