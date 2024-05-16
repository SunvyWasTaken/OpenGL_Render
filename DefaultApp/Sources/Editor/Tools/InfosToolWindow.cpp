#include "InfosToolWindow.h"

#include <imgui.h>

InfosToolWindow::InfosToolWindow(const std::string& title, bool open, Point2Di position, Point2Di size)
    : ToolWindow(title, open, position, size), fps(0), verticesCount(0), primitivesCount(0)
{
}

InfosToolWindow::~InfosToolWindow()
{
}

void InfosToolWindow::Draw()
{
    Begin();
    ImGui::Text("FPS: %d", fps);
    ImGui::Text("Vertices: %d", verticesCount);
    ImGui::Text("Primitives: %d", primitivesCount);
    End();
}

void InfosToolWindow::UpdateFPS(int f)
{
    fps = f;
}
