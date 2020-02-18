#ifndef METEORITEPOOL_H
#define METEORITEPOOL_H

#include <glm/glm.hpp>
#include <vector>
#include "Meteorite.h"
#include "../Helpers/DeltaTime.h"


class MeteoritePool
{
private:
	std::vector<Meteorite> m_Meteorites;
	int m_SpawnFrequency;
public:
	MeteoritePool()
		: m_SpawnFrequency(1)
	{
	}
	void Add(Meteorite meteorite)
	{
		m_Meteorites.push_back(meteorite);
	}
	void Render(Renderer& renderer, Texture* texture = nullptr)
	{
		int index = 0;
		for (Meteorite& meteorite : m_Meteorites)
		{
			if (meteorite.GetPosition().y <= 0 || meteorite.IsDestroyed())
			{
				m_Meteorites.erase(m_Meteorites.begin() + index);
			}

			meteorite.Render(renderer, texture);
			meteorite.Move(glm::vec2(0.0f, -50.0f), DeltaTime::m_DeltaTime);

			index++;
		}
	}
	int GetSpawnFrequency()
	{
		return m_SpawnFrequency;
	}
	std::vector<Meteorite>& GetMeteorites()
	{
		return m_Meteorites;
	}
};

#endif