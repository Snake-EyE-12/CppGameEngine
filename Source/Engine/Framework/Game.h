#pragma once
#include "GameIncludes.h"

namespace game
{
	class Game
	{
	public:
		Game() {}
		~Game() = default;
		virtual bool Start() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Clear() = 0;
	protected:
		cg::Scene m_scene;
		bool m_quit = false;
	};
}