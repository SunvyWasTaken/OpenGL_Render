#include "ToolWindow.h"

#include "Editor/ToolsManager.h"

#include <imgui.h>
#include <iostream>

ToolWindow::ToolWindow(const std::string& title, bool open, Point2Di position, Point2Di size)
	: m_title(title), m_open(open), m_position(position), m_size(size)
{
}

ToolWindow::~ToolWindow()
{
	std::cout << "Destroy Window Editor" << std::endl;
}

void ToolWindow::Begin()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
	ImGui::Begin(m_title.c_str(), &m_open, flags);
	//set position and size
	ImGui::SetWindowPos(ImVec2(m_position.x, m_position.y));
	ImGui::SetWindowSize(ImVec2(m_size.x, m_size.y));
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
