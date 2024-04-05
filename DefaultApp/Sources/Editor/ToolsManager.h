#pragma once
#include <vector>

class ToolWindow;

class ToolsManager
{
public:
	ToolsManager();
	~ToolsManager();

	void AddWindowEditor(ToolWindow* windowEditor);
	void RemoveWindowEditor(const ToolWindow* windowEditor);

	void Render();

private:
	std::vector<ToolWindow*> m_tools;
};
