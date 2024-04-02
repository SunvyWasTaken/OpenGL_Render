#include "Application.h"

#include <stdexcept>

Application::Application()
	: m_window(new OGLWindow(800, 800, "Procedural map generation"))
{
}

Application::~Application()
{
}

void Application::Run()
{
	m_window->Init();

	if (!m_window)
		throw std::runtime_error("Can't run, no window has created !");

	while (!m_window->isWindowShouldClose())
	{
		m_window->ClearBackBuffer();

		// TODO: write code here...

		_Draw(*m_window);

		m_window->SwapBuffer();
		_PollEvent();
	}
}

void Application::_Draw(OGLWindow& window)
{
	// TODO: or write code here...
}

void Application::_PollEvent()
{
	m_window->PollEvent();
}
