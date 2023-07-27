#include "Cell.h"
#include "Input/InputSystem.h"
#include "Renderer/ModelManager.h"
#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"
namespace cg
{
	void Cell::Reveal(int value)
	{
		if (value == 0) {
			//revealZero(m_pos.x, m_pos.y);
		}

		m_text->Create(cg::g_renderer, std::to_string(value), cg::Color{ 1, 1, 1, 1 });
		m_model = cg::g_manager.Get("empty.txt");

		if (m_bomb) {
			cg::g_audioSystem.PlayOneShot("hit", false);
			m_model = cg::g_manager.Get("bomb.txt");
			//
			//*m_restart = true;
		}
		else cg::g_audioSystem.PlayOneShot("success", false);
		m_revealed = true;
	}

	void Cell::Update(float dt)
	{
		Actor::Update(dt);
		if (cg::g_inputSystem.GetMouseButtonDown(0) && inRange() && !m_flagged && !m_revealed) {
			Reveal((bombsInRadius(m_pos.x, m_pos.y)));
		}
		if (cg::g_inputSystem.GetMouseButtonDown(2) && !cg::g_inputSystem.GetMousePreviousButtonDown(2) && inRange() && !m_revealed) {
			if (!m_flagged) {
				m_model = cg::g_manager.Get("flag.txt");
				cg::g_audioSystem.PlayOneShot("flag", false);
				m_flagged = true;
			}
			else {
				m_model = cg::g_manager.Get("box.txt");
				m_flagged = false;
			}
		}
	}

	bool Cell::inRange() {
		float spread = 10;
		return cg::g_inputSystem.GetMousePosition().x + spread >= m_transform.position.x
			&& cg::g_inputSystem.GetMousePosition().x - spread <= m_transform.position.x
			&& cg::g_inputSystem.GetMousePosition().y + spread >= m_transform.position.y
			&& cg::g_inputSystem.GetMousePosition().y - spread <= m_transform.position.y
			;
	}

	int Cell::bombsInRadius(int x, int y)
	{
		int total = 0;
		for (int i = x - 1; i <= x + 1; i++) {
			for (int j = y - 1; j <= y + 1; j++) {
				if (!(i == x && j == y) && i >= 0 && j >= 0 && i < 36 && j < 23 && matrix[j][i]) {
					total++;
				}
			}
		}
		return total;
	}

	void Cell::revealZero(int x, int y)
	{
		for (int i = x - 1; i <= x + 1; i++) {
			for (int j = y - 1; j <= y + 1; j++) {
				if (!(i == x && j == y) && i >= 0 && j >= 0 && i < 36 && j < 23 && matrix[j][i]) {
					//
				}
			}
		}
	}

	void Cell::Draw(cg::Renderer& renderer)
	{
		Actor::Draw(renderer);
		if (!m_bomb && m_revealed) m_text->Draw(renderer, m_transform.position.x - 7.5, m_transform.position.y - 7.5);
	}
}
