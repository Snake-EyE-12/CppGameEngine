#include "Paddle.h"

void Paddle::Update(float dt)
{
	Actor::Update(dt);

	cg::Vector2 forward = cg::Vector2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * cg::g_time.GetDeltaTime();

	m_transform.position.x = cg::Wrap(m_transform.position.x, (float)cg::g_renderer.getWidth());
	m_transform.position.y = cg::Wrap(m_transform.position.y, (float)cg::g_renderer.getHeight());
}

void Paddle::OnCollision(Actor* other)
{
	if (other->m_tag != m_tag) {
		m_destroyed = true;
	}
}
