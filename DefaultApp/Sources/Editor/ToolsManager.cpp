#include "ToolsManager.h"
#include "Tools/ToolWIndow.h"
#include <stdexcept>

ToolsManager::ToolsManager()
{
}

ToolsManager::~ToolsManager()
{
	for (const auto& tool : m_tools)
	{
		delete tool;
	}
}

void ToolsManager::AddWindowEditor(ToolWindow* windowEditor)
{
	if(std::find(m_tools.begin(), m_tools.end(), windowEditor) != m_tools.end())
		throw std::runtime_error("Window Editor already exist");

	m_tools.push_back(windowEditor);
}

void ToolsManager::RemoveWindowEditor(const ToolWindow* windowEditor)
{
	auto it = std::find(m_tools.begin(), m_tools.end(), windowEditor);
	if (it != m_tools.end())
	{
		m_tools.erase(it);
		delete windowEditor;
	}
}

void ToolsManager::Render()
{
	for(const auto& tool : m_tools)
	{
		tool->Begin();
		tool->Draw();
		tool->End();
	}
}
