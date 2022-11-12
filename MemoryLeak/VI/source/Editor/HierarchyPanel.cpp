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
	if (ImGui::Begin("Hierarchy Manager"))
	{
		ImGui::BeginTabBar("Hierarchy ");
		if (ImGui::BeginTabItem("Scene 1: "))
		{
			for (int i = 0; i < (int)tag.size(); i++)
			{
				
				if (ImGui::CollapsingHeader(tag[i].c_str()))
				{
					int id = 0;
					for (const Entity& e : *myEntities)
					{
						if (e.GetComponent<General>().tag != (TAG)i)
							continue;
						ImGui::PushID(id);
						listComponents(&e, e.GetComponent<General>().name);
						ImGui::PopID();
						id++;
					}
				}
			}
			ImGui::EndTabItem();
			ImGui::NewLine();
			if (ImGui::Button("New Entity"))
			{
				newEntity();
			}
		}
			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::MenuItem(" Create Entity"))
				{
					newEntity();
				}
				ImGui::EndPopup();
			}
		ImGui::EndTabBar();
	}
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
		Sprite{ Color{0,255,0,255}, SPRITE::CIRCLE, 0,highestLayer },
		RectCollider{ { 0.f, 0.f }, {1.f,1.f}, true });
	newEntityCount++;
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
		selectedType = 1;
		aspect = false;
	}
}

/*!*****************************************************************************
\brief
	This function sets the selected entity or prefab

\return
None.
*******************************************************************************/
//void HierarchyPanel::setSelected(Entity* e)
//{
//	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
//	{
//		selectedEntity = e;
//		selectedPrefab = nullptr;
//		selectedType = 1;
//		
//	}
//}
/*!*****************************************************************************
\brief
	This function list components for entities or prefabs

\return
None.
*******************************************************************************/

void HierarchyPanel::listComponents(const Entity* e, std::string _name)
{
	
	if (ImGui::TreeNode(_name.c_str()))
	{
		if (e->HasComponent<General>())
		{
			ImGui::Text("General");
			setSelectedEntity(e);
		}
		if (e->HasComponent<Lifespan>())
		{
			ImGui::Text("Lifespan");
			setSelectedEntity(e);
		}
		if (e->HasComponent<Transform>())
		{
			ImGui::Text("Transform");
			setSelectedEntity(e);
		}
		if (e->HasComponent<Sprite>())
		{
			ImGui::Text("Sprite");
			setSelectedEntity(e);
		}
		if (e->HasComponent<Animation>())
		{
			ImGui::Text("Animation");
			setSelectedEntity(e);
		}
		if (e->HasComponent<SheetAnimation>())
		{
			ImGui::Text("SheetAnimation");
			setSelectedEntity(e);
		}
		if (e->HasComponent<Physics2D>())
		{
			ImGui::Text("Physics2D");
			setSelectedEntity(e);
		}
		if (e->HasComponent<RectCollider>())
		{
			ImGui::Text("RectCollider");
			setSelectedEntity(e);
		}
		if (e->HasComponent<CircleCollider>())
		{
			ImGui::Text("CircleCollider");
			setSelectedEntity(e);
		}
		if (e->HasComponent<Edge2DCollider>())
		{
			ImGui::Text("Edge2DCollider");
			setSelectedEntity(e);
		}
		if (e->HasComponent<Audio>())
		{
			ImGui::Text("Audio");
			setSelectedEntity(e);
		}
		if (e->HasComponent<Text>())
		{
			ImGui::Text("Text");
			setSelectedEntity(e);
		}
		if (e->HasComponent<AI>())
		{
			ImGui::Text("AI");
			setSelectedEntity(e);
		}
		if (e->HasComponent<Script>())
		{
			ImGui::Text("Script");
			setSelectedEntity(e);
		}
		if (e->HasComponent<Dialogue>())
		{
			ImGui::Text("Dialogue");
			setSelectedEntity(e);
		}
		if (e->HasComponent<PlayerTmp>())
		{
			ImGui::Text("PlayerTmp");
			setSelectedEntity(e);
		}
		ImGui::TreePop();
	}
	setSelectedEntity(e);
}

