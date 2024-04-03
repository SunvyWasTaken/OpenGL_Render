#include "ToolWindow.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

#include "../ToolsManager.h"

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

void ToolWindow::Draw()
{
	
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
