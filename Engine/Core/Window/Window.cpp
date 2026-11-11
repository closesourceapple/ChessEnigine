#include "Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>




Window::Window(const unsigned int Height, const unsigned int Width, const char* Title)
	: window(nullptr), m_Height(Height), m_Width(Width)
{
	if (!glfwInit())
	{
		return;
	}

	IS_GLFW_INIT = true;

	window = glfwCreateWindow(m_Width, m_Height, Title, NULL, NULL);
	if (!window)
	{

		Error = true;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	//glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	if (glewInit() != GLEW_OK)
	{
		Error = true;
		return;
	}



	glViewport(0, 0, m_Width, m_Height);
	glfwSwapInterval(1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

Window::~Window()
{
	if (window)
		glfwDestroyWindow(window);

	if (!IS_GLFW_INIT)
		glfwTerminate();
}


void Window::BeginFrame()
{
	//glfwGetFramebufferSize(window, &m_Width, &m_Height);

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);

	m_Width = w;
	m_Height = h;

	glViewport(0, 0, w, h);

	glClear(GL_COLOR_BUFFER_BIT);
}


void Window::EndFrame()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(window);
}


void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

	wnd->m_Width = width;
	wnd->m_Height = height;

	glViewport(0, 0, width, height);
}
void Window::Close()
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}