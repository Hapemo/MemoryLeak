#include "ECSManager.h"

void LayerManager::Update(const double& _dt) {
	// Broad phase 


	for (auto e1{ mEntities.begin() }; e1 != mEntities.end(); ++e1) {
		if (!e1->ShouldRun())
			continue;

		for (auto e2{ e1 }; e2 != mEntities.end(); ++e2) {
			if (e1 == e2)
				continue;

			if (!e2->ShouldRun())
				continue;

			Contact contact{ *e1, *e2, static_cast<int>(ColliderType::RECT), static_cast<int>(ColliderType::RECT) };

			if ((*collision2DManager->mCollisionDatabase[static_cast<int>(contact.objType[0])][static_cast<int>(contact.objType[1])])(contact, _dt)) {
				mUpdateList.emplace_back(contact);
			}
		}
	}

	for (auto& item : mUpdateList) {
		if (item.obj[0].HasComponent<Sprite>() && item.obj[1].HasComponent<Sprite>()) {
			if (item.obj[0].GetComponent<General>().tag == TAG::PLAYER) {
				if (item.obj[0].GetComponent<Transform>().translation.y > item.obj[1].GetComponent<Transform>().translation.y) 
					item.obj[0].GetComponent<Sprite>().layer = item.obj[1].GetComponent<Sprite>().layer - 5;
				else
					item.obj[0].GetComponent<Sprite>().layer = item.obj[1].GetComponent<Sprite>().layer + 5;
			}
			else if (item.obj[1].GetComponent<General>().tag == TAG::PLAYER) {
				if (item.obj[1].GetComponent<Transform>().translation.y > item.obj[0].GetComponent<Transform>().translation.y)
					item.obj[1].GetComponent<Sprite>().layer = item.obj[0].GetComponent<Sprite>().layer - 5;
				else
					item.obj[1].GetComponent<Sprite>().layer = item.obj[0].GetComponent<Sprite>().layer + 5;
			}
		}
	}

	mUpdateList.clear();
}