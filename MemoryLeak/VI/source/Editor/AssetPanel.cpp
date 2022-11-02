/*!*****************************************************************************
/*!*****************************************************************************
\file LevelEditor.cpp
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function declarations for a AssetPanel that view recources
*******************************************************************************/
#include "AssetPanel.h"
#include <ECSManager.h>
/*!*****************************************************************************
\brief
	Initializes the Asset Panel editor

\return
None.
*******************************************************************************/
void AssetPanel::Init()
{

}
/*!*****************************************************************************
\brief
	Update the Asset Panel editor

\return
None.
*******************************************************************************/
void AssetPanel::Update()
{
	GLuint my_image_texture = spriteManager->GetTextureID("Textures\\Icons\\folderIcon.png");
	GLuint my_image2_texture = 0;
	std::string rootPath = "..\\resources";
	ImVec2 buttonSize = { 100,100 };
	ImGui::Begin("Asset Manager");
	ImGui::BeginTabBar("Assets ");
	if (ImGui::BeginTabItem("Content Browser")) {
		// switch to the newly selected tab
		static std::filesystem::path m_CurrentDirectory = std::filesystem::path(rootPath);
		if (m_CurrentDirectory != std::filesystem::path(rootPath))
		{
			if (ImGui::Button("<- BACK", buttonSize))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}
		for (auto& directory : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directory.path();
			auto relativePath = std::filesystem::relative(path, rootPath);
			std::string filename = relativePath.filename().string();
			ImGui::Columns(3);

			ImTextureID folderIcon = (void*)(intptr_t)my_image_texture;
			if (directory.is_directory())
			{
				ImGui::ImageButton(folderIcon, buttonSize, ImVec2(0, 1), ImVec2(1, 0));
			}
			else
			{
				texPath = directory.path().string();
				texPath = texPath.substr(13);
				texExt = directory.path().extension().string();
				texfilename = directory.path().stem().string();
				if (texExt == ".meta")
					continue;
				my_image2_texture = spriteManager->GetTextureID(texPath);
				if (my_image2_texture)
				{
					ImTextureID textureImage = (void*)(intptr_t)my_image2_texture;
					ImGui::ImageButton(textureImage, buttonSize, ImVec2(0, 1), ImVec2(1, 0));
					if (texExt == ".png" || texExt == ".jpg")
					{
						if (ImGui::BeginDragDropSource())
						{
							const wchar_t* itemPath = (wchar_t*)texPath.c_str();
							ImGui::SetDragDropPayload("TEXTURES", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t), ImGuiCond_Once);
							ImGui::EndDragDropSource();
						}
					}
					
				}
				else
				{
					ImGui::Button(filename.c_str(), buttonSize);
					if (texExt == ".wav")
					{
						if (ImGui::BeginDragDropSource())
						{
							const wchar_t* itemPath = (wchar_t*)texfilename.c_str();
							ImGui::SetDragDropPayload("AUDIO", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t), ImGuiCond_Once);
							ImGui::EndDragDropSource();
						}
					}
					else if (texExt == ".cpp")
					{
						if (ImGui::BeginDragDropSource())
						{
							const wchar_t* itemPath = (wchar_t*)texfilename.c_str();
							ImGui::SetDragDropPayload("SCRIPT", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t), ImGuiCond_Once);
							ImGui::EndDragDropSource();
						}
					}
					else if (texExt == ".ttf")
					{
						if (ImGui::BeginDragDropSource())
						{
							const wchar_t* itemPath = (wchar_t*)texfilename.c_str();
							ImGui::SetDragDropPayload("FONT", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t), ImGuiCond_Once);
							ImGui::EndDragDropSource();
						}
					}
				}
			}
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (directory.is_directory())
					m_CurrentDirectory /= path.filename();
				else
				{
					if (texExt == ".json")
					{
						
						if (texfilename.substr(0, 6) == "Dialog")
						{
							serializationManager->LoadDialogs(texfilename);
							SetPannelIsActive(E_PANELID::DIALOGUE ,true);
						}
						else if (texfilename.substr(0, 5) == "Scene")
						{
							ECS::DestroyAllEntities();
							SceneReset();
							serializationManager->LoadScene(texfilename);
						}
					}
					else if (texExt == ".png")
					{
					}
					else if (texExt == ".wav")
					{
						//audioManager->Play(texfilename);
						std::cout << "play " << texfilename << "\n";
						audioManager->PlayAnySound(texfilename, 16);
					}

				}
			}
			ImGui::Text(filename.c_str());
			ImGui::NextColumn();
		}
		ImGui::Columns(1);
		ImGui::Text("   ");
		ImGui::EndTabItem();
	}
	ImGui::EndTabBar();
	ImGui::End();
}
/*!*****************************************************************************
\brief
	Free the Asset Panel editor

\return
None.
*******************************************************************************/
void AssetPanel::Free()
{

}