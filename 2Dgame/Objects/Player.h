#ifndef PLAYER_H
#define PLAYER_H

#include "../Window.h"
#include "Object.h"
#include "Weapon.h"
#include "../Interfaces/IEventListener.h"
#include "../Input.h"
#include "../Helpers/DeltaTime.h"

class Player : public Object, public IEventListener
{
private:
	int m_LifePoints;
	Weapon m_Weapon;
public:
	Player(glm::vec2 position, glm::vec2 size)
		: Object(position, size), m_LifePoints(3), m_Weapon(m_Position, m_Size)
	{
	}
	virtual void HandleEvent() override
	{
		// move left
		if (Input::GetKey(GLFW_KEY_A) && !Input::GetKey(GLFW_KEY_D))
		{
			this->Move(glm::vec2(-200.0f, 0.0f), DeltaTime::m_DeltaTime);
		}
		// move right
		if (Input::GetKey(GLFW_KEY_D) && !Input::GetKey(GLFW_KEY_A))
		{
			this->Move(glm::vec2(200.0f, 0.0f), DeltaTime::m_DeltaTime);
		}
		// weapon fire
		if (Input::GetKey(GLFW_KEY_SPACE))
		{
			this->FireLaserBeam();
			// not the best solution, it needs to be defined in Window.cpp;
			// fire only one bullet (laser beam) when spacebar is pressed once
			Input::SetKey(GLFW_KEY_SPACE, false);
		}
	}
	virtual void Move(const glm::vec2& velocity, float dt) override
	{
		m_Position += velocity * dt;
		m_Weapon.Move(velocity, dt);
	}
	virtual void Render(Renderer& renderer, Texture* texture = nullptr) override
	{
		renderer.Draw(m_Position, m_Size, texture);
		m_Weapon.DrawBullets(renderer, DeltaTime::m_DeltaTime);
	}
	void FireLaserBeam()
	{
		m_Weapon.Fire();
	}
	Weapon& GetWeapon()
	{
		return m_Weapon;
	}
};

#endif