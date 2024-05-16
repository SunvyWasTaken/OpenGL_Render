#pragma once
#include "ToolWindow.h"
#include "Editor/Observer/SignalSlot.h"

DECLARE_MULTICAST_DELEGATE(FOnRegenaretedTerrain, int /*= iteration*//*, float / * = x* /, float/ * = y* /*/)

class SettingsToolWindow : public ToolWindow
{
public:
	explicit SettingsToolWindow(const std::string& title, bool open = false);
	~SettingsToolWindow();

	void Draw() override;

	FOnRegenaretedTerrain OnRegeneratedTerrain;

	class FaultFormation* CurrentTerrain;

private:

	int m_selectedMethode = 0;
	int NbrIteration = 50;
};