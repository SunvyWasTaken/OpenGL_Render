#pragma once
#include "ToolWindow.h"
#include "Editor/Observer/SignalSlot.h"

DECLARE_MULTICAST_DELEGATE()

class InfosToolWindow : public ToolWindow
{
public:
    explicit InfosToolWindow(const std::string& title, bool open = false);
    ~InfosToolWindow();

    void Draw() override;
    
private:
    int fps;
    int verticesCount;
    int primitivesCount;
    
};
