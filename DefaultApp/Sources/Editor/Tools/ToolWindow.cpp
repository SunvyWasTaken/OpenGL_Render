#include "ToolWindow.h"

#include "Editor/ToolsManager.h"

#include <imgui.h>
#include <iostream>

ToolWindow::ToolWindow(const std::string& title, bool open)
	: m_title(title), m_open(open)
{
}

ToolWindow::~ToolWindow()
{
	std::cout << "Destroy Window Editor" << std::endl;
}

void ToolWindow::Begin()
{
	ImGui::Begin(m_title.c_str(), &m_open);
}

void ToolWindow::End()
{
	ImGui::End();
}

void ToolWindow::AddToEditorManager(ToolsManager* toolsManager)
{
	toolsManager->AddWindowEditor(this);
}

void ToolWindow::RemoveToEditorManager(ToolsManager* toolsManager)
{
	toolsManager->RemoveWindowEditor(this);
}
