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
	ImGui::Begin(m_title.c_str(), NULL, flags);
	//set position and size
	ImGui::SetWindowPos(ImVec2(m_position.x, m_position.y));
	ImGui::SetWindowSize(ImVec2(m_size.x, m_size.y));

	ImGuiStyle& m_style = ImGui::GetStyle();
	m_style = ImGui::GetStyle();
	m_style.WindowRounding = 5.0f;
	m_style.ChildRounding = 5.0f;
	m_style.FrameRounding = 5.0f;
	m_style.GrabRounding = 5.0f;
	m_style.PopupRounding = 5.0f;
	m_style.ScrollbarRounding = 5.0f;
	m_style.TabRounding = 5.0f;
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
