/*!*****************************************************************************
\file PassengerScript.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Course: CSD2400
\par Group: Memory Leak Studios
\date 27-11-2022
\brief
Allow the passenger to be picked up and dropped off by the player
*******************************************************************************/
#pragma once

#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

class PassengerScript : public ScriptComponent {
private:
	std::string name{ "PassengerScript" };
	bool pickedUp;
	bool pickingUp;
	bool readyToPickUp;
	Math::Vec2 diff;
	Entity boat;
	Entity passenger;
	Entity destination;
	Entity destinationHouse;
	Transform* passengerTransform;
	Transform* boatTransform;
public:
	// Default constructor and destructor
	PassengerScript() = default;
	~PassengerScript() override = default;

	// Refer to parent
	void StartScript(const Entity& _e) override;
	void UpdateScript(const Entity& _e) override;
	void EndScript(const Entity& _e) override;
};