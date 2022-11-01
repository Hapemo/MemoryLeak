/*!*****************************************************************************
\file LevelEditor.h
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function declarations for a Level Editor system that modifies
Entities and its Components.
*******************************************************************************/
#pragma once
#include "Panel.h"

/*!*****************************************************************************
\brief
	This class encapsulates the functions for the Level Editor
*******************************************************************************/
class InspectorPanel : public Panel
{
public:
	void Init();
	void Update();
	void Free();

	
private:
	void GeneralEditor();
	void LifespanEditor();
	void TransformEditor();
	void SpriteEditor();
	void AnimationEditor();
	void SheetAnimationEditor();
	void Physics2DEditor();
	void RectColliderEditor();
	void CircleColliderEditor();
	void Edge2DColliderEditor();
	void Point2DColliderEditor();
	void AudioEditor();
	void TextEditor();
	void AIEditor();
	void PlayerTmpEditor();

	
	void AddComponent();
	void DeleteEntity();

	Entity e;
	float tmpFloat;
	float tmpVec2[2];
	float tmpVec4[4];
	COMPONENT tempComponent{};

	int addComponentID{};
	const char* componentsList[17]{ "General","Lifespan","Transform", "Sprite" ,"Animation","SheetAnimation","Physics2D",
				"RectCollider" , "CircleCollider" ,"Edge2DCollider" ,"Point2DCollider","Audio" ,"Text","AI", "Script", "Dialogue", "PlayerTmp" };
};
