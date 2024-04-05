#pragma once
#include <memory>
#include "Window/OGLWindow.h"

class ToolsManager;

class Application
{
public:
	Application();
	~Application();

	void Run();

private:
	void _Draw(OGLWindow& window);
	void _PollEvent();

	std::unique_ptr<OGLWindow> m_window;
	std::unique_ptr<ToolsManager> m_toolsManager;
};