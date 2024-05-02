#include "Application.h"

#include <stdexcept>

#include "ContextRenderer.h"
#include "Editor/Tools/ExempleToolImpl.h"
#include "Editor/ToolsManager.h"
#include "Editor/Tools/ToolWindow.h"
#include "LowLevel_Renderer/Cameras/Camera.h"
#include "LowLevel_Renderer/Primitive/Cube.h"
#include "LowLevel_Renderer/Primitive/Plane.h"
#include "LowLevel_Renderer/Primitive/Triangle.h"
#include "LowLevel_Renderer/Viewports/Viewport.h"

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

	using P3D = Math::Point3D<float>;
	using TriangleF = Triangle<float>;
	TriangleF triangle{};
	triangle.transform.position = P3D{ 2.5f, 2.5f, -8.f };

	using PlaneF = Plane<float>;
	PlaneF plane{};
	plane.transform.position = P3D{ 0.f, -1.f, -5.f };
	plane.transform.rotation = { 0.f, 0.0f, 0.0f };

	Cube<float> light{ "light" };
	light.transform.position = { -0.5f,0.8f,-5.0f };
	light.transform.scale = { 0.1f, 0.1f, 0.1f };

	Cube<float> cube{ "default" };
	cube.transform.position = { 0.f, 0.f, -5.f };
	cube.transform.scale = { 0.5f, 0.5f, 0.5f };
	cube.li = true;

	float aspectRation = 800 / 800;
	float fov = 45.f / 180.f * 3.141592f;
	float nearPlane = 0.01f;
	float farPlane = 10.f;
		
	Viewport viewport(aspectRation, fov, nearPlane, farPlane); //projection matrix
	//Math::Mat4<float> camera = Math::Mat4<float>::identity();  //view matrix

	camera.transform.position = { 0.f, -1.6f, 2.f };
	camera.transform.rotation = { 0.3f, 0.f, 0.f };
	Math::Mat4<float> model = Math::Mat4<float>::identity();   //model matrix

	//ContextRenderer contextRenderer{ viewport.getMatrixProjection(), camera.getMatrixView() };

	while (!m_window->isWindowShouldClose())
	{
		m_window->ClearBackBuffer();

		ContextRenderer contextRenderer{ viewport.getMatrixProjection(), camera.getMatrixView() };


		// TODO: write code here...

		//triangle.transform.rotation.y += 0.0025f;
		//plane.transform.rotation.y += 0.001f;

		cube.transform.rotation.y = 0.5f;

		light.render(contextRenderer, light, camera);
		cube.render(contextRenderer, light, camera);

		//plane.render(contextRenderer, cube, camera);
		//triangle.render(pvm);
		//cube.transform.rotation.y += 0.0005f;
		//cube.transform.rotation.x += 0.0005f;
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
	m_window->PollEvent(camera);
}
