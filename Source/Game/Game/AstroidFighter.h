#pragma once
#include "Framework/Game.h"

namespace game
{
	class AstroidFighter : public Game
	{
	public:
		AstroidFighter() = default;
		bool Start() override;
		void Update() override;
		void Draw() override;
		void Clear() override;
	private:

	};
}
