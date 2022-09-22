#pragma once
#include "pch.h"
#include "ECS_tools.h"

#include "Graphics/TransformManager.h"
#include "Graphics/SpriteManager.h"
//#include "Graphics/RenderManager.h"
#include "Graphics/RenderManager.h"
#include "ColliderTransformManager.h"

#include "PlayerManager.h"
#include "Physics2DManager.h"
#include "Collision2DManager.h"

#include "LevelEditor.h"
#include "Graphics/Animator.h"
#include "Graphics/SheetAnimator.h"
#include "AudioManager.h"
#include "Serialization.h"
#include "DialogManager.h"

extern std::shared_ptr<LifespanManager> lifespanManager;
extern std::shared_ptr<BenchmarkManager> benchmarkManager;
extern std::shared_ptr<TransformManager> transformManager;
extern std::shared_ptr<SpriteManager> spriteManager;
extern std::shared_ptr<RenderManager> renderManager;
extern std::shared_ptr<Animator> animator;
extern std::shared_ptr<SheetAnimator> sheetAnimator;
extern std::shared_ptr<PlayerManager> playerManager;
extern std::shared_ptr<Physics2DManager> physics2DManager;
extern std::shared_ptr<Collision2DManager> collision2DManager;
extern std::shared_ptr<LevelEditor> levelEditor;
extern std::shared_ptr<AudioManager> audioManager;
extern std::shared_ptr<SerializationManager> serializationManager;
extern std::shared_ptr<DialogManager> dialogManager;

class ECSManager {
private:
	static void RegisterLifespanManager();
	static void RegisterBenchmarkManager();
	static void RegisterTransformManager();
	static void RegisterSpriteManager();
	static void RegisterRenderManager();
	static void RegisterAnimator();
	static void RegisterSheetAnimator();
	static void RegisterPlayerManager();
	static void RegisterPhysics2DManager();
	static void RegisterCollision2DManager();
	static void RegisterLevelEditor();
	static void RegisterAudioManager();
	static void RegisterSerializationManager();
	static void RegisterDialogManager();
	
	// More to come
	
	static void RegisterAllSystems();
	static void RegisterAllComponents();
public:
	static void ECS_init();
};










