#pragma once
#include "Framework/Actor.h"
class Paddle : public cg::Actor
{
public:
	Paddle(float speed, const cg::Transform& transform, std::shared_ptr<cg::Model> model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		m_lifespan = 2.0f;
	}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
private:
	float m_speed = 0;
};