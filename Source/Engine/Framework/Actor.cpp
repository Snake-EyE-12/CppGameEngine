#include "Actor.h"

namespace cg
{
	void Actor::Update(float dt) {
		if (m_lifespan != -1.0f) {
			m_lifespan -= dt;
			if (m_lifespan <= 0) {
				m_destroyed = true;
			}
		}
	}
	void Actor::Draw(cg::Renderer& renderer) {
		m_model->Draw(renderer, m_transform);
	}
}
