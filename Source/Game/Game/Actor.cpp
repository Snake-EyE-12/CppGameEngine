#include "Actor.h"


void Actor::Draw(cg::Renderer& renderer) {
	m_model.Draw(renderer, m_transform);
}
