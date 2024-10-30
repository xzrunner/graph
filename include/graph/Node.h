#pragma once

#include <objcomp/Object.h>

#include <memory>
#include <vector>

namespace graph
{

class Node : public objcomp::Object
{
public:
	Node() {}

	void SetName(const std::string& name) { m_name = name; }
	auto& GetName() const { return m_name; }

	void SetValue(int val) { m_value = val; }
	int GetValue() const { return m_value; }

	void AddConnect(const std::shared_ptr<Node>& conn);
	void DelConnect(const std::shared_ptr<Node>& conn);
	auto& GetConnects() const { return m_conns; }

private:
	std::string m_name;
	int m_value = -1;

	std::vector<std::shared_ptr<Node>> m_conns;

}; // Node

}