#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"

class Actor
{
public:
	Actor() = default;
	Actor(const cg::Transform& transform, const cg::Model& model) :
		m_transform{ transform },
		m_model{ model }
	{}

	virtual void Update(float dt) = 0;
	virtual void Draw(cg::Renderer& renderer);
protected:
	cg::Transform m_transform;
	cg::Model m_model;

};