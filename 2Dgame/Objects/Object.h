#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include "../Renderers/Renderer.h"


class Object
{
protected:
	glm::vec2 m_Position;
	glm::vec2 m_Size; 
public:		
	Object(glm::vec2 position, glm::vec2 size)
		: m_Position(position), m_Size(size)
	{
	}
	virtual ~Object()
	{
	}
	virtual void Render(Renderer& renderer, Texture* texture = nullptr)
	{
		renderer.Draw(m_Position, m_Size, texture);
	}
	virtual void Move(const glm::vec2& velocity, float dt)
	{
		m_Position += velocity * dt;
	}
	glm::vec2& GetPosition()
	{
		return m_Position;
	}
	glm::vec2& GetSize()
	{
		return m_Size;
	}
};


#endif
