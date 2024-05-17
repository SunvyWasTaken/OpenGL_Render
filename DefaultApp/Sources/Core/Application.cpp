#include "Application.h"

#include "Editor/Tools/SettingsToolWindow.h"
#include "Editor/Tools/InfosToolWindow.h"
#include "Editor/ToolsManager.h"
#include "Editor/Tools/ToolWindow.h"
#include "LowLevel_Renderer/Cameras/Camera.h"
#include "LowLevel_Renderer/Primitive/Cube.h"
#include "LowLevel_Renderer/Primitive/SkyBox.h"
#include "LowLevel_Renderer/Primitive/Vertex.h"


#include <stdexcept>

using Point2Di = Math::Point2D<int>;

Application::Application()
	: m_window(new OGLWindow(1240, 720, "Procedural map generation")), m_toolsManager(new ToolsManager())
{
	m_settingsUI = new SettingsToolWindow("TERRAIN SETTINGS", true, Point2Di(10, 10), Point2Di(300, 400));
	m_infosUI = new InfosToolWindow("SCENE", true, Point2Di(1030, 10), Point2Di(200, 405));
	m_settingsUI->AddToEditorManager(m_toolsManager.get());
	m_infosUI->AddToEditorManager(m_toolsManager.get());
	OnUpdateFPS.Bind(m_infosUI, &InfosToolWindow::UpdateFPS);
	m_window->sensitivityChanged.Bind(m_infosUI, &InfosToolWindow::UpdateSensitivity);
	m_infosUI->wireframeModeChanged.Bind(this, &Application::SwitchWireframeMode);
	m_infosUI->fovChanged.Bind(this, &Application::ChangeFOV);
	m_infosUI->toggleModeChanged.Bind(m_window.get(), &OGLWindow::ToggleCameraRotationMode);
	m_infosUI->sunDirectionChanged.Bind(this, &Application::ChangeSunDirection);
}

Application::~Application()
{
}

void Application::Run()
{
	if (!m_window)
		throw std::runtime_error("Can't run, no window has created !");

	m_window->Init();

	InitializePrimitives();
	InitializeTerrain();
	InitializeLights();
	InitializeRenderer(120.f);
	m_infosUI->SetTriObjectNbr(primitiveCount, objects);

	camera.transform.position = { 0.f, 20.f, 0.f };
	camera.transform.rotation = { 0.f, 4.f, 0.f };

	while (!m_window->isWindowShouldClose())
	{
		m_window->ClearBackBuffer();
		
		m_renderer.projection = m_viewport.getMatrixProjection();
		m_renderer.camera = camera;

		for (const auto& mesh : m_meshes)
		{
			mesh->render(m_renderer);
		}
		m_Terrain.Render(m_renderer);
		_Draw(*m_window);
		glPolygonMode(GL_FRONT_AND_BACK, WireframeMode ? GL_LINE : GL_FILL);	//Set view mode with full triangle

		CalculateFPS();

		glFlush();

		m_window->SwapBuffer();
		_PollEvent();
	}
}

