/*!*****************************************************************************
/*!*****************************************************************************
\file PrefabPanel.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains function definations for a Hierarchy Panel Editor system 
that lists the entities and its components in the scene
*******************************************************************************/
#include "PrefabPanel.h"
#include <ECSManager.h>
int PrefabPanel::newPrefabCount = 1;


/*!*****************************************************************************
\brief
	Loads the Prefabs

\return
None.
*******************************************************************************/
void PrefabPanel::LoadPrefab()
{
	std::string rootPath = "..\\resources\\Prefabs\\";
	std::filesystem::path m_CurrentDirectory = std::filesystem::path(rootPath);
	for (auto& directory : std::filesystem::directory_iterator(m_CurrentDirectory))
	{
		const auto& path = directory.path();
		if (path.extension() == ".meta")
			continue;
		//serializationManager->LoadPrefab(path.stem().string());
	}
}


/*!*****************************************************************************
\brief
	Initializes the PrefabPanel editor

\return
None.
*******************************************************************************/
void PrefabPanel::Init()
{
	
}
/*!*****************************************************************************
\brief
	Updates the Prefab Panel editor

\return
None.
*******************************************************************************/
void PrefabPanel::Update()
{
	if (ImGui::Begin("Prefab Manager"))
	{
		/*ImGui::BeginTabBar("Prefab ");
		if (ImGui::BeginTabItem("Prefabs: "))
		{*/		
		
			int id = 0;
			for (PrefabPtr p : PrefabManager::GetInstance()->GetPrefab())
			{
				if (ImGui::CollapsingHeader(p->Name().c_str()))
				{
					ImGui::PushID(id++);
					listComponents(p, p->Name());
					ImGui::PopID();
					ImGui::PushID(id++);
					if (ImGui::Button("New Prefabee"))
					{
						newPrefabee(p);
					}
					ImGui::PopID();
					ImGui::PushID(id++);
					if (ImGui::Button("Save Prefab"))
					{
						serializationManager->SavePrefab(p->Name());
					}
					ImGui::PopID();
				}
			}
			ImGui::NewLine();
			if (ImGui::Button("New Prefab"))
			{
				newPrefab();
			}
			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::MenuItem(" Create Prefab"))
				{
					newPrefab();
				}
				ImGui::EndPopup();
			}
		/*}
		ImGui::EndTabItem();*/
	}
	ImGui::End();
}
/*!*****************************************************************************
\brief
	Free the Prefab Panel editor

\return
None.
*******************************************************************************/
void PrefabPanel::Free()
{
	/*for (size_t p = 0; p < mPrefabs.size(); p++)
	{
		delete mPrefabs[p];
	}
	mPrefabs.clear();*/
}

void PrefabPanel::newPrefab()
{
	static int n{1};
	//static Prefab pre(".new Prefab"+n);
	//Prefab* pre = new Prefab("new Prefab"+std::to_string(n));
	//mPrefabs.push_back(pre);

	PrefabPtr newPrefab = PrefabManager::GetInstance()->CreatePrefab();
	newPrefab->Name() = "new Prefab" + std::to_string(n);

	n++;
}
void PrefabPanel::newPrefabee(PrefabPtr pre)
{
	static int n{1};
	Entity b = pre->CreatePrefabee();
	b.GetComponent<General>().name = "Prefabee" + std::to_string(n);
	n++;
}

/*!*****************************************************************************
\brief
	This function sets the selected prefab

\return
None.
*******************************************************************************/
void PrefabPanel::setSelectedPrefab(PrefabPtr p)
{
	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	{
		selectedPrefab = p;
		selectedEntity = nullptr;
		selectedType = 2;
	}
}
/*!*****************************************************************************
\brief
	This function sets the selected entity or prefab

\return
None.
*******************************************************************************/
//void PrefabPanel::setSelected(PrefabPtr p)
//{
//	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
//	{
//		selectedPrefab = p;
//		selectedEntity = nullptr;
//		selectedType = 2;
//	}
//}
/*!*****************************************************************************
\brief
	This function list components for entities or prefabs

\return
None.
*******************************************************************************/

void PrefabPanel::listComponents(PrefabPtr p, std::string _name)
{

	if (p->HasComponent<General>())
	{
		ImGui::Text("General");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<Lifespan>())
	{
		ImGui::Text("Lifespan");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<Transform>())
	{
		ImGui::Text("Transform");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<Sprite>())
	{
		ImGui::Text("Sprite");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<Animation>())
	{
		ImGui::Text("Animation");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<SheetAnimation>())
	{
		ImGui::Text("SheetAnimation");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<Physics2D>())
	{
		ImGui::Text("Physics2D");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<RectCollider>())
	{
		ImGui::Text("RectCollider");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<CircleCollider>())
	{
		ImGui::Text("CircleCollider");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<Edge2DCollider>())
	{
		ImGui::Text("Edge2DCollider");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<Audio>())
	{
		ImGui::Text("Audio");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<Text>())
	{
		ImGui::Text("Text");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<AI>())
	{
		ImGui::Text("AI");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<Script>())
	{
		ImGui::Text("Script");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<Dialogue>())
	{
		ImGui::Text("Dialogue");
		setSelectedPrefab(p);
	}
	if (p->HasComponent<PlayerTmp>())
	{
		ImGui::Text("PlayerTmp");
		setSelectedPrefab(p);
	}
	for (Entity b : p->GetPrefabees())
	{
		if (ImGui::TreeNode(b.GetComponent<General>().name.c_str()))
		{
			ImGui::Text(b.GetComponent<General>().name.c_str());
			ImGui::TreePop();
		}
	}
}


