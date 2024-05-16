#pragma once
#include "ToolWindow.h"
#include "Editor/Observer/SignalSlot.h"

DECLARE_MULTICAST_DELEGATE(OnChangedWireframeMode)

class InfosToolWindow : public ToolWindow
{
public:
    explicit InfosToolWindow(const std::string& title, bool open = false, Point2Di position = Point2Di(0, 0), Point2Di size = Point2Di(0, 0));
    ~InfosToolWindow();

    void Draw() override;

    void UpdateFPS(int fps);
    void UpdateSensitivity(float sensitivity);

    OnChangedWireframeMode wireframeModeChanged;
    
private:
    int fps;
    int verticesCount;
    int primitivesCount;

    float sensitivity;
    float FOV;

    bool toggleChecked;
    bool wireFrameChecked = false;
    bool lastWireframeMode = false;
};
