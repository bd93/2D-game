#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <functional>

#include "Window.h"
#include "Shader.h"
#include "Objects/Object.h"
#include "Objects/Player.h"
#include "Objects/MeteoritePool.h"
#include "Game.h"


int main()
{
	std::unique_ptr<Game> game = std::make_unique<Game>();
	game->Init();

	while (game->Running())
	{
		game->Render();
		game->HandleEvents();
		game->Update();
	}

	return 0;
}