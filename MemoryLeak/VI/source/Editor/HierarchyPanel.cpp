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
		int id = 0;
		if (ImGui::BeginTabBar("GameState"))
		{
			for (int g = 0; g < allEntities.size(); g++)
			{
				//ImGui::PushID(id++);
				if (ImGui::BeginTabItem(allNames[g].first.c_str()))
				{
					//ImGui::PopID();
					selectedGameState = g;
					ImGui::InputText("GameState Name", &allNames[g].first);
					std::string saveGSbtn = "SAVE " + allNames[g].first + " GameState";
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.f, 0.5f, 0.f, 1.0f });
					if (ImGui::Button(saveGSbtn.c_str()))
					{
						serializationManager->SaveGameState(allNames[g], allEntities[g]);
					}
					ImGui::PopStyleColor();
					std::string removeGSbtn = "REMOVE " + allNames[g].first + " GameState";
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.f, 0.f, 1.0f });
					if (ImGui::Button(removeGSbtn.c_str()))
					{
						allNames.erase(allNames.begin() + g);
						allEntities.erase(allEntities.begin() + g);
						selectedGameState = (int)allEntities.size() - 1;
						ImGui::EndTabItem();
						ImGui::PopStyleColor();
						break;
					}
					ImGui::PopStyleColor();
					if (ImGui::BeginTabBar("Scenes"))
					{
						int layer = 0;
						int order = 0;
						bool isActive = true;
						for (int s = 0; s < allEntities[g].size(); s++)
						{
							//ImGui::PushID(id++);
							if (ImGui::BeginTabItem(allNames[g].second[s].c_str()))
							{
								//ImGui::PopID();
								selectedScene = s;
								ImGui::InputText("Scene Name", &allNames[selectedGameState].second[selectedScene]);
								std::string saveScenebtn = "SAVE " + allNames[g].second[s] + " Scene";
								ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.f, 0.5f, 0.f, 1.0f });
								if (ImGui::Button(saveScenebtn.c_str()))
								{
									serializationManager->SaveScene(allNames[g].second[s], allEntities[g][s]);
								}
								ImGui::PopStyleColor();
								std::string removeScenebtn = "REMOVE " + allNames[g].second[s] + " Scene";
								ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.f, 0.f, 1.0f });
								if (ImGui::Button(removeScenebtn.c_str()))
								{
									allNames[g].second.erase(allNames[g].second.begin() + s);
									allEntities[g].erase(allEntities[g].begin() + s);
									selectedScene = (int)allEntities[g].size() - 1;
									ImGui::EndTabItem();
									ImGui::PopStyleColor();
									break;
								}
								ImGui::PopStyleColor();
								if (ImGui::CollapsingHeader("Scene Camera"))
								{
									ImGui::Checkbox("isActive", &isActive);
									float pos[2] = { renderManager->GetGameCamera().GetPos().x , renderManager->GetGameCamera().GetPos().y };
									ImGui::InputFloat2("Camera Pos", pos);
									renderManager->GetGameCamera().SetPos(Math::Vec2{ pos[0], pos[1] });
									float zoom = renderManager->GetGameCamera().GetZoom();
									ImGui::InputFloat("Camera Zoom", &zoom);
									renderManager->GetGameCamera().SetZoom(zoom);
									ImGui::InputInt("Layer", &(++layer));
									ImGui::InputInt("Order", &(++order));
								}
								for (int i = 0; i < (int)tag.size(); i++)
								{

									if (ImGui::CollapsingHeader(tag[i].c_str()))
									{
										//int id = 0;
										for (const Entity& e : allEntities[g][s])
										{
											if (e.GetComponent<General>().tag != (TAG)i)
												continue;
											
											for (int l = -1; l < 255; l++)
											{
												if (l == -1)
												{
													if (!e.HasComponent<Sprite>())
													{
														ImGui::PushID(id++);
														listComponents(&e, e.GetComponent<General>().name);
														ImGui::PopID();
													}
												}
												else
												{
													if (e.GetComponent<Sprite>().layer != l)
														continue;
													std::string name = "(" + std::to_string(l) + ") " + e.GetComponent<General>().name;
													ImGui::PushID(id++);
													listComponents(&e, name);
													ImGui::PopID();
												}
											}
										}
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
								ImGui::NewLine();
								if (ImGui::Button("NEW Entity"))
								{
									newEntity();
								}
								ImGui::EndTabItem(); //end scene item

							}
							//ImGui::PopID();
						}
						ImGui::EndTabBar(); //for scene
					}
					std::string newScenebtn = "NEW "+ allNames[g].first  +" Scene";
					if (ImGui::Button(newScenebtn.c_str()))
					{//FUNCTION GS SCENE
						static int sn = 1;
						std::set<Entity> newSecen{};
						allEntities[g].push_back(newSecen);
						allNames[g].second.push_back("NewScene" + std::to_string(sn++));
						selectedScene = (int)allEntities[g].size() - 1;
					}
					ImGui::EndTabItem(); //forGS
				}
				//else
					//ImGui::PopID();
			}
			ImGui::EndTabBar();
		}

		if (ImGui::Button("NEW GameState"))
		{//FUNCTION GS SCENE
			static int gn = 1;
			std::vector < std::set<Entity>> newGS{};
			allEntities.push_back(newGS);
			std::pair< std::string, std::vector<std::string>> newGSNmae{};
			newGSNmae.first = "NewGameState" + std::to_string(gn++);
			allNames.push_back(newGSNmae);
			selectedGameState = (int)allEntities.size() - 1;
		}



		////IF Change Scene
		//if (selectedPrevious != (selectedGameState*10 + selectedScene))
		//{
		//	for (const Entity& e : *myEntities)
		//	{
		//		e.GetComponent<General>().isActive = false;
		//	}
		//	if (selectedGameState < allEntities.size())
		//	{
		//		if (selectedScene < allEntities[selectedGameState].size())
		//		{
		//			for (const Entity& e : allEntities[selectedGameState][selectedScene])
		//			{
		//				e.GetComponent<General>().isActive = true;
		//			}
		//		}
		//	}
		//	LOG_INFO("Selected Game State: " + std::to_string(selectedGameState));
		//	LOG_INFO("Selected Scene: " + std::to_string(selectedScene));
		//	SceneReset();
		//}
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
	(allEntities[selectedGameState][selectedScene]).insert(e);
	e.AddComponent(
		General{ "_NEW_" + std::to_string(newEntityCount), TAG::OTHERS, SUBTAG::NOSUBTAG, true , false},
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
		if (e->HasComponent<LayerCollider>())
		{
			ImGui::Text("LayerCollider");
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

