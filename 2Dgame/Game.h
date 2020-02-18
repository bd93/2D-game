#ifndef GAME_H
#define GAME_H

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#include <time.h>
#include "Window.h"
#include "Objects/MeteoritePool.h"
#include "Objects/Player.h"
#include "Helpers/ResourceManager.h"
#include "Objects/ParticleSystem.h"
#include "Interfaces/IEventListener.h"
#include "Renderers/SpriteRenderer.h"
#include "Helpers/DeltaTime.h"

class Game
{
public:
	Game();
	~Game();
	void Init();
	void HandleEvents();
	void Update();
	void Render();
	bool Running();
	void Quit();
	void CheckCollisions();
private:
	Window* m_Window;
	Player* m_Player;
	MeteoritePool* m_Meteorites;
	SpriteRenderer* m_SpriteRenderer;
	ParticleRenderer* m_ParticleRenderer;
	ParticleSystem* m_ParticleSystem;
	std::vector<IEventListener*> m_EventListeners;
	bool m_Running;
};

#endif
