#include "Enemy.h"
#include "Player.h"
#include "Paddle.h"
#include "AstroidFighter.h"

#include "Framework/Scene.h"
#include "Renderer/Renderer.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	if (player) {
		cg::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + cg::HalfPi;
	}

	cg::Vector2 forward = cg::Vector2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * cg::g_time.GetDeltaTime();

	m_transform.position.x = cg::Wrap(m_transform.position.x, (float)cg::g_renderer.getWidth());
	m_transform.position.y = cg::Wrap(m_transform.position.y, (float)cg::g_renderer.getHeight());

	m_fireTimer -= dt;
	if (m_fireTimer <= 0) {
		m_fireTimer = m_fireRate;
		cg::Transform transform{m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Paddle> paddle = std::make_unique<Paddle>(400.0f, transform, m_model);
		paddle->m_tag = "Enemy";
		m_scene->Add(std::move(paddle));
	}

}

void Enemy::OnCollision(Actor* other)
{
	if (other->m_tag != m_tag) {
		m_game->AddPoints(100);
		m_destroyed = true;
	}
}
