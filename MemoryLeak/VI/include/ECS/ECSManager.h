#pragma once
#include "pch.h"
#include "ECS_tools.h"

#include "TransformManager.h"
#include "SpriteManager.h"
//#include "RenderManager.h"
#include "RenderManager.h"
#include "ColliderTransformManager.h"

#include "PlayerManager.h"
#include "../Physics/Physics2DManager.h"
#include "Collision2DManager.h"

#include "LevelEditor.h"
#include "Animator.h"
#include "SheetAnimator.h"
#include "AudioManager.h"
#include "Serialization.h"

extern std::shared_ptr<LifespanManager> lifespanManager;
extern std::shared_ptr<BenchmarkManager> benchmarkManager;

extern std::shared_ptr<TransformManager> transformManager;
extern std::shared_ptr<SpriteManager> spriteManager;
//extern std::shared_ptr<RenderManager> renderManager;
extern std::shared_ptr<RenderManager> renderManager;
extern std::shared_ptr<Animator> animator;
extern std::shared_ptr<SheetAnimator> sheetAnimator;

//extern std::shared_ptr<ColliderTransformManager> colliderTransnformManager;

extern std::shared_ptr<PlayerManager> playerManager;
extern std::shared_ptr<Physics2DManager> physics2DManager;
extern std::shared_ptr<Collision2DManager> collision2DManager;

//@weijhin
extern std::shared_ptr<LevelEditor> levelEditor;
extern std::shared_ptr<AudioManager> audioManager;
extern std::shared_ptr<SerializationManager> serializationManager;

class ECSManager {
private:
	static void RegisterLifespanManager();
	static void RegisterBenchmarkManager();

	static void RegisterTransformManager();
	static void RegisterSpriteManager();
	//static void RegisterRenderManager();
	static void RegisterRenderManager();
	static void RegisterAnimator();
	static void RegisterSheetAnimator();


	static void RegisterPlayerManager();
	static void RegisterPhysics2DManager();
	static void RegisterCollision2DManager();
	// static void RegisterColliderTransformManager();

	//@weijhin
	static void RegisterLevelEditor();
	static void RegisterAudioManager();
	static void RegisterSerializationManager();
	// More to come
	
	static void RegisterAllSystems();
	static void RegisterAllComponents();
public:
	static void ECS_init();
};










