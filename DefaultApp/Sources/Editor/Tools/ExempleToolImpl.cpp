#include "ExempleToolImpl.h"

#include <imgui.h>

ExempleToolImpl::ExempleToolImpl(const std::string& title, bool open)
	: ToolWindow(title, open)
{
}

ExempleToolImpl::~ExempleToolImpl()
{
}

void ExempleToolImpl::Draw()
{
	//ToolWindow::Draw();

	ImGui::Text("Hello World");
	float samples[100];
	for (int n = 0; n < 100; n++)
		samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
	ImGui::PlotLines("Samples", samples, 100);
	ImGui::Text("Sheesh");
	ImGui::Text("New Text");
}
