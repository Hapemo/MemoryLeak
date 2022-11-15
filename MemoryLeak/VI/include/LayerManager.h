#pragma once

#include "ECS_systems.h"
#include "./Physics/ColliderType.h"
#include "./Physics/Contact.h"

class LayerManager : public System {
public:
	void Update(const double& _dt);
private:
	std::vector<Contact> mUpdateList;
};