/*!*****************************************************************************
\file Start_background.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
Scene to control the background
*******************************************************************************/
#pragma once
#include "pch.h"
#include "Scene.h"
#include "Input.h"

class Start_background : public Scene, public Singleton<Start_background> {
public:
	//------------------------------------------------------------------------------
	// Virtual functions from base class Scene. Refer to class Scene for details
	//------------------------------------------------------------------------------
	virtual void Init();
	virtual void Update();
	virtual void Reset();
	virtual void Clear();

private:


};











