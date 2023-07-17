#include "Enemy.h"
#include "Renderer/Renderer.h"

void Enemy::Update(float dt)
{

	cg::Vector2 forward = cg::Vector2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * cg::g_time.GetDeltaTime();

	m_transform.position.x = cg::Wrap(m_transform.position.x, (float)cg::g_renderer.getWidth());
	m_transform.position.y = cg::Wrap(m_transform.position.y, (float)cg::g_renderer.getHeight());

}
