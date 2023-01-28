/*!*****************************************************************************
\file MonoMethods.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 04-01-2023
\brief
This file contains the function declarations of the class MonoMethods.
MonoMethods are where all the mono internal calls functions that scripts need
to use from the engine is being linked.
*******************************************************************************/

#pragma once
#include "Singleton.h"
#include "InternalCalls.h"
#include <mono/jit/jit.h>

#define MONO MonoMethods::GetInstance()

class MonoMethods : public Singleton<MonoMethods> {
public:
	/*!*****************************************************************************
	\brief
	Registers the internal calls for mono use.
	*******************************************************************************/
	void RegisterCalls();

	/*!*****************************************************************************
	\brief
	MonoString conversion methods.
	*******************************************************************************/
	std::string ConvertFromMonoString(MonoString* _string);
	MonoString* ConvertToMonoString(std::string _string);

	/*!*****************************************************************************
	\brief
	Internal Call functions that uses MonoString.
	*******************************************************************************/
	static void ApplyImpulse(MonoString* _entityName, MonoString* _sceneName, const float _impulseX, const float _impulseY, const float _rotationX, const float _rotationY);
	static void LoadDialogs(MonoString* _filename);
	static MonoString* GetDialogue(int _id);
	static void ChangeGameState(MonoString* _name);
	static bool EntityIsActive(MonoString* _entityName, MonoString* _sceneName);
	static void EntityActivate(MonoString* _entityName, MonoString* _sceneName);
	static void EntityDeactivate(MonoString* _entityName, MonoString* _sceneName);
	static MonoString* EntityGetParent(MonoString* _entityName, MonoString* _sceneName);
	static int EntityGetParentId(MonoString* _entityName, MonoString* _sceneName);
	static MonoString* GetCurrentGameStateName();
	static void PauseScene(MonoString* _name);
	static void PlayScene(MonoString* _name);
	static void SetAnimationSpeed(MonoString* _entityName, MonoString* _sceneName, float _speed);
	static float GetAnimationSpeed(MonoString* _entityName, MonoString* _sceneName);
	static void SetAnimationCurrentIndex(MonoString* _entityName, MonoString* _sceneName, int _index);
	static int GetAnimationCurrentIndex(MonoString* _entityName, MonoString* _sceneName);
	static int GetAnimationFrameCount(MonoString* _entityName, MonoString* _sceneName);
	static void SetAnimationFrameCount(MonoString* _entityName, MonoString* _sceneName, int _count);
	static void SetTexture(MonoString* _entityName, MonoString* _sceneName, MonoString* _path);
	static MonoString* GetTexture(MonoString* _entityName, MonoString* _sceneName);
	static bool EntitiesCollided(MonoString* _entityName1, MonoString* _entityName2, MonoString* _sceneName);
	static bool CheckCollision(MonoString* _entityName1, MonoString* _entityName2, MonoString* _sceneName, bool _dynamicCheck);
	static void StopSound(MonoString* _entityName, MonoString* _sceneName);
	static void PlaySoundOnLoop(MonoString* _entityName, MonoString* _sceneName);
	static void PlayAnySound(MonoString* _name, int _channel);
	static void PlayBGSound(MonoString* _name, int _channel);
	static float GetPosX(MonoString* _entityName, MonoString* _sceneName);
	static float GetPosY(MonoString* _entityName, MonoString* _sceneName);
	static void SetPosX(MonoString* _entityName, MonoString* _sceneName, float _posX);
	static void SetPosY(MonoString* _entityName, MonoString* _sceneName, float _posY);
	static float GetScaleX(MonoString* _entityName, MonoString* _sceneName);
	static float GetScaleY(MonoString* _entityName, MonoString* _sceneName);
	static void SetScaleX(MonoString* _entityName, MonoString* _sceneName, float _scaleX);
	static void SetScaleY(MonoString* _entityName, MonoString* _sceneName, float _scaleY);
	static float GetRotate(MonoString* _entityName, MonoString* _sceneName);
	static void SetRotate(MonoString* _entityName, MonoString* _sceneName, float _rotate);
	static bool ButtonClicked(MonoString* _entityName, MonoString* _sceneName);
	static bool ButtonReleased(MonoString* _entityName, MonoString* _sceneName);
	static bool ButtonHover(MonoString* _entityName, MonoString* _sceneName);
	static void UpdateText(MonoString* _entityName, MonoString* _sceneName, MonoString* _text);
	static void SetTextOffset(MonoString* _entityName, MonoString* _sceneName, float _xoffset, float _yoffset);
	static int GetLineCount(MonoString * _entityName, MonoString * _sceneName);
};
