#include "ECSManager.h"

bool LayerManager::CI_RectvsRect(Contact& _contact, const double& _dt) {
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
			if (diff.x < diff.y) {
				return true;
			}
			else {
				return true;
			}
		}
	}

	return false;
}

void LayerManager::Update(const double& _dt) {
	// Broad phase 


	for (auto e1{ mEntities.begin() }; e1 != mEntities.end(); ++e1) {
		if (!e1->ShouldRun())
			continue;

		if (e1->GetComponent<General>().tag != TAG::PLAYER)
			continue;

		for (auto e2{ mEntities.begin() }; e2 != mEntities.end(); ++e2) {
			if (e1 == e2)
				continue;

			if (!e2->ShouldRun())
				continue;

			Contact contact{ *e1, *e2, static_cast<int>(ColliderType::RECT), static_cast<int>(ColliderType::RECT) };

			if (CI_RectvsRect(contact, _dt)) {
				mUpdateList.emplace_back(contact);
			}
		}
	}

	for (auto& item : mUpdateList) {
		if (item.obj[0].HasComponent<Sprite>() && item.obj[1].HasComponent<Sprite>()) {
			if (item.obj[0].GetComponent<General>().tag == TAG::PLAYER) {
				//stack.push_back(std::make_pair(item.obj[0], item.obj[0].GetComponent<Sprite>().layer));
				LayerManager::mOriginLayerMap.try_emplace(&item.obj[0], item.obj[0].GetComponent<Sprite>().layer);
				item.obj[0].GetComponent<Sprite>().layer = item.obj[1].GetComponent<Sprite>().layer - 5;

			}
			else if (item.obj[1].GetComponent<General>().tag == TAG::PLAYER) {
				//stack.push_back(std::make_pair(item.obj[1], item.obj[1].GetComponent<Sprite>().layer));
				LayerManager::mOriginLayerMap.try_emplace(&item.obj[1], item.obj[1].GetComponent<Sprite>().layer);
				item.obj[1].GetComponent<Sprite>().layer = item.obj[0].GetComponent<Sprite>().layer - 5;
			}
		}
	}

	bool CollidedFlag{ false };
	for (auto it{ mOriginLayerMap.begin() }; it != mOriginLayerMap.end(); ) {
		for (auto& collisionPair : mUpdateList) {
			if (&collisionPair.obj[0] == it->first || &collisionPair.obj[1] == it->first)
				CollidedFlag = true;
		}

		if (CollidedFlag)
			++it;
		else {
			it->first->GetComponent<Sprite>().layer = it->second;
			it = mOriginLayerMap.erase(it);
			CollidedFlag = false;
		}
	}


	mUpdateList.clear();
}