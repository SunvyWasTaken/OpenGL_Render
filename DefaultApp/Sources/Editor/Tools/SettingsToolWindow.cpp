#include "SettingsToolWindow.h"
#include "Procedural/BaseTerrain/BaseTerrain.h"

#include <imgui.h>
#include <vector>
#include <string>
#include <cstring>

namespace
{
	static int TerrainSize = 500;
	static int NbrIteration = 1000;
	static float MinHeight = 0.f;
	static float MaxHeight = 50.f;
	static float filter = 0.75f;
}

SettingsToolWindow::SettingsToolWindow(const std::string& title, bool open, Point2Di position, Point2Di size)
	: ToolWindow(title, open, position, size), CurrentTerrain(nullptr), m_selectedMethode(0), NbrIteration(1000),
	currentMidDisData(std::unique_ptr<MidDisData>(new MidDisData()))
{
}

SettingsToolWindow::~SettingsToolWindow()
{
	
}



void SettingsToolWindow::Draw()
{
	//ToolWindow::Draw();
	ImgUISpacing(0, 10);
	ImGui::Text("Generation Method");
	ImGui::Combo(" ", &m_selectedMethode, ProceduralGen::Names().begin(), (int)ProceduralGen::Names().size());
	if (m_selectedMethode != CurrentTerrain->GetMethodeIndex())
	{
		CurrentTerrain->SetGenMethode(m_selectedMethode);
	}

	ImGui::Separator();
	ImgUISpacing(0, 10);

	ImGui::Text("Parameters");

	CheckVariant(CurrentTerrain->m_GenerationMethode,
		[&](FaultFormation)
		{
			ImGui::DragInt("Iteration", &NbrIteration, 1);
			if (NbrIteration <= 0) { NbrIteration = 0; }
			ImGui::DragFloat("Min height", &MinHeight, 1);

			if (MinHeight <= 0) { MinHeight = 0; }
			ImGui::DragFloat("Max height", &MaxHeight, 1);
			if (MaxHeight <= 0) { MaxHeight = 0; }
			ImGui::SliderFloat("Filter", &filter, 0.01f, 0.99f, "%.2f");
			if (ImGui::Button("GenerateTerrain"))
			{
				CurrentTerrain->GenerateProceduralTerrain<FaultFormation>(NbrIteration, MinHeight, MaxHeight, filter);
			}

		},
		[&](MidpointDispTerrain)
		{
			int size = CurrentTerrain->GetTerrainSize();
			float minRoughness = 0.f;
			float maxRoughness = 0.f;
			if (size <= 128)
			{
				minRoughness = 0.01f;
				maxRoughness = 0.2f;
			}
			else if (size > 128 && size <= 512)
			{
				minRoughness = 0.02f;
				maxRoughness = 0.4f;
			}
			else
			{
				minRoughness = 0.05f;
				maxRoughness = 0.8f;
			}
			if (currentMidDisData->roughness < minRoughness || currentMidDisData->roughness > maxRoughness)
			{
				currentMidDisData->roughness = minRoughness + ((minRoughness - maxRoughness) / 2.f);
			}
			ImGui::SliderFloat("Rougness", &currentMidDisData->roughness, minRoughness, maxRoughness, "%.2f");

			ImGui::DragFloat("Min height", &currentMidDisData->minHeight, 1);

			if (currentMidDisData->minHeight <= 0) { currentMidDisData->minHeight = 0; }
			ImGui::DragFloat("Max height", &currentMidDisData->maxHeight, 1);
			if (currentMidDisData->maxHeight <= 0) { currentMidDisData->maxHeight = 0; }

			if (ImGui::Button("GenerateTerrain"))
			{
				CurrentTerrain->GenerateProceduralTerrain<MidpointDispTerrain>(currentMidDisData->roughness, currentMidDisData->minHeight, currentMidDisData->maxHeight);
			}
		},
		[&](NoGeneration)
		{
			ImGui::Text("No Generation");
			ImGui::TextWrapped("Sorry other methode where not implemented yet sry");
		}
	);
}
