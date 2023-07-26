#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>

namespace cg
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const cg::Transform& transform) :
			m_transform{ transform }
		{}
		Actor(const cg::Transform& transform, std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model }
		{}

		virtual void Update(float dt);
		virtual void Draw(cg::Renderer& renderer);

		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }

		virtual void OnCollision(Actor* other) {}

		class Scene* m_scene = nullptr;
		friend class Scene;
		//friend class EmitterData;
		class Game* m_game = nullptr;
		cg::Transform m_transform;
		std::string m_tag;
		float m_lifespan = -1.0f;

	protected:
		bool m_destroyed = false;

		std::shared_ptr<Model> m_model;


	};
}