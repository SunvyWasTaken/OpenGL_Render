#pragma once
#include <chrono>
#include <memory>

#include "Editor/Observer/SignalSlot.h"
#include "Window/OGLWindow.h"
#include "LowLevel_Renderer/Cameras/Camera.h"

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

	bool WireframeMode = false;
};