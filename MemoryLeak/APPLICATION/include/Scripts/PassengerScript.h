#pragma once

#include "ECS_tools.h"
#include "ScriptManager.h"
#include "ScriptComponent.h"

class PassengerScript : public ScriptComponent {
private:
	std::string name{ "PassengerScript" };
	bool pickedUp;
	bool readyToPickUp;
	//Entity passenger;
	Entity boat;
	Entity destination;
	Entity destinationHouse;
	Transform* passengerTransform;
	Transform* boatTransform;
public:
	PassengerScript() = default;
	~PassengerScript() override = default;

	void StartScript(const Entity& _e) override;

	void UpdateScript(const Entity& _e) override;

	void EndScript(const Entity& _e) override;
};