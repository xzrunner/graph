#pragma once

#include <objcomp/Component.h>
#include <SM_Vector.h>

namespace graph
{

class NodePos : public objcomp::Component
{
public:
	NodePos(const sm::vec2& pos) : m_pos(pos) {}

	virtual const char* Type() const override { return "pos"; }
	virtual objcomp::CompID TypeID() const override { return objcomp::GetCompTypeID<NodePos>(); }
	virtual NodePos* Clone() const override { return nullptr; }

	auto& GetPos() const { return m_pos; }
	void SetPos(const sm::vec2& pos) { m_pos = pos; }

private:
	sm::vec2 m_pos;

}; // NodePos

}