#pragma once
//
//#include "pch.h"
//#include "ECS_components.h"
//#include "ECS_items.h"
//#include "ECS_tools.h"
//#define MAX_PREFAB 500

//
//class Prefab {
//public:
//	Prefab();
//	~Prefab();
//
//	// Create new entity with prefab
//	// Must use ECS::CreateEntity
//	Entity CreatePrefabee();
//
//	// Remove entity's link from prefab. Can be called by user.
//	// When user press a button to uncheck a flag for being a prefabee.
//	// Must be called when entity gets deleted.
//	// Must be called when entity gets copy assigned to another entity.
//	void UnlinkPrefabee(Entity const&);
//
//	// Add components to prefab. Must update all prefabees on newly added component.
//	template<typename T>
//	void AddComponent(T const&);
//
//	// Change component in prefab. Must update all prefabees on updated component.
//	template<typename T>
//	void UpdateComponent(T const&);
//	
//	// Remove component from prefab. Must remove component from all components.
//	template<typename T>
//	void RemoveComponent();
//
//	std::string& Name() { return mName; }
//
//private:
//	std::string mName;
//	std::vector<Entity> mPrefabees;
//	std::array<void*, MAX_COMPONENTS> mComponents;
//
//	/* Components (Needs to be updated)
//	General*							mGeneral;
//	Lifespan*							mLifespan;
//	Transform*						mTransform;
//	Sprite*								mSprite;
//	Animation*						mAnimation;
//	SheetAnimation*				mSheetAnimation;
//	Physics2D*						mPhysics2D;
//	RectCollider*					mRectCollider;
//	CircleCollider*				mCircleCollider;
//	Edge2DCollider*				mEdge2DCollider;
//	Point2DCollider*			mPoint2DCollider;
//	PlayerTmp*						mPlayerTmp;
//	Stuff*								mStuff;
//	Audio*								mAudio;
//	Text*									mText;
//	*/
//};
//
//
//class PrefabManager {
//	
//};
//
//
//template<typename T>
//void Prefab::AddComponent(T const& _component) { // TODO: Possible optimisation to put _component into data instead of *(static_cast<T*>(mComponents[pos]))
//	ComponentType pos{ ECS::GetComponentType<T>() };
//	mComponents[pos] = new T;
//	*(static_cast<T*>(mComponents[pos])) = _component;
//
//	for (Entity const& e : mPrefabees)
//		e.AddComponent<T>(*(static_cast<T*>(mComponents[pos])));
//}
//
//template<typename T>
//void Prefab::UpdateComponent(T const& _component) { // TODO: Possible optimisation to put _component into data instead of *(static_cast<T*>(mComponents[pos]))
//	ComponentType pos{ ECS::GetComponentType<T>() };
//	*(static_cast<T*>(mComponents[pos])) = _component;
//
//	for (Entity const& e : mPrefabees)
//		e.GetComponent<T>() = *(static_cast<T*>(mComponents[pos]));
//}
//
//template<typename T>
//void Prefab::RemoveComponent() {
//	for (Entity const& e : mPrefabees)
//		e.RemoveComponent<T>();
//	
//	ComponentType pos{ ECS::GetComponentType<T>() };
//	delete mComponents[pos];
//	mComponents[pos] = nullptr;
//}
//







