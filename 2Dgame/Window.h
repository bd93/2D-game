#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "Input.h"

class Window
{
private:
	GLFWwindow* m_GLFWwindow;
	Input* m_Input;
	int m_Width;
	int m_Height;
	std::string m_Name;
public:
	Window(int width, int height, const std::string& name);
	~Window();
	void Init();
	GLFWwindow* GetWindow();
	int GetWidth() const;
	int GetHeight() const;
};


#endif // !WINDOW_H
