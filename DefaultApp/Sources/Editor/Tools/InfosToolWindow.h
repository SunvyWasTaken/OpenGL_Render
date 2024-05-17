#pragma once
#include "ToolWindow.h"
#include "Editor/Observer/SignalSlot.h"
#include "Math/Vector3D.h"

DECLARE_MULTICAST_DELEGATE(OnChangedWireframeMode)
DECLARE_MULTICAST_DELEGATE(OnChangedToggleMode)
DECLARE_MULTICAST_DELEGATE(OnChangedFOV, float)
DECLARE_MULTICAST_DELEGATE(OnChangedSunDirection, Math::Vector3D<float>)

class InfosToolWindow : public ToolWindow
{
public:
    explicit InfosToolWindow(const std::string& title, bool open = false, Point2Di position = Point2Di(0, 0), Point2Di size = Point2Di(0, 0));
    ~InfosToolWindow();

    void Draw() override;

    void UpdateFPS(int newFps){fps = newFps;}
    void UpdateSensitivity(float newSensitivity){sensitivity = newSensitivity;}

    void SetTriObjectNbr(int newPrimitiveCount, int newObjectsCount)
    {
        primitivesCount = newPrimitiveCount;
        objectsCount = newObjectsCount;
    }

    OnChangedWireframeMode wireframeModeChanged;
    OnChangedToggleMode toggleModeChanged;
    OnChangedFOV fovChanged;
    OnChangedSunDirection sunDirectionChanged;
    
private:
    int fps;
    int objectsCount;
    int primitivesCount;
    float sensitivity;
    
    float FOV;
    bool wireFrameChecked = false;
    bool toggleChecked = false;

    float lastFOV;
    bool lastWireframeMode = false;
    bool lastToggleMode = false;

    Math::Vector3D<float> sunRotation;
    Math::Vector3D<float> lastSunRotation;
};
