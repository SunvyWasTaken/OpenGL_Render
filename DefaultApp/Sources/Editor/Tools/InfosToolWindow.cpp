#include "InfosToolWindow.h"

#include <imgui.h>

InfosToolWindow::InfosToolWindow(const std::string& title, bool open, Point2Di position, Point2Di size)
    : ToolWindow(title, open, position, size), fps(0), verticesCount(0), primitivesCount(0), sensitivity(0), FOV(0)
{
    
}

InfosToolWindow::~InfosToolWindow()
{
}

void InfosToolWindow::Draw()
{
    ImGui::SeparatorText("SCENE INFOS");
    ImGui::Text("FPS: %d", fps);
    ImGui::Text("Vertices: %d", verticesCount);
    ImGui::Text("Primitives: %d", primitivesCount);
    ImgUISpacing(0, 30);
    ImGui::SeparatorText("CAMERA SETTINGS");
    ImGui::SliderFloat("FOV Y", &FOV, 0.1f, 180.f);
    ImgUISpacing(0, 10);
    ImGui::Text("Move Speed: %.2f", sensitivity);
    ImgUISpacing(0, 5);
    ImGui::Checkbox("Toggle Camera Rotation", &toggleChecked);
    ImGui::Checkbox("Wireframe View", &wireFrameChecked);

    if (lastWireframeMode != wireFrameChecked)
    {
        lastWireframeMode = wireFrameChecked;
        wireframeModeChanged.Broadcast();
    }
}

void InfosToolWindow::UpdateFPS(int f)
{
    fps = f;
}

void InfosToolWindow::UpdateSensitivity(float s)
{
    sensitivity = s;
}
