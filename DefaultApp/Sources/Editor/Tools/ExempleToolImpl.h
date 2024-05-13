#pragma once
#include "ToolWindow.h"
#include "Editor/Observer/SignalSlot.h"

DECLARE_MULTICAST_DELEGATE(FOnRegenaretedTerrain, int /*= iteration*//*, float / * = x* /, float/ * = y* /*/)

class ExempleToolImpl : public ToolWindow
{
public:
	explicit ExempleToolImpl(const std::string& title, bool open = false);
	~ExempleToolImpl();

	void Draw() override;

	FOnRegenaretedTerrain OnRegeneratedTerrain;

	class BaseTerrain* CurrentTerrain;

private:

	int m_selectedMethode = 0;
	int NbrIteration = 50;
};