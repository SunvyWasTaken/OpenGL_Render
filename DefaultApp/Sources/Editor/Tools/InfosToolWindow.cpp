#include "InfosToolWindow.h"

#include <imgui.h>
#include <iostream>

InfosToolWindow::InfosToolWindow(const std::string& title, bool open, Point2Di position, Point2Di size)
    : ToolWindow(title, open, position, size), fps(0), objectsCount(0), primitivesCount(0), sensitivity(0), lastFOV(0), FOV(120),
    lastWireframeMode(false), lastToggleMode(false), sunRotation(1.f, -1.f, -0.3f), lastSunRotation(-0.f, -0.f, -0.f)
{
}

InfosToolWindow::~InfosToolWindow()
{
}

void InfosToolWindow::Draw()
{
    ImGui::SeparatorText("SCENE INFOS");
    ImGui::Text("FPS: %d", fps);
    ImGui::Text("Triangles: %d", primitivesCount);
    ImGui::Text("Objects: %d", objectsCount);
    ImgUISpacing(0, 15);
    ImGui::SeparatorText("CAMERA SETTINGS");
    ImgUISpacing(0, 5);    
    ImGui::SliderFloat("FOV", &FOV, 20.f, 170.f, "%.0f");
    ImgUISpacing(0, 5);    
    ImGui::Text("Move Speed: %.2f", sensitivity);
    ImgUISpacing(0, 5);    
    ImGui::Checkbox("Toggle Rotation Mode", &toggleChecked);
    ImGui::Checkbox("Wireframe View", &wireFrameChecked);
    ImgUISpacing(0, 15);
    ImGui::SeparatorText("SUN SETTINGS");
    ImgUISpacing(0, 5);
    ImGui::Text("Sun Rotation :");
    ImGui::SliderFloat("X", &sunRotation.x, -1.f, 1.f, "%.2f");
    ImGui::SliderFloat("Y", &sunRotation.y, -1.f, 1.f, "%.2f");
    ImGui::SliderFloat("Z", &sunRotation.z, -1.f, 1.f, "%.2f");
    

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
    if (sunRotation != lastSunRotation)
    {
        lastSunRotation = sunRotation;
        sunDirectionChanged.Broadcast(sunRotation);
    }
}