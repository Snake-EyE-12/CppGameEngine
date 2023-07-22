#pragma once
#include "Framework/Actor.h"
#include "Renderer/Text.h"
class Player : public cg::Actor
{
public:
	Player(float speed, float turnRate, const cg::Transform& transform, std::shared_ptr<cg::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
	cg::Text m_text;
private:
	float m_speed = 0;
	float m_turnRate = 0;
	int m_health = 100;
};