#include "Application.h"

#include <stdexcept>

#include "Editor/Tools/ExempleToolImpl.h"
#include "Editor/ToolsManager.h"
#include "Editor/Tools/ToolWindow.h"

Application::Application()
	: m_window(new OGLWindow(800, 800, "Procedural map generation")), m_toolsManager(new ToolsManager())
{
	ToolWindow* ExempleEditor = new ExempleToolImpl("Exemple Window Editor Implementation", true);
	ExempleEditor->AddToEditorManager(m_toolsManager.get());
}

Application::~Application()
{
}

void Application::Run()
{
	if (!m_window)
		throw std::runtime_error("Can't run, no window has created !");

	m_window->Init();

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
	m_toolsManager->Render();
}

void Application::_PollEvent()
{
	m_window->PollEvent();
}
