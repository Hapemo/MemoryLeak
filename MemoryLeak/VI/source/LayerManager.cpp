#include "ECSManager.h"

bool LayerManager::CI_RectvsRect(Contact& _contact, const double& _dt) {
	// Get reference to the entities
	Entity& obj1{ _contact.obj[0] },
		& obj2{ _contact.obj[1] };

	// Store center and scale of both entities
	Math::Vec2	center1{ Math::Vec2{obj1.GetComponent<Transform>().translation} + obj1.GetComponent<RectCollider>().centerOffset },
		scale1{ static_cast<float>(static_cast<double>(std::fabs(obj1.GetComponent<Transform>().scale.x)) * static_cast<double>(obj1.GetComponent<RectCollider>().scaleOffset.x) / 2.0),
				static_cast<float>(static_cast<double>(std::fabs(obj1.GetComponent<Transform>().scale.y)) * static_cast<double>(obj1.GetComponent<RectCollider>().scaleOffset.y) / 2.0) },
		center2{ Math::Vec2{obj2.GetComponent<Transform>().translation} + obj2.GetComponent<RectCollider>().centerOffset },
		scale2{ static_cast<float>(static_cast<double>(std::fabs(obj2.GetComponent<Transform>().scale.x)) * static_cast<double>(obj2.GetComponent<RectCollider>().scaleOffset.x) / 2.0),
				static_cast<float>(static_cast<double>(std::fabs(obj2.GetComponent<Transform>().scale.y)) * static_cast<double>(obj2.GetComponent<RectCollider>().scaleOffset.y) / 2.0) };

	// Static check
		//if (aabb1max.x < aabb2min.x)
		//	return false;
		//if (aabb1min.x > aabb2max.x)
		//	return false;
		//if (aabb1max.y < aabb2min.y)
		//	return false;
		//if (aabb1min.y > aabb2max.y)
		//	return false;
	Math::Vec2 distVec{ center1 - center2 };
	Math::Vec2 diff{ scale1.x + scale2.x - std::fabs(distVec.x),
					 scale1.y + scale2.y - std::fabs(distVec.y) };
	// For 2 rect to collide, both axis needs to be larger than 0, indicating a penetration has happened on both axis
	if (0.f < diff.x) {
		if (0.f < diff.y) {
			if (diff.x < diff.y) {
				// Set contact information
				_contact.normal = distVec.x < 0.f ? Math::Vec2{ 1.f, 0.f } : Math::Vec2{ -1.f, 0.f };
				_contact.penetration = diff.x;
				_contact.contacts = _contact.normal * scale1.x + center1;
				return true;
			}
			else {
				// Set contact information
				_contact.normal = distVec.y < 0.f ? Math::Vec2{ 0.f, 1.f } : Math::Vec2{ 0.f, -1.f };
				_contact.penetration = diff.y;
				_contact.contacts = _contact.normal * scale1.y + center1;
				return true;
			}
		}
	}

	// Dynamic check
		// Compute min and max of both entities
	Math::Vec2	aabb1min{ center1 - scale1 },
		aabb1max{ center1 + scale1 },
		aabb2min{ center2 - scale2 },
		aabb2max{ center2 + scale2 };

	// Compute relative velocity
	Math::Vec2 Vb{};
	if (obj2.HasComponent<Physics2D>() && obj1.HasComponent<Physics2D>())
		Vb = obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt) - obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (obj1.HasComponent<Physics2D>())
		Vb = obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	else if (obj2.HasComponent<Physics2D>())
		Vb = obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);

	// Check if relative velocity is zero
	if (Vb == Math::Vec2{ 0.f, 0.f })
		return false;

	double tFirst{ 0 }, tLast{ _dt }, tTmp{ 0 };

	// ------ X axis -----
	if (static_cast<double>(Vb.x) < 0.0) {
		if (static_cast<double>(aabb1min.x) > static_cast<double>(aabb2max.x)) // Case 1
			return false;
		if (static_cast<double>(aabb1max.x) < static_cast<double>(aabb2min.x)) {// Case 4
			tTmp = (static_cast<double>(aabb1max.x) - static_cast<double>(aabb2min.x)) / static_cast<double>(Vb.x);
			tFirst = tTmp > tFirst ? tTmp : tFirst;
		}
		if (static_cast<double>(aabb1min.x) < static_cast<double>(aabb2max.x)) {// Case 4
			tTmp = (static_cast<double>(aabb1min.x) - static_cast<double>(aabb2max.x)) / static_cast<double>(Vb.x);
			tLast = tTmp < tLast ? tTmp : tLast;
		}
	}
	if (static_cast<double>(Vb.x) > 0.0) {
		if (static_cast<double>(aabb1min.x) > static_cast<double>(aabb2max.x)) {// Case 2
			tTmp = (static_cast<double>(aabb1min.x) - static_cast<double>(aabb2max.x)) / static_cast<double>(Vb.x);
			tFirst = tTmp > tFirst ? tTmp : tFirst;
		}
		if (static_cast<double>(aabb1max.x) > static_cast<double>(aabb2min.x)) {// Case 2
			tTmp = (static_cast<double>(aabb1max.x) - static_cast<double>(aabb2min.x)) / static_cast<double>(Vb.x);
			tLast = tTmp < tLast ? tTmp : tLast;
		}
		if (static_cast<double>(aabb1max.x) < static_cast<double>(aabb2min.x)) // Case 3
			return false;
	}
	if (tFirst > tLast) // Case 5
		return false;

	// ------ Y axis -----
	if (static_cast<double>(Vb.y) < 0.0) {
		if (static_cast<double>(aabb1min.y) > static_cast<double>(aabb2max.y)) // Case 1
			return false;
		if (static_cast<double>(aabb1max.y) < static_cast<double>(aabb2min.y)) {// Case 4
			tTmp = (static_cast<double>(aabb1max.y) - static_cast<double>(aabb2min.y)) / static_cast<double>(Vb.y);
			tFirst = tTmp > tFirst ? tTmp : tFirst;
		}
		if (static_cast<double>(aabb1min.y) < static_cast<double>(aabb2max.y)) {// Case 4
			tTmp = (static_cast<double>(aabb1min.y) - static_cast<double>(aabb2max.y)) / static_cast<double>(Vb.y);
			tLast = tTmp < tLast ? tTmp : tLast;
		}
	}
	if (static_cast<double>(Vb.y) > 0.0) {
		if (static_cast<double>(aabb1min.y) > static_cast<double>(aabb2max.y)) {// Case 2
			tTmp = (static_cast<double>(aabb1min.y) - static_cast<double>(aabb2max.y)) / static_cast<double>(Vb.y);
			tFirst = tTmp > tFirst ? tTmp : tFirst;
		}
		if (static_cast<double>(aabb1max.y) > static_cast<double>(aabb2min.y)) {// Case 2
			tTmp = (static_cast<double>(aabb1max.y) - static_cast<double>(aabb2min.y)) / static_cast<double>(Vb.y);
			tLast = tTmp < tLast ? tTmp : tLast;
		}
		if (static_cast<double>(aabb1max.y) < static_cast<double>(aabb2min.y)) // Case 3
			return false;
	}
	if (tFirst > tLast) // Case 5
		return false;

	// Will intersect within the next delta time
		// Use first as intersection time
		//_contact.interTime = tFirst;

		// Compute next frame's position and use that data for collision response 
	Math::Vec2 obj1NewPos{ center1 },
		obj2NewPos{ center2 };
	if (obj1.HasComponent<Physics2D>())
		obj1NewPos += obj1.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);
	if (obj2.HasComponent<Physics2D>())
		obj2NewPos += obj2.GetComponent<Physics2D>().velocity * static_cast<float>(_dt);

	// Compute penetration
	Math::Vec2 newDistVec{ obj1NewPos - obj2NewPos };
	Math::Vec2 newDiff{ scale1.x + scale2.x - std::fabs(newDistVec.x),
					 scale1.y + scale2.y - std::fabs(newDistVec.y) };

	// Find axis that penetrates less and use it to resolve collision
	if (newDiff.x < newDiff.y) {
		// Set contact information
		_contact.normal = newDistVec.x < 0.f ? Math::Vec2{ 1.f, 0.f } : Math::Vec2{ -1.f, 0.f };
		_contact.penetration = newDiff.x;
		_contact.contacts = _contact.normal * scale1.x + center1;
	}
	else {
		// Set contact information
		_contact.normal = newDistVec.y < 0.f ? Math::Vec2{ 0.f, 1.f } : Math::Vec2{ 0.f, -1.f };
		_contact.penetration = newDiff.y;
		_contact.contacts = _contact.normal * scale1.y + center1;
	}
	if (obj1.HasComponent<Audio>())
		obj1.GetComponent<Audio>().sound.toPlay = true;
	if (obj2.HasComponent<Audio>())
		obj2.GetComponent<Audio>().sound.toPlay = true;
	return true;

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