#ifndef GAME_H
#define GAME_H

#include "MeteoritePool.h"
#include "Player.h"
#include "ResourceManager.h"

class Game
{
private:
	// renderer
	SpriteRenderer m_spriteRenderer;
	// resource manager (for shaders)
	ResourceManager m_resourceManager;
	// game objects
	Player m_player;
	MeteoritePool m_meteorites;

	// for speed correction
	float m_deltaTime;
public:
	void addShader(std::string shaderName, Shader shader)
	{
		m_resourceManager.addToMap(shaderName, shader);
	}
	void setRenderer(std::string shaderName)
	{
		Shader shader = m_resourceManager.getLoadedShader(shaderName);
		m_spriteRenderer = SpriteRenderer(shader);
	}
	void setDeltaTime(float delta)
	{
		m_deltaTime = delta;
	}
	void drawGameObjects()
	{
		m_player.draw(m_spriteRenderer);

		float time = glfwGetTime();
		static float checkTime = (float)m_meteorites.getSpawnFrequency();
		if (time > checkTime)
		{
			m_meteorites.add_to_pool(
				Object(glm::vec2(rand() % MAX_RANDOM, 600),  // position
				glm::vec2(30, 30),						   // size
				Texture("Textures/meteorite.png"),		   // texture
				glm::vec2(0, 3))						   // velocity
			);				     
			checkTime += 1;
		}

		m_meteorites.drawMeteorites(m_spriteRenderer, m_deltaTime);

		if (!m_player.getWeapon().getBullets().empty())
			m_player.getWeapon().drawBullets(m_spriteRenderer, m_deltaTime);
	}
	void checkCollisions()
	{
		std::vector<Object>& bullets = m_player.getWeapon().getBullets();
		std::vector<Object>& meteorites = m_meteorites.getMeteorites();

		for (int i = 0; i < bullets.size(); i++)
		{
			for (int j = 0; j < meteorites.size(); j++)
			{
				if ((bullets[i].getPosition().y + bullets[i].getSize().y) >= meteorites[j].getPosition().y && 
					bullets[i].getPosition().x >= meteorites[j].getPosition().x && 
					bullets[i].getPosition().x <= meteorites[j].getPosition().x + meteorites[j].getSize().x)
				{
					meteorites[j].setDestroyed(true);
				}
			}
		}
	}
	void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		if (glfwGetKey(window, GLFW_KEY_A))
			m_player.move(m_deltaTime * 70.0f, "left");
		if (glfwGetKey(window, GLFW_KEY_D))
			m_player.move(m_deltaTime * 70.0f, "right");
	}
	void handleKeyPress(int key, int action)
	{
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
			m_player.fireLaserBeam(m_spriteRenderer);
	}
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Game* game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
		game->handleKeyPress(key, action);
	}
};


#endif
