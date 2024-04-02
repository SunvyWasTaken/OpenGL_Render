#include "OGLWindow.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

OGLWindow::OGLWindow(int width, int height, const std::string& title)
	: m_width(width), m_height(height), m_title(title), m_windowOpenGL(nullptr)
{
}

OGLWindow::~OGLWindow()
{
	_Destroy();
}

void OGLWindow::ClearBackBuffer()
{
	//Clear background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	//Clear the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
}

void OGLWindow::SwapBuffer()
{
	glfwSwapBuffers(m_windowOpenGL);
}

int OGLWindow::isWindowShouldClose()
{
	return glfwWindowShouldClose(m_windowOpenGL);
}

void OGLWindow::PollEvent()
{
	glfwPollEvents();
}

void OGLWindow::Init()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_windowOpenGL = glfwCreateWindow(800, 800, m_title.c_str(), nullptr, nullptr);
	if (!m_windowOpenGL)
	{
		std::cout << "Failed to create GLFW window 1" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_windowOpenGL);

	//Load glad so it configures OpenGL
	gladLoadGL();
	glViewport(0, 0, m_width, m_height);
}

void OGLWindow::_Destroy()
{
	glfwDestroyWindow(m_windowOpenGL);
	glfwTerminate();
}
