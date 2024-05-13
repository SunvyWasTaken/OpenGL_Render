#include "ExempleToolImpl.h"

#include "Core/ProceduralGeneration.h"
#include "Procedural/BaseTerrain/BaseTerrain.h"

#include <imgui.h>
#include <vector>
#include <string>
#include <cstring>


ExempleToolImpl::ExempleToolImpl(const std::string& title, bool open)
	: ToolWindow(title, open), CurrentTerrain(nullptr)
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

	//std::vector<const char*> charArray;
	//for (const std::string& name : ProceduralGen::GetTypeNames())
	//{
	//	charArray.push_back(name.c_str());
	//}
	//// Allocate memory for the actual array (needs manual management)
	//const char* result[charArray.size()];
	//std::strcpy(result, *charArray.begin());


	//ImGui::Combo("List", &m_selectedMethode, result, IM_ARRAYSIZE(result));
	//if (m_selectedMethode == 0)
	//{
	//	CurrentTerrain->CurrentGenerationMethode = FaultFormation();
	//}
	//else if (m_selectedMethode == 1)
	//{
	//	CurrentTerrain->CurrentGenerationMethode = NoErrosion();
	//}

	//CheckVariant(CurrentTerrain->CurrentGenerationMethode,
	//	[](FaultFormation obj) {
	//		ImGui::Text("Fault Formation");
	//	},
	//	[](NoErrosion obj)
	//	{
	//		ImGui::Text("No Errosion");
	//	});
	ImGui::InputInt("Iteration", &NbrIteration);
	if (ImGui::Button("RegenaretedTerrain"))
	{
		OnRegeneratedTerrain.Broadcast(NbrIteration);
	}
}
