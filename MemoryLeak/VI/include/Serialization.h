/*!*****************************************************************************
\file Serialization.h
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function declarations for a Serialization system that modifies
Entities and its Components.
*******************************************************************************/
#pragma once
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"
#include <ECS_tools.h>

#include "document.h"
#include "writer.h"
#include <istreamwrapper.h>
#include "stringbuffer.h"
class SerializationManager : public System
{
public:
	void LoadScene();
	void SaveScene();
	void LoadDialogs();
	void SaveDialogs();
private:
};