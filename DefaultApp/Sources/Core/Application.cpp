#include "Application.h"

#include <stdexcept>

#include "Editor/Tools/ExempleToolImpl.h"
#include "Editor/ToolsManager.h"
#include "Editor/Tools/ToolWindow.h"
#include "LowLevel_Renderer/Primitive/Triangle.h"
#include "LowLevel_Renderer/Primitive/Vertex.h"
#include "Editor/Observer/SignalSlot.h"
#include <iostream>

DECLARE_MULTICAST_DELEGATE(TestSignalSlot)

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

	VertexF p0{ { -0.5f, -0.5f, 0.5f}, {1.f, 0.f, 0.f} };
	VertexF p1{ { 0.5f, -0.5f, 0.5f}, {0.f, 1.f, 0.f} };
	VertexF p2{ { 0.5f, 0.5f, 0.5f}, {0.f, 0.f, 1.f} };

	TriangleF triangle(p0, p1, p2);

	/*Test Signal Slot*/
	TestSignalSlot signal;
	signal.Bind([]() {
		std::cout << "Application Started" << std::endl;
		});

	signal.Broadcast();

	while (!m_window->isWindowShouldClose())
	{
		m_window->ClearBackBuffer();

		// TODO: write code here...

		triangle.render();

		_Draw(*m_window);

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
