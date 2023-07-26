#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

class AstroidFighter : public cg::Game
{
public:
	enum eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver
	};

public:
	virtual bool Initialize() override;

	virtual void Shutdown() override;

	virtual void Update(float dt) override;

	virtual void Draw(cg::Renderer& renderer) override;
	void SetState(eState state) { m_state = state; }
private:
	eState m_state = eState::Title;
	float m_spawnTime = 0.0f;
	float m_spawnRate = 3.0f;

	std::shared_ptr<cg::Font> m_font;
	std::unique_ptr<cg::Text> m_scoreText;
	std::unique_ptr<cg::Text> m_titleText;


};
