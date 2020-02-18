#include "Window.h"

Window::Window(int width, int height, const std::string& name)
	: m_Width(width), m_Height(height), m_Name(name), m_GLFWwindow(nullptr)
{
	m_Input = Input::GetInstance();
}

Window::~Window()
{
	glfwTerminate();
}

void Window::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_GLFWwindow = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), NULL, NULL);
	if (m_GLFWwindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_GLFWwindow);
	glfwSetWindowUserPointer(m_GLFWwindow, reinterpret_cast<void*>(m_Input));

	glfwSetFramebufferSizeCallback(m_GLFWwindow, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

	glfwSetKeyCallback(m_GLFWwindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Input* input = reinterpret_cast<Input*>(glfwGetWindowUserPointer(window));
			switch (action)
			{
			case GLFW_PRESS:
				input->SetKey(key, true);
				break;
			case GLFW_RELEASE:
				input->SetKey(key, false);
				break;
			}
		});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, m_Width, m_Height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GLFWwindow* Window::GetWindow()
{
	return m_GLFWwindow;
}

int Window::GetWidth() const
{
	return m_Width;
}

int Window::GetHeight() const
{
	return m_Height;
}
