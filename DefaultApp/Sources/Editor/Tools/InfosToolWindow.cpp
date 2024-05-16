#include "InfosToolWindow.h"

#include <imgui.h>
#include <iostream>

InfosToolWindow::InfosToolWindow(const std::string& title, bool open, Point2Di position, Point2Di size)
    : ToolWindow(title, open, position, size), fps(0), verticesCount(0), primitivesCount(0), sensitivity(0), lastFOV(0), FOV(120)
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
    ImgUISpacing(0, 5);    
    ImGui::SliderFloat("FOV", &FOV, 20.f, 170.f, "%.0f");
    ImgUISpacing(0, 5);    
    ImGui::Text("Move Speed: %.2f", sensitivity);
    ImgUISpacing(0, 5);    
    ImGui::Checkbox("Toggle Rotation Mode", &toggleChecked);
    ImGui::Checkbox("Wireframe View", &wireFrameChecked);

    if (lastWireframeMode != wireFrameChecked)
    {
        lastWireframeMode = wireFrameChecked;
        wireframeModeChanged.Broadcast();
    }
    if (FOV != lastFOV)
    {
        lastFOV = FOV;
        fovChanged.Broadcast(FOV);
    }
    if (toggleChecked != lastToggleMode)
    {
        lastToggleMode = toggleChecked;
        toggleModeChanged.Broadcast();
    }
}