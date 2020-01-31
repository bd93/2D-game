#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include "SpriteRenderer.h"
#include "Texture.h"

class Object
{
protected:
	glm::vec2 m_position, m_size, m_velocity;
	Texture m_texture;
	bool m_destroyed;
public:															
	Object(glm::vec2 position, glm::vec2 size, Texture texture,  glm::vec2 velocity = glm::vec2(0.0f, 0.0f))
		: m_position(position), m_size(size), m_velocity(velocity), m_texture(texture), m_destroyed(false)
	{
	}
	Object()
		: m_position(0, 0), m_size(1, 1), m_velocity(0.0f), m_texture(), m_destroyed(false)
	{
	}
	glm::vec2 getPosition()
	{
		return m_position;
	}
	glm::vec2 getSize()
	{
		return m_size;
	}
	bool getDestroyed()
	{
		return m_destroyed;
	}
	void setDestroyed(bool option)
	{
		m_destroyed = option;
	}
	void draw(SpriteRenderer& renderer)
	{
		renderer.draw(m_texture, m_position, m_size);
	}
	void move(GLfloat dt, std::string direction)
	{
		if (direction == "left" || direction == "down")
			m_position += -m_velocity * dt;
		else if (direction == "right" || direction == "up")
			m_position += m_velocity * dt;
	}
};


#endif
