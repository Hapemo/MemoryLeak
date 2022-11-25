#include "PassengerScript.h"


REGISTER_SCRIPT(ScriptComponent, PassengerScript);

namespace {
	static bool speedCheat{ false };
}

void PassengerScript::StartScript(const Entity& _e) {
	(void)_e;
	boat = (FUNC->GetEntity("Boat", "Level1"));
	//passenger = (FUNC->GetEntity("Passenger_1", "Level1"));
	destination = (FUNC->GetEntity("destination", "Level1"));
	//destinationHouse = FUNC->GetEntity("")
	passengerTransform = &_e.GetComponent<Transform>();
	boatTransform = &boat.GetComponent<Transform>();
	pickedUp = false;
	readyToPickUp = true;
}

void PassengerScript::UpdateScript(const Entity& _e) {
	// If ready to pick up and it collided, make it pick up next frame.
	if (readyToPickUp) {
		if (collision2DManager->EntitiesCollided(_e, boat)) {
			pickedUp = true;
			_e.GetComponent<RectCollider>().isTrigger = true;
			readyToPickUp = false;
		}
		return;
	}
	
	// If picked up, follow boat
	if (pickedUp) {
		
		passengerTransform->translation = boatTransform->translation;

		// If reached destination, get off boat (pickedUp false) and go onto island.
		if (collision2DManager->EntitiesCollided(boat, destination)) {
			pickedUp = false;
			passengerTransform->translation = destinationHouse.GetComponent<Transform>().translation;
		}
	}
}

void PassengerScript::EndScript(const Entity& _e) {
	(void)_e;
}