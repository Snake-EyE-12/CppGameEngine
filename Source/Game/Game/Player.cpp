#include "Player.h"
#include "Input/InputSystem.h"
#include "Paddle.h"
#include "Framework/Scene.h"

void Player::Update(float dt)
{
	Actor::Update(dt);
	float rotate = 0;
	if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;

	m_transform.rotation += rotate * m_turnRate * dt;

	float thrust = 0;
	if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	cg::Vector2 forward = cg::Vector2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * thrust * m_speed * cg::g_time.GetDeltaTime();

	m_transform.position.x = cg::Wrap(m_transform.position.x, (float)cg::g_renderer.getWidth());
	m_transform.position.y = cg::Wrap(m_transform.position.y, (float)cg::g_renderer.getHeight());

	if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !cg::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
		cg::Transform transform{m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Paddle> paddle = std::make_unique<Paddle>(400.0f, transform, m_model);
		paddle->m_tag = "Player";
		m_scene->Add(std::move(paddle));
	}
	
}

void Player::OnCollision(Actor* other)
{
	if (other->m_tag != m_tag) {
		m_health -= 10;
	}
	if (m_health <= 0) m_destroyed = true;
}
