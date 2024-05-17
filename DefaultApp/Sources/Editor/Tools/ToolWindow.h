#pragma once

#include <imgui.h>
#include <string>

#include "Math/Point.h"

class ToolsManager;

using Point2Di = Math::Point2D<int>;

#define ImgUISpacing(x, y) \
ImGui::Dummy(ImVec2(x,y))

class ToolWindow
{
public:
	explicit ToolWindow(const std::string& title = "Window Editor", bool open = false, Point2Di position = Point2Di(0, 0), Point2Di size = Point2Di(0, 0));
	virtual ~ToolWindow();

	void Begin();
	virtual void Draw() = 0;
	void End();

	void AddToEditorManager(ToolsManager* toolsManager);
	void RemoveToEditorManager(ToolsManager* toolsManager);

protected:
	Point2Di m_position;
	Point2Di m_size;

private:
	std::string m_title;
	bool m_open = true;

};