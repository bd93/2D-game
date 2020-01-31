#ifndef WEAPON_H
#define WEAPON_H

#include <glm/glm.hpp>
#include "Object.h"
#include <vector>

class Weapon
{
private:
	std::vector<Object> m_bullets;
public:
			  // weapon position		 // weapon size
	void fire(glm::vec2 const& position, glm::vec2 const& size)
	{
		m_bullets.push_back(Object(glm::vec2(position.x + (size.x / 2), size.y), glm::vec2(5, 20), Texture("Textures/laser_beam.png"), glm::vec2(0, 20)));
	}
	void drawBullets(SpriteRenderer& renderer, float speed)
	{
		int index = 0;
		for (auto& bullet : m_bullets)
		{
			if ((bullet.getPosition().y + bullet.getSize().y) >= SCREEN_HEIGHT)
			{
				m_bullets.erase(m_bullets.begin() + index);
			}

			bullet.draw(renderer);
			bullet.move(speed * 30.0f, "up");

			index++;
		}
	}
	std::vector<Object>& getBullets()
	{
		return m_bullets;
	}
};

#endif