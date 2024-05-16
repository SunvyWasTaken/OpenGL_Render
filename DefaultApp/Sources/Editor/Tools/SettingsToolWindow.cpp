#include "SettingsToolWindow.h"

#include "Core/ProceduralGeneration.h"

#include <imgui.h>
#include <vector>
#include <string>
#include <cstring>

namespace
{
	static int TerrainSize = 50;
	static int NbrIteration = 50;
	static float MinHeight = 10.f;
	static float MaxHeight = 50.f;
	static float filter = 0.5f;
}

SettingsToolWindow::SettingsToolWindow(const std::string& title, bool open)
	: ToolWindow(title, open), CurrentTerrain(nullptr)
{

}

SettingsToolWindow::~SettingsToolWindow()
{
}

void SettingsToolWindow::Draw()
{
	//ToolWindow::Draw();

	ImGui::Text("Hello World");
	float samples[100];
	for (int n = 0; n < 100; n++)
		samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
	ImGui::PlotLines("Samples", samples, 100);
	ImGui::Text("Sheesh");
	ImGui::Text("New Text");

	ImGui::Combo("List", &m_selectedMethode, ProceduralGen::Names.begin(), (int)ProceduralGen::Names.size());

	//// Lui temporaire a deplacer a l'endroit qui lui correspond.
	//ProceduralGen_t var;
	//if (m_selectedMethode == 0) { var = std::variant_alternative_t<0, ProceduralGen_t>(); }
	//if (m_selectedMethode == 1) { var = std::variant_alternative_t<1, ProceduralGen_t>(); }

	//CheckVariant(var,
	//	[&](FaultFormation obj)
	//	{
	ImGui::Text("Fault Formation");

	ImGui::DragInt("Iteration", &NbrIteration, 1);
	if (NbrIteration <= 0) { NbrIteration = 0; }
	ImGui::DragFloat("Min height", &MinHeight, 1);
	if (MinHeight <= 0) { MinHeight = 0; }
	ImGui::DragFloat("Max height", &MaxHeight, 1);
	if (MaxHeight <= 0) { MaxHeight = 0; }
	ImGui::DragFloat("Filter", &filter, 0.005f, 0.f, 1.f);
	if (ImGui::Button("GenerateTerrain"))
	{
		CurrentTerrain->CreateFaultFormationInternal(NbrIteration, MinHeight, MaxHeight, filter);
	}

	//	},
	//	[&](NoGeneration obj)
	//	{
	//		ImGui::Text("No Generation");
	//		ImGui::TextWrapped("Sorry other methode where not implemented yet sry");
	//	});
}
