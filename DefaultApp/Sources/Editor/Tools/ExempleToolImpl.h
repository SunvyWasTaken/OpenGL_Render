#pragma once
#include "ToolWindow.h"

class ExempleToolImpl : public ToolWindow
{
public:
	explicit ExempleToolImpl(const std::string& title = "Window Editor", bool open = false);
	~ExempleToolImpl();

	void Draw() override;
};