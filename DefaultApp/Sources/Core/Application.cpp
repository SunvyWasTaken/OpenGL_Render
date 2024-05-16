#include "Application.h"

#include "ContextRenderer.h"
#include "Editor/Tools/SettingsToolWindow.h"
#include "Editor/Tools/InfosToolWindow.h"
#include "Editor/ToolsManager.h"
#include "Editor/Tools/ToolWindow.h"
#include "LowLevel_Renderer/Cameras/Camera.h"
#include "LowLevel_Renderer/Lights/DirectionalLight.h"
#include "LowLevel_Renderer/Primitive/Cube.h"
#include "LowLevel_Renderer/Primitive/SkyBox.h"
#include "LowLevel_Renderer/Primitive/Vertex.h"
#include "LowLevel_Renderer/Viewports/Viewport.h"
#include "ProceduralGeneration.h"
#include "LowLevel_Renderer/Lights/PointLight.h"

#include <stdexcept>

#include "LowLevel_Renderer/Primitive/CubeLight.h"
#include "LowLevel_Renderer/Primitive/Plane.h"

using Point2Di = Math::Point2D<int>;

Application::Application()
	: m_window(new OGLWindow(1240, 720, "Procedural map generation")), m_toolsManager(new ToolsManager())
{
	m_settingsUI = new SettingsToolWindow("Settings", true, Point2Di(10, 10), Point2Di(300, 200));
	m_settingsUI->AddToEditorManager(m_toolsManager.get());
	m_infosUI = new InfosToolWindow("Infos", true, Point2Di(1100, 10), Point2Di(120, 90));
	m_infosUI->AddToEditorManager(m_toolsManager.get());
	OnUpdateFPS.Bind(m_infosUI, &InfosToolWindow::UpdateFPS);
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

	Material boxMaterial{
		Texture("Ressources\\mat_test_diffuse.png", GL_TEXTURE0),
		Texture("Ressources\\mat_test_specular.png", GL_TEXTURE1),
		32.f
	};

	Material catMaterial{
		Texture("Ressources\\sc.png", GL_TEXTURE0),
		Texture("Ressources\\sc.png", GL_TEXTURE1),
		32.f
	};

	std::vector<ShaderInfo> basicShaders = {
		{GL_VERTEX_SHADER,  "default.vert"},
		{GL_FRAGMENT_SHADER, "default.frag"}
	};

	std::vector<ShaderInfo> skyboxShader = {
		{GL_VERTEX_SHADER,  "skybox.vert"},
		{GL_FRAGMENT_SHADER, "skybox.frag"}
	};

	DirectionalLight directionalLight;
	directionalLight.direction = { -0.2f, -1.f, -0.3f };
	directionalLight.diffuse = { 0.4f, 0.4f, 0.4f };
	directionalLight.ambient = { 0.05f, 0.05f, 0.05f };
	directionalLight.specular = { 0.5f, 0.5f, 0.5f };

	PointLight pointLight;
	pointLight.position = { 1.f, 0.5f, -3.f };
	pointLight.diffuse = { 1.f, 1.f, 1.f };
	pointLight.ambient = pointLight.diffuse * 0.2f;
	pointLight.specular = 0.f;

	PointLight pointLight2;
	pointLight2.position = { -1.f, 0.5f, -3.f };
	pointLight2.diffuse = { 0.f, 0.f, 0.f };
	pointLight2.ambient = pointLight2.diffuse * 2.f;
	pointLight2.specular = 1.f;

	SkyBox<float> skybox;
	skybox.transform.scale = { 500.f,500.f,500.f };
	skybox.addShaders(skyboxShader);
	skybox.load();

	using PlaneF = Plane<float>;
	PlaneF plane;
	plane.transform.position = P3D{ 0.f, -1.f, -5.f };
	plane.transform.rotation = { 0.f, 0.0f, 0.0f };
	plane.addShaders(basicShaders);
	plane.applyMaterial(boxMaterial);
	plane.load();

	Cube<float> cube;
	cube.transform.position = { 0.f, 0.f, -5.f };
	cube.transform.scale = { 0.5f, 0.5f, 0.5f };
	cube.applyMaterial(boxMaterial);
	cube.addShaders(basicShaders);
	cube.load();

	Cube<float> cube2;
	cube2.transform.position = { 1.5f, -0.0f, -12.f };
	cube2.transform.scale = { 0.5f, 0.5f, 0.5f };
	cube2.applyMaterial(boxMaterial);
	cube2.addShaders(basicShaders);
	cube2.load();

	CubeLight<float> cubeLight;
	cubeLight.transform.scale = { 1.f, 1.f, 1.f };
	cubeLight.setColor({ 0.f, 0.f, 1.f });
	cubeLight.addShaders({
		{GL_VERTEX_SHADER,  "light.vert"},
		{GL_FRAGMENT_SHADER, "light.frag"}
		});
	cubeLight.load();

	float aspectRatio = 1240.f / 720.f;
	float fov = 45.f / 180.f * 3.141592f;
	float nearPlane = 0.01f;
	float farPlane = 15000.f;
		
	Viewport viewport(aspectRatio, fov, nearPlane, farPlane); //projection matrix

	camera.transform.position = { 0.f, 0.f, 0.f };
	camera.transform.rotation = { 0.f, 0.f, 0.f };

	ContextRenderer contextRenderer{
		viewport.getMatrixProjection(),
		camera,
		directionalLight,
		std::vector<PointLight>{cubeLight}
	};

	FaultFormation Terrain;
	m_settingsUI->CurrentTerrain = &Terrain;
	Terrain.transform.position = { -25.f, -25.f, -25.f };
	Terrain.transform.scale = { 1.f, 1.f, 1.f };

	Terrain.GenerateTerrain(500, 100, 0, 50, 0.01f);

	float lastTime = 0.0f;

	while (!m_window->isWindowShouldClose())
	{
		m_window->ClearBackBuffer();

		contextRenderer.projection = viewport.getMatrixProjection();
		contextRenderer.camera = camera;

		// TODO: write code here...

		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		int fps = 1 / deltaTime;
		OnUpdateFPS.Broadcast(fps);

		//triangle.transform.rotation.y += 0.0025f;
		//plane.transform.rotation.y += 0.001f;

		plane.transform.rotation.x = 0.9f;

		cube.render(contextRenderer);
		cubeLight.render(contextRenderer);
		//cube2.render(contextRenderer);

		plane.render(contextRenderer);

		//cube.transform.rotation.y += 0.0005f;
		cube.transform.rotation.x += 0.0005f;
		
		//skybox.render(contextRenderer);
		Terrain.Render(contextRenderer);
		
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
