#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include "Object.h"
#include "Weapon.h"

class Player : public Object
{
private:
	int m_lifePoints;
	Weapon m_weapon;
public:
	Player(glm::vec2 position, glm::vec2 size, Texture texture, glm::vec2 velocity)
		: Object(position, size, texture, velocity)
	{
		m_lifePoints = 3;
	}
	Player()
		: Object(glm::vec2(SCREEN_WIDTH / 2, 0), glm::vec2(100, 100), Texture("Textures/spacecraft.png"), glm::vec2(4, 0))
	{
		m_lifePoints = 3;
	}
	~Player()
	{
	}
	void fireLaserBeam(SpriteRenderer& renderer)
	{
		m_weapon.fire(m_position, m_size);
	}
	Weapon& getWeapon()
	{
		return m_weapon;
	}
};

#endif