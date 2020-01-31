#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <functional>

#define MAX_RANDOM 800
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#include "Shader.h"
#include "SpriteRenderer.h"
#include "Object.h"
#include "Player.h"
#include "MeteoritePool.h"
#include "Game.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	stbi_set_flip_vertically_on_load(true);

	Game game;
	game.addShader("spriteShaders", Shader("Shaders/vertex.shader", "Shaders/fragment.shader"));
	game.setRenderer("spriteShaders"); // using spriteShaders for spriteRenderer

	glfwSetWindowUserPointer(window, &game);
	glfwSetKeyCallback(window, game.key_callback);

	srand(time(0));

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		game.setDeltaTime(deltaTime);
		lastFrame = currentFrame;

		game.processInput(window);

		//render
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		game.drawGameObjects();
		game.checkCollisions();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

