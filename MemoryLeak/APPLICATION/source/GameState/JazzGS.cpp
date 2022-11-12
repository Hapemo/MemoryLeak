/*!*****************************************************************************
\file JazzGS.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 01-11-2022
\brief
Game state for testing jazz's stuff
*******************************************************************************/
#include "JazzGS.h"
#include "Application.h"
#include "Input.h"

#define PREFAB_OR_PARENTCHILD 0 // 0 for prefab, 1 for parentchild

Entity gParent{};

void AddChildren(Entity _parent, Entity _children) {
	_parent.GetComponent<General>().children.insert(_children);
}

void FullTranslate(Entity _e, Math::Vec2 const& addVec) {
#ifdef PREFAB_OR_PARENTCHILD
	(void) _e;
	(void)addVec;
	//Transform& transform = _e.GetComponent<Transform>();
	//transform.translation += addVec;

	//if (_e.HasComponent<ParentChild>()) {
	//	std::set<Entity> children = _e.GetComponent<ParentChild>().children;
	//	for (Entity e : children) {
	//		e.GetComponent<Transform>().translation += addVec;
	//	}
	//}
#else

#endif
}

void JazzGS::Load() {
#ifdef PREFAB_OR_PARENTCHILD
	int totalEnt{ 5 };
	while (totalEnt--) {
		Entity e = ECS::CreateEntity();
		mEntities.insert(e);
		Transform trans = Transform{ { 1.f, 1.f }, 1, {e.id * 10.f,e.id * 10.f} };
		e.AddComponent<Transform>(trans);
	}
#else

#endif
}

void JazzGS::Init() {
	// How does yu jun update the entity position?
	// How does he translate and rotate those entities?
	// Would be best if through a function
#ifdef PREFAB_OR_PARENTCHILD
	gParent = *(mEntities.begin());
#else

#endif
}

void JazzGS::Update() {
#ifdef PREFAB_OR_PARENTCHILD
	if (Input::CheckKey(PRESS, P)) {
		for (auto e : mEntities) {
			Transform const& transform = e.GetComponent<Transform>();
			printf("Entity %d Transform: %f, %f\n", e.id, transform.translation.x, transform.translation.y);
		}
	}

	if (Input::CheckKey(PRESS, EQUAL)) {
		int count{ 1 };
		while (++count <= 5)
			AddChildren(gParent, Entity(count));
	}

	if (Input::CheckKey(PRESS, PERIOD)) {
		FullTranslate(gParent, { 1,1 });
	}
#else

#endif
}

void JazzGS::Draw() {
#ifdef PREFAB_OR_PARENTCHILD

#else

#endif
}

void JazzGS::Free() {
#ifdef PREFAB_OR_PARENTCHILD
	
#else

#endif
}

void JazzGS::Unload() {
#ifdef PREFAB_OR_PARENTCHILD

#else

#endif
}