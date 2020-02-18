#ifndef WEAPON_H
#define WEAPON_H

#include <glm/glm.hpp>
#include <vector>
#include "Object.h"
#include "../Helpers/ResourceManager.h"

class Weapon : public Object
{
private:
	std::vector<Object> m_Bullets;
public:
	Weapon(const glm::vec2& position, const glm::vec2& size)
		: Object(position, size)
	{
	}
	void Fire()
	{
		// "x" position of a bullet is at the center of a player and "y" is player's size.y coordinate
		m_Bullets.push_back(Object(glm::vec2(m_Position.x + (m_Size.x / 2), m_Size.y), glm::vec2(5, 20)));
	}
	void DrawBullets(Renderer& renderer, float dt)
	{
		int index = 0;
		for (auto& bullet : m_Bullets)
		{
			// erase bullet that touches the top of the screen from vector
			if ((bullet.GetPosition().y + bullet.GetSize().y) >= 600)
			{
				m_Bullets.erase(m_Bullets.begin() + index);
			}

			bullet.Render(renderer, &ResourceManager::GetLoadedTexture("LaserBeam"));
			bullet.Move(glm::vec2(0.0f, 250.0f), dt);

			index++;
		}
	}
	std::vector<Object>& GetBullets()
	{
		return m_Bullets;
	}
};

#endif