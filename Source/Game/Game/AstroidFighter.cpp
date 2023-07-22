#include "GameIncludes.h"
#include "AstroidFighter.h"

namespace game
{
	bool AstroidFighter::Start()
	{
		//Initialization
		cg::MemoryTracker::Initialize();
		cg::seedRandom((unsigned int)time(nullptr));
		cg::setFilePath("assets");
		cg::g_renderer.Initialize();
		cg::g_renderer.CreateWindow("Window", 800, 600);
		cg::g_inputSystem.Initialize();
		cg::g_audioSystem.Initialize();

		//UI
		std::shared_ptr<cg::Font> font = std::make_shared<cg::Font>("Marlboro.ttf", 24);
		std::unique_ptr<cg::Text> text = std::make_unique<cg::Text>(font);
		text->Create(cg::g_renderer, "Score", cg::Color{ 1, 1, 1, 1 });

		//Audio
		cg::g_audioSystem.AddAudio("hit", "boom.wav");

		//Objects
		std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, cg::Pi, cg::Transform{ {400, 300}, 0, 5 }, cg::g_manager.Get("ship.txt"));
		player->m_tag = "Player";
		m_scene.Add(move(player));
		for (int i = 0; i < 10; i++) {
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(cg::randomf(100, 150), cg::Pi, cg::Transform{ {cg::random(800), cg::random(600)}, cg::randomf(cg::TwoPi), 6}, cg::g_manager.Get("astroid.txt"));
			enemy->m_tag = "Enemy";
			m_scene.Add(move(enemy));
		}
		//Start Loop
		while (!m_quit) {
			Update();
			Draw();
			Clear();
		}
		m_scene.RemoveAll();
		return false;
	}

	void AstroidFighter::Update()
	{
		//ENGINE
		cg::g_time.Tick();
		cg::g_audioSystem.Update();
		cg::g_inputSystem.Update();
		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			m_quit = true;
		}
		//GAME
		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !cg::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			cg::g_audioSystem.PlayOneShot("hit");
		}
		m_scene.Update(cg::g_time.GetDeltaTime());
	}

	void AstroidFighter::Draw()
	{
		cg::g_renderer.SetColor(0, 0, 0, 0);
		cg::g_renderer.BeginFrame();
		cg::g_renderer.SetColor(255, 255, 255, 0);

		//text->Draw(cg::g_renderer, 400, 300);


		m_scene.Draw(cg::g_renderer);
	}

	void AstroidFighter::Clear()
	{
		cg::g_renderer.EndFrame();
	}
}
