#include "MessageMinesweeper.h"
namespace game
{
	bool MessageMinesweeper::Start()
	{
		cg::MemoryTracker::Initialize();
		cg::seedRandom((unsigned int)time(nullptr));
		cg::setFilePath("assets");
		cg::g_renderer.Initialize();
		cg::g_renderer.CreateWindow("Just A Normal Minesweeper", 800, 600);
		cg::g_inputSystem.Initialize();
		cg::g_audioSystem.Initialize();

		//Audio
		cg::g_audioSystem.AddAudio("hit", "boom.wav");
		cg::g_audioSystem.AddAudio("flag", "flagPick.wav");
		cg::g_audioSystem.AddAudio("success", "low.wav");
		int width = 36;
		int height = 23;
		float centerScale = 20;
		float boxScale = 2;
		cg::Vector2 offset(50, 100);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				std::unique_ptr<cg::Cell> cell = std::make_unique<cg::Cell>(&restart, cg::Vector2{i, j}, ShouldBomb(i, j), cg::Transform{ {i* centerScale + offset.x, j* centerScale + offset.y}, 0, boxScale}, GetBox(i,j));
				m_scene.Add(move(cell));
			}
		}

		//Start Loop
		while (!m_quit && !restart) {
			//std::cout << restart << " " << m_quit << std::endl;
			Update();
			Draw();
			Clear();
		}
		cg::g_renderer.Shutdown();
		m_scene.RemoveAll();
		return restart;

	}
	bool MessageMinesweeper::ShouldBomb(int x, int y) {
		return cg::Cell::matrix[y][x];
	}
	std::shared_ptr<cg::Model> MessageMinesweeper::GetBox(int x, int y) {
		return ((x == 30 && y == 20)
			|| (x == 32 && y == 4)) ? cg::g_manager.Get("glowBox.txt") : cg::g_manager.Get("box.txt");
	}
	
	

	void MessageMinesweeper::Update()
	{
		//ENGINE
		cg::g_time.Tick();
		cg::g_audioSystem.Update();
		cg::g_inputSystem.Update();
		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			m_quit = true;
		}
		//GAME
		//std::cout << cg::g_inputSystem.GetMousePosition().x << " " << cg::g_inputSystem.GetMousePosition().y << std::endl;
		
		m_scene.Update(cg::g_time.GetDeltaTime());
	}
	void MessageMinesweeper::Draw()
	{
		cg::g_renderer.SetColor(0, 0, 0, 0);
		cg::g_renderer.BeginFrame();
		cg::g_renderer.SetColor(255, 255, 255, 0);

		m_scene.Draw(cg::g_renderer);
	}
	void MessageMinesweeper::Clear()
	{
		cg::g_renderer.EndFrame();
	}
}


//The Murder Suspect Will End Up In Court, Just Not This One.