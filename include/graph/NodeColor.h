#pragma once

#include <objcomp/Component.h>
#include <SM_Vector.h>

namespace graph
{

class NodeColor : public objcomp::Component
{
public:
	NodeColor(const sm::vec3& color) : m_color(color) {}

	virtual const char* Type() const override { return "color"; }
	virtual objcomp::CompID TypeID() const override { return objcomp::GetCompTypeID<NodeColor>(); }
	virtual NodeColor* Clone() const override { return nullptr; }

	auto& GetColor() const { return m_color; }
	void SetColor(const sm::vec3& color) { m_color = color; }

private:
	sm::vec3 m_color;

}; // NodeColor

}