void Application::CalculateFPS()
{
	static float lastTime;
	float currentTime = glfwGetTime();
	float deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	static float time = 0.f;
	time += deltaTime;
	if (time >= 1.f)
	{
		OnUpdateFPS.Broadcast(1.f / deltaTime);
		time = 0.f;
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

void Application::InitializeRenderer(float newFov)
{
	float setFOV = 100.f;
	float aspectRatio = 1240.f / 720.f;
	float fov = setFOV / 180.f * 3.141592f;
	float nearPlane = 0.01f;
	float farPlane = 15000.f;

	m_viewport = Viewport(aspectRatio, fov, nearPlane, farPlane);
	m_renderer = ContextRenderer{
		m_viewport.getMatrixProjection(),
		camera,
		m_SceneSun,
		&m_lights,
	};
}

void Application::ChangeFOV(float newFov)
{
	float FOV = newFov / 180.f * 3.141592f;
	m_viewport = Viewport(m_viewport.m_apsectRatio, FOV, m_viewport.m_nearPlane, m_viewport.m_farPlane);
	m_renderer.projection = m_viewport.getMatrixProjection();
}

void Application::InitializePrimitives()
{
	std::shared_ptr<Material> boxMaterial = std::make_shared<Material>();
	boxMaterial->LoadTexture<diffuse>("Ressources\\mat_test_diffuse.png");
	boxMaterial->LoadTexture<specular>("Ressources\\mat_test_specular.png");
	boxMaterial->shininess = 32.f;

	//Material* catMaterial = new Material();
	//catMaterial->LoadTexture<diffuse>("Ressources\\sc.png");
	//catMaterial->LoadTexture<specular>("Ressources\\sc.png");
	//catMaterial->shininess = 32.f;

	std::vector<ShaderInfo> basicShaders = {
		{GL_VERTEX_SHADER,  "default.vert"},
		{GL_FRAGMENT_SHADER, "default.frag"}
	};

	std::vector<ShaderInfo> skyboxShader = {
		{GL_VERTEX_SHADER,  "skybox.vert"},
		{GL_FRAGMENT_SHADER, "skybox.frag"}
	};
	
	SkyBox<float>* skybox = new SkyBox<float>();
	skybox->transform.scale = { 500.f,500.f,500.f };
	skybox->addShaders(skyboxShader);
	skybox->load();
	m_meshes.emplace_back(skybox);

	Cube<float>* cube = new Cube<float>();
	cube->transform.position = { 0.f, 0.f, -5.f };
	cube->transform.scale = { 0.5f, 0.5f, 0.5f };
	cube->applyMaterial(boxMaterial);
	cube->addShaders(basicShaders);
	cube->load();
	m_meshes.emplace_back(cube);

	Cube<float>* cube2 = new Cube<float>();
	cube2->transform.position = { 1.5f, -0.0f, -12.f };
	cube2->transform.scale = { 0.5f, 0.5f, 0.5f };
	cube2->applyMaterial(boxMaterial);
	cube2->addShaders(basicShaders);
	cube2->load();
	m_meshes.emplace_back(cube2);

	for (auto& mesh : m_meshes)
	{
		primitiveCount += mesh->triCount;
		objects++;
	}
}


void Application::InitializeLights()
{
	DirectionalLight directionalLight;
	directionalLight.direction = { -0.2f, -1.f, -0.3f };
	directionalLight.diffuse = { 1.f, 1.f, 1.f };
	directionalLight.ambient = directionalLight.diffuse * 0.2f;
	directionalLight.specular = {1.f, 1.f, 1.f};
	m_SceneSun = directionalLight;
	objects++;

	PointLight* pointLight = new PointLight();
	pointLight->position = { 1.f, 0.5f, -3.f };
	pointLight->diffuse = { 1.f, 0.f, 0.f };
	pointLight->ambient = pointLight->diffuse * 0.2f;
	pointLight->specular = 50.f;
	m_lights.emplace_back(pointLight);

	PointLight* pointLight2 = new PointLight();
	pointLight2->position = { -1.f, 0.5f, -3.f };
	pointLight2->diffuse = { 0.f, 0.f, 1.f };
	pointLight2->ambient = pointLight2->diffuse * 2.f;
	pointLight2->specular = 1.f;
	m_lights.emplace_back(pointLight2);
	
	objects += m_lights.size();
}

void Application::ChangeSunDirection(Math::Vector3D<float> newDirection)
{
	m_SceneSun.direction = Math::Point3D<float>{newDirection.x, newDirection.y, newDirection.z};
	m_renderer = ContextRenderer{
		m_viewport.getMatrixProjection(),
		camera,
		m_SceneSun,
		&m_lights,
	};
}

void Application::InitializeTerrain()
{
	m_settingsUI->CurrentTerrain = &m_Terrain;
	m_Terrain.transform.position = { -25.f, -25.f, -25.f };
	m_Terrain.transform.scale = { 1.f, 1.f, 1.f };
	m_Terrain.InitTerrain(500);
	m_Terrain.GenerateProceduralTerrain<FaultFormation>(1000, 0, 50, 0.75f);
	primitiveCount += m_Terrain.GetTerrainSize() * m_Terrain.GetTerrainSize() * 2;
	objects++;
}
