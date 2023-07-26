#include "AstroidFighter.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"
#include "Framework/Emitter.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"







bool AstroidFighter::Initialize()
{
	//UI
	m_font = std::make_shared<cg::Font>("Marlboro.ttf", 24);
	m_scoreText = std::make_unique<cg::Text>(m_font);
	m_scoreText->Create(cg::g_renderer, "Score: 0000", cg::Color{ 1, 1, 1, 1 });

	m_titleText = std::make_unique<cg::Text>(m_font);
	m_titleText->Create(cg::g_renderer, "Astroid Fighter", cg::Color{ 1, 1, 1, 1 });

	//Audio
	cg::g_audioSystem.AddAudio("hit", "boom.wav");

	//Scene
	m_scene = std::make_unique<cg::Scene>();

	
	


	return true;
}

void AstroidFighter::Shutdown()
{
}

void AstroidFighter::Update(float dt)
{
	
	switch (m_state)
	{
	case eState::Title:
		std::cout << m_state << std::endl;
		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
		}
		break;
	case eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case eState::StartLevel: {
		m_scene->RemoveAll();

		

		std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, cg::Pi, cg::Transform{ {400, 300}, 0, 5 }, cg::g_manager.Get("ship.txt"));
		player->m_tag = "Player";
		player->m_game = this;
		m_scene->Add(move(player));
		m_state = eState::Game;
		break;
	}
	case eState::Game:
		m_spawnTime += dt;
		if (m_spawnTime >= m_spawnRate) {
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(cg::randomf(100, 150), cg::Pi, cg::Transform{ {cg::random(800), cg::random(600)}, cg::randomf(cg::TwoPi), 6}, cg::g_manager.Get("astroid.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(move(enemy));
			m_spawnTime = 0;
		}
		if (cg::g_inputSystem.GetMouseButtonDown(0)) {

			//Particles
			cg::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0;
			data.angleRange = cg::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = cg::Color{ 1, 0, 0, 1 };

			cg::Transform transform{ { cg::g_inputSystem.GetMousePosition() }, 0, 1 };
			auto emitter = std::make_unique<cg::Emitter>(transform, data);
			emitter->m_lifespan = 1.0f;
			m_scene->Add(std::move(emitter));
		}
		break;
	case eState::PlayerDead:
		//Wait for seconds
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::StartLevel;
		break;
	case eState::GameOver:
		break;
	default:
		break;
	}
	
	m_scoreText->Create(cg::g_renderer, std::to_string(m_score), { 1, 1, 0, 1 });
	m_scene->Update(dt);
}

void AstroidFighter::Draw(cg::Renderer& renderer)
{
	if (m_state == eState::Title) m_titleText->Draw(renderer, 400, 300);
	m_scoreText->Draw(renderer, 40, 40);

	m_scene->Draw(renderer);
}



//#include "GameIncludes.h"
//#include "AstroidFighter.h"
//
//namespace game
//{
//	bool AstroidFighter::Start()
//	{
//		//Initialization
//		cg::MemoryTracker::Initialize();
//		cg::seedRandom((unsigned int)time(nullptr));
//		cg::setFilePath("assets");
//		cg::g_renderer.Initialize();
//		cg::g_renderer.CreateWindow("Window", 800, 600);
//		cg::g_inputSystem.Initialize();
//		cg::g_audioSystem.Initialize();
//
//		
//
//		//Audio
//		cg::g_audioSystem.AddAudio("hit", "boom.wav");
//
//		//Objects
//		std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, cg::Pi, cg::Transform{ {400, 300}, 0, 5 }, cg::g_manager.Get("ship.txt"));
//		player->m_tag = "Player";
//		m_scene.Add(move(player));
// 
// 
//		for (int i = 0; i < 10; i++) {
//			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(cg::randomf(100, 150), cg::Pi, cg::Transform{ {cg::random(800), cg::random(600)}, cg::randomf(cg::TwoPi), 6}, cg::g_manager.Get("astroid.txt"));
//			enemy->m_tag = "Enemy";
//			m_scene.Add(move(enemy));
//		}
// 
// 
//		//Start Loop
//		while (!m_quit) {
//			Update();
//			Draw();
//			Clear();
//		}
//		m_scene.RemoveAll();
//		return false;
//	}
//
//	void AstroidFighter::Update()
//	{
//		//ENGINE
//		cg::g_time.Tick();
//		cg::g_audioSystem.Update();
//		cg::g_inputSystem.Update();
//		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
//			m_quit = true;
//		}
//		//GAME
//		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !cg::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
//		{
//			cg::g_audioSystem.PlayOneShot("hit");
//		}
//		m_scene.Update(cg::g_time.GetDeltaTime());
//	}
//
//	void AstroidFighter::Draw()
//	{
//		cg::g_renderer.SetColor(0, 0, 0, 0);
//		cg::g_renderer.BeginFrame();
//		cg::g_renderer.SetColor(255, 255, 255, 0);
//
//		
//		text->Draw(cg::g_renderer, 10, 10);
//
//
//		m_scene.Draw(cg::g_renderer);
//	}
//
//	void AstroidFighter::Clear()
//	{
//		cg::g_renderer.EndFrame();
//	}
//}