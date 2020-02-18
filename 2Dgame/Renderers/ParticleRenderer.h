#ifndef PARTICLERENDERER_H
#define PARTICLERENDERER_H

#include "Renderer.h"

class ParticleRenderer : public Renderer
{
public:
	ParticleRenderer(Shader& shader)
		: Renderer(shader)
	{
		this->Init();
	}
	~ParticleRenderer()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_IBO);
	}
	virtual void Draw(const glm::vec2& position, const glm::vec2& size, Texture* texture = nullptr) override
	{
		//if (texture != nullptr)
		//{
		//	glActiveTexture(GL_TEXTURE0);
		//	texture->bind();
		//}

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position, 0.0f));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, glm::vec3(size, 0.0f));

		glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

		m_Shader.setMatrix4("model", model, GL_FALSE);
		m_Shader.setMatrix4("projection", projection, GL_FALSE);

		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
private:
	GLuint m_IBO;
	void Init()
	{
		GLfloat vertices[] = {
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
		};

		GLuint indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		m_Shader.setVector4f("color", glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), true);

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_IBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
};


#endif