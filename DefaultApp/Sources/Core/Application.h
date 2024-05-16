#pragma once
#include <chrono>
#include <memory>
#include "Window/OGLWindow.h"
#include "LowLevel_Renderer/Cameras/Camera.h"

class ToolsManager;

class Application
{
public:
	Application();
	~Application();

	void Run();

	Camera camera;
private:
	void _Draw(OGLWindow& window);
	void _PollEvent();

	class SettingsToolWindow* m_settingsUI;
	class InfosToolWindow* m_infosUI;

	std::unique_ptr<OGLWindow> m_window;
	std::unique_ptr<ToolsManager> m_toolsManager;
};