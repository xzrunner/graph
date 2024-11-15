#pragma once

#include <objcomp/Component.h>
#include <SM_Vector.h>

namespace graph
{

class EdgeStyle : public objcomp::Component
{
public:
	EdgeStyle(const sm::vec3& color) : m_color(color) {}

	virtual const char* Type() const override { return "edge_style"; }
	virtual objcomp::CompID TypeID() const override { return objcomp::GetCompTypeID<EdgeStyle>(); }
	virtual EdgeStyle* Clone() const override { return nullptr; }

	auto& GetColor() const { return m_color; }
	void SetColor(const sm::vec3& color) { m_color = color; }

private:
	sm::vec3 m_color;

}; // EdgeStyle

}