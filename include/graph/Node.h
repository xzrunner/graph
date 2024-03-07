#pragma once

#include <SM_Vector.h>

#include <memory>
#include <vector>

namespace graph
{

class Node
{
public:
	Node() {}
	Node(int id) : m_id(id) {}

	void SetId(int id) { m_id = id; }
	int GetId() const { return m_id; }

	void AddConnect(const std::shared_ptr<Node>& conn);
	auto& GetConnects() const { return m_conns; }

	auto& GetPos() const { return m_pos; }
	void SetPos(const sm::vec2& pos) { m_pos = pos; }

private:
	int m_id = 0;

	std::vector<std::shared_ptr<Node>> m_conns;

	sm::vec2 m_pos;

}; // Node

}