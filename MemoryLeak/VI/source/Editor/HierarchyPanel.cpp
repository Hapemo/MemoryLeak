/*!*****************************************************************************
/*!*****************************************************************************
\file HierarchyPanel.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains function definations for a Hierarchy Panel Editor system 
that lists the entities and its components in the scene
*******************************************************************************/
#include "HierarchyPanel.h"
#include <ECSManager.h>
int HierarchyPanel::newEntityCount = 1;
/*!*****************************************************************************
\brief
	Initializes the HierarchyPanel editor

\return
None.
*******************************************************************************/
void HierarchyPanel::Init()
{
	//to be read from file in the future
	tag = { "PLAYER","PASSENGER", "ENEMY", "BUILDING","BACKGROUND", "ENVIRONMENT","EFFECTS","PREFABS","OTHERS" };
}
/*!*****************************************************************************
\brief
	Updates the Hierarchy Panel editor

\return
None.
*******************************************************************************/
void HierarchyPanel::Update()
{
	ImGui::Begin("Hierarchy Manager");
	ImGui::BeginTabBar("Hierarchy ");
	if (ImGui::BeginTabItem("Scene 1: "))
	{
		for (int i = 0; i < (int)tag.size(); i++)
		{
			if (ImGui::CollapsingHeader(tag[i].c_str()))
			{
				for (const Entity& e : *myEntities)
				{
					if (e.GetComponent<General>().tag != (TAG)i)
						continue;
					listComponents(&e, e.GetComponent<General>().name);
					
				}
			}
		}
		ImGui::EndTabItem();
		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem(" Create Entity"))
			{
				newEntity();
			}
			ImGui::EndPopup();
		}
		if (ImGui::Button("New Entity"))
		{
			newEntity();
		}
		if (ImGui::Button("New Prefab")) 
		{
			newPrefab();
		}
		for (Prefab* p: mPrefabs)
		{
			if (ImGui::CollapsingHeader(p->Name().c_str()))
			{
				listComponents(p, p->Name());
				if (ImGui::Button("New Prefabee"))
				{
					newPrefabee(p);
				}
			}
			
		}
	}
	ImGui::EndTabBar();
	ImGui::End();
}
/*!*****************************************************************************
\brief
	Free the Hierarchy Panel editor

\return
None.
*******************************************************************************/
void HierarchyPanel::Free()
{

}
/*!*****************************************************************************
\brief
	This function creates a new entity

\return
None.
*******************************************************************************/
void HierarchyPanel::newEntity()
{
	Math::Vec2 campos = renderManager->GetWorldCamera().GetPos();
	LOG_INFO("Created new entity");
	Entity e{ ECS::CreateEntity() };
	(*myEntities).insert(e);
	e.AddComponent(
		General{ "_NEW_" + std::to_string(newEntityCount), TAG::OTHERS, SUBTAG::NOSUBTAG, true },
		Transform{ {150,150}, 0, campos },
		Sprite{ Color{0,255,0,100}, SPRITE::CIRCLE, 0,highestLayer },
		RectCollider{ { 0.f, 0.f }, {1.f,1.f}, true });
	newEntityCount++;
}
/*!*****************************************************************************
\brief
	This function creates a new entity

\return
None.
*******************************************************************************/
void HierarchyPanel::newPrefab()
{
	static int n{1};
	Prefab* pre = new Prefab("new Prefab"+std::to_string(n));
	//static Prefab pre("new Prefab"+n);
	mPrefabs.push_back(pre);
	n++;
}
void HierarchyPanel::newPrefabee(Prefab* pre)
{
	static int n{1};
	Entity b = pre->CreatePrefabee();
	b.GetComponent<General>().name = "Prefabee" + std::to_string(n);
	n++;
}
/*!*****************************************************************************
\brief
	This function sets the selected entity

\return
None.
*******************************************************************************/

void HierarchyPanel::setSelectedEntity(const Entity* e)
{
	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	{
		selectedEntity = e;
		selectedPrefab = nullptr;
	}
}
/*!*****************************************************************************
\brief
	This function sets the selected prefab

\return
None.
*******************************************************************************/
void HierarchyPanel::setSelectedPrefab( Prefab* p)
{
	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	{
		selectedPrefab = p;
		selectedEntity = nullptr;
	}
}
/*!*****************************************************************************
\brief
	This function sets the selected entity or prefab

\return
None.
*******************************************************************************/
void HierarchyPanel::setSelected(const void* e)
{
	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	{
		selected = e;
		if (selectedType == 1)
		{
			selectedEntity = static_cast<const Entity*>(e);
			selectedPrefab = nullptr;
		}
		else if (selectedType == 2)
		{
			selectedPrefab = const_cast<Prefab*>(static_cast<const Prefab*>(e));
			selectedEntity = nullptr; 
		}
	}
}
/*!*****************************************************************************
\brief
	This function list components for entities or prefabs

\return
None.
*******************************************************************************/
template<typename T>
void HierarchyPanel::listComponents(const T* e, std::string _name)
{
	
	if (ImGui::TreeNode(_name.c_str()))
	{
		if (std::is_same<T, Entity>::value)
		{
			selectedType = 1;
		}
		else if (std::is_same<T, Prefab>::value)
		{
			selectedType = 2;
		}
		if (e->HasComponent<General>())
		{
			ImGui::Text("General");
			setSelected(e);
		}
		if (e->HasComponent<Lifespan>())
		{
			ImGui::Text("Lifespan");
			setSelected(e);
		}
		if (e->HasComponent<Transform>())
		{
			ImGui::Text("Transform");
			setSelected(e);
		}
		if (e->HasComponent<Sprite>())
		{
			ImGui::Text("Sprite");
			setSelected(e);
		}
		if (e->HasComponent<Animation>())
		{
			ImGui::Text("Animation");
			setSelected(e);
		}
		if (e->HasComponent<SheetAnimation>())
		{
			ImGui::Text("SheetAnimation");
			setSelected(e);
		}
		if (e->HasComponent<Physics2D>())
		{
			ImGui::Text("Physics2D");
			setSelected(e);
		}
		if (e->HasComponent<RectCollider>())
		{
			ImGui::Text("RectCollider");
			setSelected(e);
		}
		if (e->HasComponent<CircleCollider>())
		{
			ImGui::Text("CircleCollider");
			setSelected(e);
		}
		if (e->HasComponent<Edge2DCollider>())
		{
			ImGui::Text("Edge2DCollider");
			setSelected(e);
		}
		if (e->HasComponent<Audio>())
		{
			ImGui::Text("Audio");
			setSelected(e);
		}
		if (e->HasComponent<Text>())
		{
			ImGui::Text("Text");
			setSelected(e);
		}
		if (e->HasComponent<AI>())
		{
			ImGui::Text("AI");
			setSelected(e);
		}
		if (e->HasComponent<Script>())
		{
			ImGui::Text("Script");
			setSelected(e);
		}
		if (e->HasComponent<Dialogue>())
		{
			ImGui::Text("Dialogue");
			setSelected(e);
		}
		if (e->HasComponent<PlayerTmp>())
		{
			ImGui::Text("PlayerTmp");
			setSelected(e);
		}
		ImGui::TreePop();
	}
}

