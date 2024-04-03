#pragma once

#include <string>

class ToolsManager;

class ToolWindow
{
public:
	explicit ToolWindow(const std::string& title = "Window Editor", bool open = false);
	virtual ~ToolWindow();

	void Begin();
	virtual void Draw();
	void End();

	void AddToEditorManager(ToolsManager* toolsManager);
	void RemoveToEditorManager(ToolsManager* toolsManager);

private:
	std::string m_title;
	bool m_open;
};