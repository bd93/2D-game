#include "ParticleSystem.h"


ParticleSystem::ParticleSystem()
{
	// initialize 100 particles
	m_ParticlePool.resize(100);
}

void ParticleSystem::Emit(const Particle& particleProps)
{
	// starting from the last index
	Particle& particle = m_ParticlePool[m_PoolIndex];

	particle.size = particleProps.size;
	particle.position = particleProps.position;
	particle.velocity.x = particleProps.velocity.x + RandomGenerator::GetFloat(-100.0f, 100.0f);
	particle.velocity.y = particleProps.velocity.y + RandomGenerator::GetFloat(-100.0f, 100.0f);
	particle.available = particleProps.available;
	particle.lifeTime = particleProps.lifeTime;

	/*
	 because index cannot be negative, there will always be particle available for emitting;
	 "% m_ParticlePool.size()" will limit index to 99 (last index in particle vector);
	 this way particles are being reused inside pool
	*/
	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}

void ParticleSystem::Update(float timeStep)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.available)
		{
			continue;
		}

		if (particle.lifeTime <= 0.0f)
		{
			particle.available = false;
			continue;
		}

		particle.lifeTime -= timeStep;
		particle.position.x += particle.velocity.x * DeltaTime::m_DeltaTime;
		particle.position.y += particle.velocity.y * DeltaTime::m_DeltaTime;
	}
}

void ParticleSystem::Render(Renderer& renderer)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.available)
		{
			continue;
		}
		renderer.Draw(particle.position, particle.size);
	}
}
