/*!*****************************************************************************
\file ScriptManager.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 19-10-2022
\brief
This file contains the function definitions of the class ScriptManager.
The ScriptManager class handles the C# scripting for the engine.
*******************************************************************************/

#include "ScriptComponent.h"

/*!*****************************************************************************
\brief
Default constructor and destructor.
*******************************************************************************/
ScriptComponent::ScriptComponent(std::string _key, Entity* _entity) : mBehaviourKey(_key), mOwner(_entity) {}
ScriptComponent::~ScriptComponent() {

}

void ScriptComponent::SetBehaviourKey(std::string _behaviourKey) {
	mBehaviourKey = _behaviourKey;
}
void ScriptComponent::SetOwner(Entity* _owner) {
	mOwner = _owner;
}
