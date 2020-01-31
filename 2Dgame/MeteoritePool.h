#ifndef METEORITEPOOL_H
#define METEORITEPOOL_H

#include <glm/glm.hpp>
#include <vector>
#include "Object.h"


class MeteoritePool
{
private:
	std::vector<Object> m_meteorites;
	int m_spawnFrequency = 2; // in seconds
public:
	void add_to_pool(Object meteorite)
	{
		m_meteorites.push_back(meteorite);
	}
	void drawMeteorites(SpriteRenderer& renderer, float speed)
	{
		int index = 0;
		for (auto& meteorite : m_meteorites)
		{
			if (meteorite.getPosition().y <= 0 || meteorite.getDestroyed())
			{
				m_meteorites.erase(m_meteorites.begin() + index);
			}

			meteorite.draw(renderer);
			meteorite.move(speed * 30.0f, "down");

			index++;
		}
	}
	int getSpawnFrequency()
	{
		return m_spawnFrequency;
	}
	std::vector<Object>& getMeteorites()
	{
		return m_meteorites;
	}
};

#endif