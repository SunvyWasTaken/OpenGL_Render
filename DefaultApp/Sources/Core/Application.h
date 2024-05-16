#pragma once
#include <chrono>
#include <memory>

#include "ContextRenderer.h"
#include "Editor/Observer/SignalSlot.h"
#include "Window/OGLWindow.h"
#include "LowLevel_Renderer/Cameras/Camera.h"
#include "LowLevel_Renderer/Primitive/PrimitiveMesh.h"
#include "LowLevel_Renderer/Viewports/Viewport.h"
#include "LowLevel_Renderer/Lights/PointLight.h"
#include <vector>

#include "Procedural/FaultFormation/FaultFormation.h"

class ToolsManager;

DECLARE_MULTICAST_DELEGATE(infos_tool_window_delegate, int);

class Application
{
public:
	Application();
	~Application();

	void Run();
	void CalculateFPS();

	void SwitchWireframeMode(){WireframeMode = !WireframeMode;}

	Camera camera;
private:
	void _Draw(OGLWindow& window);
	void _PollEvent();

	class SettingsToolWindow* m_settingsUI;
	class InfosToolWindow* m_infosUI;

	infos_tool_window_delegate OnUpdateFPS;
	infos_tool_window_delegate OnUpdateVertices;

	std::unique_ptr<OGLWindow> m_window;
	std::unique_ptr<ToolsManager> m_toolsManager;

	Viewport m_viewport;
	ContextRenderer m_renderer;
	void InitializeRenderer(float newFov);
	void ChangeFOV(float newFov);

	void InitializePrimitives();
	std::vector<std::unique_ptr<PrimitiveMesh<float>>> m_meshes;

	void InitializeLights();
	std::vector<std::unique_ptr<PointLight>> m_lights;

	DirectionalLight m_SceneSun;

	void InitializeTerrain();
	FaultFormation m_Terrain;

	bool WireframeMode = false;

	int primitiveCount = 0;
};