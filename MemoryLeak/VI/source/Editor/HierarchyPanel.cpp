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
int HierarchyPanel::newEntityCount = 0;
/*!*****************************************************************************
\brief
	Initializes the HierarchyPanel editor

\return
None.
*******************************************************************************/
void HierarchyPanel::Init()
{
	//to be read from file in the future
	tag = { "PLAYER","PASSENGER", "ENEMY", "BUILDING","BACKGROUND", "OTHERS" };
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
	ImGui::BeginTabBar("Edit Scene ");
	if (ImGui::BeginTabItem("Scene: "))
	{
		for (int i = 0; i < (int)tag.size(); i++)
		{
			if (ImGui::CollapsingHeader(tag[i].c_str()))
			{
				for (const Entity& e : *myEntities)
				{
					if (e.GetComponent<General>().tag != (TAG)i)
						continue;
					const char* lbl = e.GetComponent<General>().name.c_str();
					if (ImGui::TreeNode(lbl))
					{
						if (e.HasComponent<General>())
						{
							ImGui::Text("General");
							setSelectedEntity(&e);
						}
						if (e.HasComponent<Lifespan>())
						{
							ImGui::Text("Lifespan");
							setSelectedEntity(&e);
						}
						if (e.HasComponent<Transform>())
						{
							ImGui::Text("Transform");
							setSelectedEntity(&e);
						}
						if (e.HasComponent<Sprite>())
						{
							ImGui::Text("Sprite");
							setSelectedEntity(&e);
						}
						if (e.HasComponent<Animation>())
						{
							ImGui::Text("Animation");
							setSelectedEntity(&e);
						}
						if (e.HasComponent<SheetAnimation>())
						{
							ImGui::Text("SheetAnimation");
							setSelectedEntity(&e);
						}
						if (e.HasComponent<Physics2D>())
						{
							ImGui::Text("Physics2D");
							setSelectedEntity(&e);
						}
						if (e.HasComponent<RectCollider>())
						{
							ImGui::Text("RectCollider");
							setSelectedEntity(&e);
						}
						if (e.HasComponent<CircleCollider>())
						{
							ImGui::Text("CircleCollider");
							setSelectedEntity(&e);
						}
						if (e.HasComponent<Edge2DCollider>())
						{
							ImGui::Text("Edge2DCollider");
							setSelectedEntity(&e);
						}
						if (e.HasComponent<Audio>())
						{
							ImGui::Text("Audio");
							setSelectedEntity(&e);
						}
						if (e.HasComponent<Text>())
						{
							ImGui::Text("Stuff");
							setSelectedEntity(&e);
						}
						if (e.HasComponent<Stuff>())
						{
							ImGui::Text("AI");
							setSelectedEntity(&e);
						}
						ImGui::TreePop();

					}
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
		Sprite{ Color{0,255,0,100}, SPRITE::CIRCLE, 0 },
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
	}
}