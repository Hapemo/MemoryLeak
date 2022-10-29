/*!*****************************************************************************
/*!*****************************************************************************
\file LevelEditor.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definations for a Level Editor system that modifies
Entities and its Components.
*******************************************************************************/
#include "HierarchyPanel.h"
#include <ECSManager.h>
void HierarchyPanel::Init()
{

}
void HierarchyPanel::Update()
{
	static int n = 0;
	ImGui::Begin("Scene Manager");
	ImGui::BeginTabBar("Edit Scene ");
	if (ImGui::BeginTabItem("Edit Game: "))
	{
		std::vector<std::string> tag{ "PLAYER","PASSENGER", "ENEMY", "BUILDING","BACKGROUND", "OTHERS" };
		for (int i = 0; i < (int)tag.size(); i++)
		{

			//if (ImGui::TreeNode(tag[i].c_str()))
			if (ImGui::CollapsingHeader(tag[i].c_str()))
			{
				int counter = 0;
				static bool first[20]{};
				for (const Entity& e : mEntities)///////here////////////////////////////////////////////
				{
					if (e.GetComponent<General>().tag != (TAG)i)
						continue;
					++counter;
					const char* lbl = e.GetComponent<General>().name.c_str();
					if (ImGui::TreeNode(lbl))
					{
						if (e.HasComponent<General>())
						{
							ImGui::Text("General");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Lifespan>())
						{
							ImGui::Text("Lifespan");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Transform>())
						{
							ImGui::Text("Transform");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Sprite>())
						{
							ImGui::Text("Sprite");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Animation>())
						{
							ImGui::Text("Animation");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<SheetAnimation>())
						{
							ImGui::Text("SheetAnimation");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Physics2D>())
						{
							ImGui::Text("Physics2D");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<RectCollider>())
						{
							ImGui::Text("RectCollider");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<CircleCollider>())
						{
							ImGui::Text("CircleCollider");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Edge2DCollider>())
						{
							ImGui::Text("Edge2DCollider");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Stuff>())
						{
							ImGui::Text("Stuff");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Audio>())
						{
							ImGui::Text("Audio");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						if (e.HasComponent<Stuff>())
						{
							ImGui::Text("AI");
							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							{
								selectedEntity = &e;
							}
						}
						ImGui::TreePop();

					}
				}
				//ImGui::TreePop();
				if (ImGui::BeginPopupContextWindow(0, 1, false))
				{
					if (ImGui::MenuItem(" Create Entity"))
					{
						Math::Vec2 campos = renderManager->GetWorldCamera().GetPos();
						LOG_INFO("Created new entity");
						Entity e{ ECS::CreateEntity() };
						mEntities.insert(e);
						e.AddComponent(
							General{ "_NEW_" + std::to_string(n), TAG::OTHERS, SUBTAG::NOSUBTAG, true },
							Transform{ {150,150}, 0, campos },
							Sprite{ Color{0,255,0,100}, SPRITE::CIRCLE, 0 },
							RectCollider{ { 0.f, 0.f }, {1.f,1.f}, true });
						n++;
					}
					ImGui::EndPopup();
				}

			}
		}
		/*if (ImGui::TreeNode("Scene 2"))
		{
			ImGui::Text("Nothing");
			ImGui::TreePop();
		}*/
		ImGui::EndTabItem();
		if (ImGui::Button("New object"))
		{
			Math::Vec2 campos = renderManager->GetWorldCamera().GetPos();
			LOG_INFO("Created new entity");
			Entity e{ ECS::CreateEntity() };
			mEntities.insert(e);
			e.AddComponent(
				General{ "_NEW_" + std::to_string(n), TAG::OTHERS, SUBTAG::NOSUBTAG, true },
				Transform{ {150,150}, 0, campos },
				Sprite{ Color{0,255,0,100}, SPRITE::CIRCLE, 0 },
				RectCollider{ { 0.f, 0.f }, {1.f,1.f}, true });
			n++;
		}
	}
	ImGui::EndTabBar();
	ImGui::End();
}
void HierarchyPanel::Free()
{

}