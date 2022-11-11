/*!*****************************************************************************
\file PrefabPanel.h
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
class PrefabPanel : public Panel
{
public:
	void Init();
	void Update();
	void Free();

	
private:
	void newPrefab();
	void newPrefabee(Prefab*);

	void setSelectedPrefab( Prefab* p);
	template<typename T>
	void listComponents(const T* e, std::string _name);
	void setSelected(const void* e);
	static int newPrefabCount;
};