/*!*****************************************************************************
\file ScriptComponent.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 24-10-2022
\brief
This file contains the function declarations of the class ScriptComponent.
The ScriptComponent class handles the C# scripting for the engine.
*******************************************************************************/

#pragma once
#include "ECS_items.h"
#include <string>
#include <vector>

// allows making bahaviour objects
class ScriptComponent
{
protected:
	// holds the behaviour index of the scripts container in the LogicSystem
	std::string mBehaviourKey;
	Entity* mOwner;
public:
	/*!*****************************************************************************
	\brief
	Default constructor and destructor.
	*******************************************************************************/
	ScriptComponent(std::string _key, Entity* _entity);
	~ScriptComponent();

	/*!*****************************************************************************
	\brief
	Delete copy constructor.
	*******************************************************************************/
	ScriptComponent(const ScriptComponent&) = delete;
	const ScriptComponent& operator=(const ScriptComponent&) = delete;

	void SetBehaviourKey(std::string _behaviourKey);
	void SetOwner(Entity* _owner);

	inline std::string GetBehaviourKey() noexcept {
		return mBehaviourKey;
	}
	inline Entity* GetOwner() noexcept {
		return mOwner;
	}
};
