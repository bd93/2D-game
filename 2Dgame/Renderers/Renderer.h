#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

#include "../Texture.h"
#include "../Shader.h"


class Renderer
{
protected:
	GLuint m_VBO;
	GLuint m_VAO;
	Shader& m_Shader;
public:
	Renderer(Shader& shader)
		: m_Shader(shader)
	{
	}
	virtual ~Renderer()
	{
	}
	virtual void Draw(const glm::vec2& position, const glm::vec2& size, Texture* texture = nullptr) = 0;
};

#endif // !RENDERER_H
