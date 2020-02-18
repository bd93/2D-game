#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H


#include <vector>
#include <glm/glm.hpp>
#include "../Shader.h"
#include "../Helpers/RandomGenerator.h"
#include "../Helpers/ResourceManager.h"
#include "../Renderers/ParticleRenderer.h"
#include "../Helpers/DeltaTime.h"

struct Particle
{
	glm::vec2 size;
	glm::vec2 position;
	glm::vec3 velocity;
	float lifeTime;
	bool available = false;
};

class ParticleSystem
{
private:
	size_t m_PoolIndex = 99;
	std::vector<Particle> m_ParticlePool;
public:
	ParticleSystem();
	void Emit(const Particle& particelProps);
	void Update(float timeStep);
	void Render(Renderer& renderer);
};

#endif
