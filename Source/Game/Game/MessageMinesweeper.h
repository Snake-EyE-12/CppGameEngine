#pragma once
#include "Framework/Game.h"
#include <map>
#include "Core/Vector2.h"
#include "Cell.h"

namespace game
{
	class MessageMinesweeper : public Game
	{
	public:
		MessageMinesweeper() = default;
		bool Start() override;
		void Update() override;
		void Draw() override;
		void Clear() override;
		bool ShouldBomb(int x, int y);
		std::shared_ptr<cg::Model> GetBox(int x, int y);
		bool restart = false;
	private:
		std::map<cg::Vector2, cg::Cell> grid;
	};
}
