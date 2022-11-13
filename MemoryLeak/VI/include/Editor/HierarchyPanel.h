/*!*****************************************************************************
\file HierarchyPanel.h
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-10-2022
\brief
This file contains function declarations for a Hierarchy Panel Editor system 
that lists the entities and its components in the scene
*******************************************************************************/
#pragma once
#include "Panel.h"

/*!*****************************************************************************
\brief
	This class encapsulates the functions for the Level Editor
*******************************************************************************/
class HierarchyPanel : public Panel
{
public:
	void Init();
	void Update();
	void Free();

	
private:
	void newEntity();
	/*void newPrefab();
	void newPrefabee(Prefab*);
	void setSelectedPrefab( Prefab* p);*/

	void setSelectedEntity(const Entity* e);

	//void setSelected(Entity* e);
	void listComponents(const Entity* e, std::string _name);
	static int newEntityCount;
	std::vector<std::string> tag;
};