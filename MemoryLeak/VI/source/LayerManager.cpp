#include "ECSManager.h"

bool LayerManager::CI_RectvsRect(Contact& _contact) {
	// Get reference to the entities
	Entity& obj1{ _contact.obj[0] },
		& obj2{ _contact.obj[1] };

	// Store center and scale of both entities
	Math::Vec2	center1{ Math::Vec2{obj1.GetComponent<Transform>().translation} + obj1.GetComponent<LayerCollider>().centerOffset },
		scale1{ static_cast<float>(static_cast<double>(std::fabs(obj1.GetComponent<Transform>().scale.x)) * static_cast<double>(obj1.GetComponent<LayerCollider>().scaleOffset.x) / 2.0),
				static_cast<float>(static_cast<double>(std::fabs(obj1.GetComponent<Transform>().scale.y)) * static_cast<double>(obj1.GetComponent<LayerCollider>().scaleOffset.y) / 2.0) },
		center2{ Math::Vec2{obj2.GetComponent<Transform>().translation} + obj2.GetComponent<LayerCollider>().centerOffset },
		scale2{ static_cast<float>(static_cast<double>(std::fabs(obj2.GetComponent<Transform>().scale.x)) * static_cast<double>(obj2.GetComponent<LayerCollider>().scaleOffset.x) / 2.0),
				static_cast<float>(static_cast<double>(std::fabs(obj2.GetComponent<Transform>().scale.y)) * static_cast<double>(obj2.GetComponent<LayerCollider>().scaleOffset.y) / 2.0) };

// Only static check required
	Math::Vec2 distVec{ center1 - center2 };
	Math::Vec2 diff{ scale1.x + scale2.x - std::fabs(distVec.x),
					 scale1.y + scale2.y - std::fabs(distVec.y) };
	// For 2 rect to collide, both axis needs to be larger than 0, indicating a penetration has happened on both axis
	if (0.f < diff.x) {
		if (0.f < diff.y) {
			if (diff.x < diff.y)
				return true;
			else 
				return true;
		
		}
	}

	// Not colliding; Return false
	return false;
}

void LayerManager::Update() {
	// Broad phase 

	// Loop through player entities
	for (auto e1{ mEntities.begin() }; e1 != mEntities.end(); ++e1) {
		if (!e1->ShouldRun())
			continue;

		if (e1->GetComponent<General>().tag != TAG::PLAYER)
			continue;

		// Loop through all other entities
		for (auto e2{ mEntities.begin() }; e2 != mEntities.end(); ++e2) {
			if (e1 == e2)
				continue;

			if (!e2->ShouldRun())
				continue;

			Contact contact{ *e1, *e2, static_cast<int>(ColliderType::RECT), static_cast<int>(ColliderType::RECT) };
			// Check for layer collision
			if (CI_RectvsRect(contact)) 
				mUpdateList.emplace_back(contact);	// Push into list if true
	
		}
	}

	//  For every contact
	for (auto& item : mUpdateList) {
		// Check if they both have a sprite component (contains the layer value
		if (item.obj[0].HasComponent<Sprite>() && item.obj[1].HasComponent<Sprite>()) {
			// Check which entity is the player and store its original value while making its layer value be one
			// lesser than the current entity
			if (item.obj[0].GetComponent<General>().tag == TAG::PLAYER) {
				LayerManager::mOriginLayerMap.try_emplace(&item.obj[0], item.obj[0].GetComponent<Sprite>().layer);
				item.obj[0].GetComponent<Sprite>().layer = item.obj[1].GetComponent<Sprite>().layer - 2;

			}
			else if (item.obj[1].GetComponent<General>().tag == TAG::PLAYER) {
				LayerManager::mOriginLayerMap.try_emplace(&item.obj[1], item.obj[1].GetComponent<Sprite>().layer);
				item.obj[1].GetComponent<Sprite>().layer = item.obj[0].GetComponent<Sprite>().layer - 2;
			}
		}
	}

	// Code to pop back the original layer value after entities are no longer colliding
	// Does not work if multiple layer colliders overlap the player's layer collider
	// Causes two layer values to be inserted and creates issues
	bool CollidedFlag{ false };
	for (auto it{ mOriginLayerMap.begin() }; it != mOriginLayerMap.end(); ) {
		for (auto& collisionPair : mUpdateList) {
			if (&collisionPair.obj[0] == it->first || &collisionPair.obj[1] == it->first)
				CollidedFlag = true;
		}

		if (CollidedFlag)
			++it;
		else {
			if (it->first->id > MAX_ENTITIES)
				continue;
			if (it->first->HasComponent<Sprite>())
				it->first->GetComponent<Sprite>().layer = it->second;
			it = mOriginLayerMap.erase(it);
			CollidedFlag = false;
		}
	}

	// Clear the update list
	mUpdateList.clear();
}