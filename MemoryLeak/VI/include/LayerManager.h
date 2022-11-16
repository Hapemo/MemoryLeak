#pragma once

#include "ECS_systems.h"
#include "./Physics/ColliderType.h"
#include "./Physics/Contact.h"

class LayerManager : public System {
public:
	static bool CI_RectvsRect(Contact& _contact, const double& _dt);
	void Update(const double& _dt);
private:
	std::vector<Contact> mUpdateList;
	std::unordered_map<Entity*, int> mOriginLayerMap;
};