#include "Game.h"

Game::Game()
	: m_Window(nullptr), m_Player(nullptr), m_Meteorites(nullptr),
	m_Running(true), m_SpriteRenderer(nullptr), m_ParticleRenderer(nullptr), m_ParticleSystem(nullptr)
{
}

Game::~Game()
{
	delete m_Window, m_Player, m_Meteorites, m_SpriteRenderer, m_ParticleRenderer, m_ParticleSystem;
}

void Game::Init()
{
	m_Window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "2DGame");
	m_Window->Init();

	// adding shaders and textures to std::map after "glad" has been initialised inside m_Window->Init()
	ResourceManager::AddLoadedShader("SpriteShader", Shader("Shaders/sprite_vertex.shader", "Shaders/sprite_fragment.shader"));
	ResourceManager::AddLoadedShader("ParticleShader", Shader("Shaders/particle_vertex.shader", "Shaders/particle_fragment.shader"));
	ResourceManager::AddLoadedTexture("Spacecraft", Texture("Textures/spacecraft.png"));
	ResourceManager::AddLoadedTexture("Meteorite", Texture("Textures/meteorite.png"));
	ResourceManager::AddLoadedTexture("LaserBeam", Texture("Textures/laser_beam.png"));

	m_Player = new Player(glm::vec2((float)((m_Window->GetWidth() / 2) - 40.0f), 0.0f), glm::vec2(80.0f, 80.0f));
	m_Meteorites = new MeteoritePool();
	m_SpriteRenderer = new SpriteRenderer(ResourceManager::GetLoadedShader("SpriteShader"));
	m_ParticleRenderer = new ParticleRenderer(ResourceManager::GetLoadedShader("ParticleShader"));
	m_ParticleSystem = new ParticleSystem();
	m_EventListeners.push_back(m_Player);
	srand(time(0));
}

void Game::HandleEvents()
{
	for (IEventListener* eventListener : m_EventListeners)
	{
		eventListener->HandleEvent();
	}
}

void Game::Update()
{
	DeltaTime::CalculateDeltaTime();

	if ((int)DeltaTime::m_CurrentTime >= DeltaTime::m_SecondsChecker)
	{
		m_Meteorites->Add(Meteorite(glm::vec2(RandomGenerator::GetFloat(0, 770), 600), glm::vec2(30, 30)));
		// initial value of m_SecondsChecker is 0
		DeltaTime::m_SecondsChecker += m_Meteorites->GetSpawnFrequency();
	}

	this->CheckCollisions();

	m_ParticleSystem->Update(0.01f);
}

void Game::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// render objects
	ResourceManager::GetLoadedShader("SpriteShader").use();
	m_Player->Render(*m_SpriteRenderer, &ResourceManager::GetLoadedTexture("Spacecraft"));
	m_Meteorites->Render(*m_SpriteRenderer, &ResourceManager::GetLoadedTexture("Meteorite"));
	ResourceManager::GetLoadedShader("ParticleShader").use();
	m_ParticleSystem->Render(*m_ParticleRenderer); // particles without texture

	glfwSwapBuffers(m_Window->GetWindow());
	glfwPollEvents();
}

bool Game::Running()
{
	if (glfwWindowShouldClose(m_Window->GetWindow()))
		m_Running = false;
	return m_Running;
}

void Game::Quit()
{
	m_Running = false;
}

void Game::CheckCollisions()
{
	std::vector<Object>& bullets = m_Player->GetWeapon().GetBullets();
	std::vector<Meteorite>& meteorites = m_Meteorites->GetMeteorites();

	for (int i = 0; i < bullets.size(); ++i)
	{
		for (int j = 0; j < meteorites.size(); ++j)
		{
			if ((bullets[i].GetPosition().y + bullets[i].GetSize().y) >= meteorites[j].GetPosition().y &&
				bullets[i].GetPosition().x >= meteorites[j].GetPosition().x && 
				bullets[i].GetPosition().x <= meteorites[j].GetPosition().x + meteorites[j].GetSize().x)
			{
				bool& destroyed = meteorites[j].IsDestroyed();
				destroyed = true;

				Particle particle;
				particle.position = glm::vec2((meteorites[j].GetPosition().x + (meteorites[j].GetSize().x / 2)), (meteorites[j].GetPosition().y + (meteorites[j].GetSize().y / 2)));
				particle.size = glm::vec2(5, 5);
				particle.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
				particle.available = true;
				particle.lifeTime = 2.0f;
				// emit 10 particles after meteorite destruction
				for (int i = 0; i < 10; ++i)
				{
					m_ParticleSystem->Emit(particle);
				}
			}
		}
	}
}
