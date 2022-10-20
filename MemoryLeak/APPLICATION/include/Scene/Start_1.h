/*!*****************************************************************************
\file Start_1.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
First scene created.
*******************************************************************************/
#pragma once
#include "pch.h"
#include "Scene.h"
#include "Input.h"

class Start_1 : public Scene, public Singleton<Start_1> {
public:
	//------------------------------------------------------------------------------
	// Virtual functions from base class Scene. Refer to class Scene for details
	//------------------------------------------------------------------------------
	virtual void Init();
	virtual void Update();
	virtual void Reset();
	virtual void Clear();

private:
	/*!*****************************************************************************
	\brief
	Updates or reset entity's lifespan
	
	\param std::set<Entity>
	Entities to operate on

	\param KEY
	Key press to operate on these entities
	*******************************************************************************/
	void ControlEntityLifespan(std::set<Entity>, E_KEY);


};











