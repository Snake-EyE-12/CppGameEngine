#include "Player.h"
#include "Input/InputSystem.h"

void Player::Update(float dt)
{

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

}
