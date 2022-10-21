#include "PrefabManager.h"


Prefab::Prefab() : mName(""), mPrefabees(), mComponents() {
	for (void* ptr : mComponents) ptr = nullptr;
}

Prefab::~Prefab() {
	for (void* ptr : mComponents) delete ptr;
}

Entity Prefab::CreatePrefabee() {
	int compType{};
	Entity e{};

	// Loop through all components, if component exists, add it to entity.
	for (void* component : mComponents) {
		++compType;
		if (!component) continue;

		// TODO: Very dangerous. If there is a change in component order, whole thing breaks
		switch (compType) {
		case 1: // General
			e.AddComponent<General>(*(static_cast<General*>(component)));
				break;

		case 2: // Lifespan
			e.AddComponent<Lifespan>(*(static_cast<Lifespan*>(component)));
				break;

		case 3: // Transform
			e.AddComponent<Transform>(*(static_cast<Transform*>(component)));
				break;

		case 4: // Sprite
			e.AddComponent<Sprite>(*(static_cast<Sprite*>(component)));
				break;

		case 5: // Animation
			e.AddComponent<Animation>(*(static_cast<Animation*>(component)));
				break;

		case 6: // SheetAnimation
			e.AddComponent<SheetAnimation>(*(static_cast<SheetAnimation*>(component)));
				break;

		case 7: // Physics2D
			e.AddComponent<Physics2D>(*(static_cast<Physics2D*>(component)));
				break;

		case 8: // CircleCollider
			e.AddComponent<CircleCollider>(*(static_cast<CircleCollider*>(component)));
				break;

		case 9: // RectCollider
			e.AddComponent<RectCollider>(*(static_cast<RectCollider*>(component)));
				break;

		case 10: // Edge2DCollider
			e.AddComponent<Edge2DCollider>(*(static_cast<Edge2DCollider*>(component)));
				break;

		case 11: // Point2DCollider
			e.AddComponent<Point2DCollider>(*(static_cast<Point2DCollider*>(component)));
				break;

		case 12: // PlayerTmp
			e.AddComponent<PlayerTmp>(*(static_cast<PlayerTmp*>(component)));
				break;

		case 13: // Stuff
			e.AddComponent<Stuff>(*(static_cast<Stuff*>(component)));
				break;

		case 14: // Audio
			e.AddComponent<Audio>(*(static_cast<Audio*>(component)));
				break;

		case 15: // Text
			e.AddComponent<Text>(*(static_cast<Text*>(component)));
			break;
		
		}
	}

	mPrefabees.push_back(e);
	return e;
}

void Prefab::UnlinkPrefabee(Entity const& _e) { // Should be called when Entity gets freed
	for (Entity& e : mPrefabees) {
		if (e.id == _e.id) {
			e.id = mPrefabees.back().id;
			mPrefabees.pop_back();
			break;
		}
	}
}









































