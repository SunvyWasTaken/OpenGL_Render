#include "Application.h"

#include <stdexcept>

#include "Editor/Tools/ExempleToolImpl.h"
#include "Editor/ToolsManager.h"
#include "Editor/Tools/ToolWindow.h"
#include "LowLevel_Renderer/Primitive/Plane.h"
#include "LowLevel_Renderer/Primitive/Triangle.h"
#include "LowLevel_Renderer/Primitive/Vertex.h"

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

	using VertexF = Vertex<float>;
	using TriangleF = Triangle<float>;
	TriangleF triangle{};

	using PlaneF = Plane<float>;
	PlaneF plane{};

	while (!m_window->isWindowShouldClose())
	{
		m_window->ClearBackBuffer();

		// TODO: write code here...

		//triangle.render();
		plane.render();

		_Draw(*m_window);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//Set view mode in wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//Set view mode with full triangle

		glFlush();

		m_window->SwapBuffer();
		_PollEvent();
	}
}

void Application::_Draw(OGLWindow& window)
{
	m_toolsManager->Render();
}

void Application::_PollEvent()
{
	m_window->PollEvent();
}
