#include <iostream>
#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include <vector>
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;


int main(int argc, char* argv[])
{


	//INIT
	cg::seedRandom((unsigned int)time(nullptr));
	cg::setFilePath("assets");
	cg::g_renderer.Initialize();
	cg::g_renderer.CreateWindow("Window", 800, 600);
	cg::g_inputSystem.Initialize();
	cg::g_audioSystem.Initialize();




	cg::Model astroid;
	astroid.Load("astroid.txt");



	cg::Model ship;
	ship.Load("ship.txt");
	Player player{ 200, cg::Pi, { {400, 300}, 0, 5 }, ship };
	std::vector<Enemy> enemies;
	for (int i = 0; i < 10; i++) {
		Enemy enemy{ 300, cg::Pi, { {cg::random(800), cg::random(600)}, cg::randomf(cg::TwoPi), 6}, astroid};
		enemies.push_back(enemy);
	}

	//GAME

	bool quit = false;
	while (!quit) {


		//ENGINE
		cg::g_time.Tick();
		cg::g_audioSystem.Update();
		cg::g_inputSystem.Update();
		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		//SOUNDS
		cg::g_audioSystem.AddAudio("hit", "boom.wav");
		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			cg::g_audioSystem.PlayOneShot("hit");
		}



		//GAME
		player.Update(cg::g_time.GetDeltaTime());
		for (Enemy& enemy : enemies) {
			enemy.Update(cg::g_time.GetDeltaTime());
		}


		//DRAW
		cg::g_renderer.SetColor(0, 0, 0, 0);
		cg::g_renderer.BeginFrame();
		cg::g_renderer.SetColor(255, 255, 255, 0);


		player.Draw(cg::g_renderer);
		for (Enemy& enemy : enemies) {
			enemy.Draw(cg::g_renderer);
		}




		//CLEAR
		cg::g_renderer.EndFrame();
	}



	return 0;
}
