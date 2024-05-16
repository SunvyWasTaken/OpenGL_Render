#include "Application.h"

#include "ContextRenderer.h"
#include "Editor/Tools/ExempleToolImpl.h"
#include "Editor/ToolsManager.h"
#include "Editor/Tools/ToolWindow.h"
#include "LowLevel_Renderer/Cameras/Camera.h"
#include "LowLevel_Renderer/Lights/DirectionalLight.h"
#include "LowLevel_Renderer/Primitive/Cube.h"
#include "LowLevel_Renderer/Primitive/SkyBox.h"
#include "LowLevel_Renderer/Primitive/Vertex.h"
#include "LowLevel_Renderer/Viewports/Viewport.h"
#include "ProceduralGeneration.h"
#include <stdexcept>

Application::Application()
	: m_window(new OGLWindow(1240, 720, "Procedural map generation")), m_toolsManager(new ToolsManager())
{
	m_ExempleEditor = new ExempleToolImpl("Exemple Window Editor Implementation", true);
	m_ExempleEditor->AddToEditorManager(m_toolsManager.get());
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
	//using TriangleF = Triangle<float>;
	//TriangleF triangle{};
	//triangle.transform.position = P3D{ 2.5f, 2.5f, -8.f };

	//using PlaneF = Plane<float>;
	//PlaneF plane{};
	//plane.transform.position = P3D{ 0.f, -1.f, -5.f };
	//plane.transform.rotation = { 0.f, 0.0f, 0.0f };

	DirectionalLight directionalLight;
	directionalLight.direction = { -0.2f, -1.f, -0.3f };
	directionalLight.diffuse = { 0.5f, 0.5f, 0.5f };
	directionalLight.ambient = directionalLight.diffuse * 0.2f;
	directionalLight.specular = 1.f;

	//SkyBox<float> skybox;
	//skybox.transform.scale = { 50.f,50.f,50.f };

	Cube<float> cube;
	cube.transform.position = { 0.f, 0.f, -5.f };
	cube.transform.scale = { 0.5f, 0.5f, 0.5f };

	//Cube<float> cube2;
	//cube2.transform.position = { 1.5f, -0.0f, -12.f };
	//cube2.transform.scale = { 0.5f, 0.5f, 0.5f };

	float aspectRatio = 1240.f / 720.f;
	float fov = 45.f / 180.f * 3.141592f;
	float nearPlane = 0.01f;
	float farPlane = 15000.f;
		
	Viewport viewport(aspectRatio, fov, nearPlane, farPlane); //projection matrix

	camera.transform.position = { 0.f, 0.f, 0.f };
	camera.transform.rotation = { 0.f, 0.f, 0.f };
	Math::Mat4<float> model = Math::Mat4<float>::identity();   //model matrix

	//ContextRenderer contextRenderer{ viewport.getMatrixProjection(), camera.getMatrixView() };

	// TODO : Ici mettre le reste pour gen le terrain;

	FaultFormation Terrain;
	m_ExempleEditor->CurrentTerrain = &Terrain;
	Terrain.transform.position = {-25.f, 0.f, -25.f};
	Terrain.transform.scale = { 1.f, 1.f, 1.f };

	Terrain.GenerateTerrain(50, 100, 0, 50, 0.01f);

	while (!m_window->isWindowShouldClose())
	{
		m_window->ClearBackBuffer();

		ContextRenderer contextRenderer{ viewport.getMatrixProjection(), camera, directionalLight };

		Terrain.Render(contextRenderer);

		// TODO: write code here...

		//triangle.transform.rotation.y += 0.0025f;
		//plane.transform.rotation.y += 0.001f;

		//cube.transform.rotation.y = 0.5f;

		cube.render(contextRenderer);
		//cube2.render(contextRenderer);

		//cube.transform.rotation.y += 0.0005f;
		//cube.transform.rotation.x += 0.0005f;
		//
		//skybox.render(contextRenderer);

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
