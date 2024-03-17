#pragma once

#include <objcomp/Component.h>

namespace graph
{

class NodeRank : public objcomp::Component
{
public:
	NodeRank(int rank) : m_rank(rank) {}

	virtual const char* Type() const override { return "rank"; }
	virtual objcomp::CompID TypeID() const override { return objcomp::GetCompTypeID<NodeRank>(); }
	virtual NodeRank* Clone() const override { return nullptr; }

	void SetRank(int rank) { m_rank = rank; }
	auto GetRank() const { return m_rank; }

private:
	int m_rank = 0;

}; // NodeRank

}