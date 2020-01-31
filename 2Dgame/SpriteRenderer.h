#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"

class SpriteRenderer
{
private:
	GLuint VBO, VAO;
	Shader shader;
public:
	SpriteRenderer(Shader shader)
	{
		this->shader = shader;
		this->shader.use();

		float vertices[] = {
			// coords   // tex coords
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(VAO);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	SpriteRenderer()
	{
	}
	~SpriteRenderer()
	{
		//delete shader;
	}
	void draw(Texture texture, glm::vec2 position, glm::vec2 size)
	{
		//this->shader.use();
		glActiveTexture(GL_TEXTURE0);
		texture.bind();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position, 0.0f));
		model = glm::scale(model, glm::vec3(size, 1.0f));

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT, -1.0f, 1.0f);

		this->shader.setMatrix4("model", model, GL_FALSE);
		this->shader.setMatrix4("view", view, GL_FALSE);
		this->shader.setMatrix4("projection", projection, GL_FALSE);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
};


#endif