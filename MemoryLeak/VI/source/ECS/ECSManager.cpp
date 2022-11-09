/*!*****************************************************************************
\file ECSManager.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
This file contains the initialisation of ECS system. Registering all systems and
components.
*******************************************************************************/
#include "ECSManager.h"

// Instantiation of system pointers
std::shared_ptr<LifespanManager> lifespanManager{ nullptr };
std::shared_ptr<TransformManager> transformManager{ nullptr };
std::shared_ptr<SpriteManager> spriteManager{ nullptr };
std::shared_ptr<RenderManager> renderManager{ nullptr };
std::shared_ptr<Physics2DManager> physics2DManager{ nullptr };
std::shared_ptr<Collision2DManager> collision2DManager{ nullptr };
std::shared_ptr<PlayerController> playerManager{ nullptr };
std::shared_ptr<EditorManager> editorManager{ nullptr };
std::shared_ptr<Animator> animator{ nullptr };
std::shared_ptr<SheetAnimator> sheetAnimator{ nullptr };
std::shared_ptr<AudioManager> audioManager{ nullptr };
std::shared_ptr<SerializationManager> serializationManager{ nullptr };
std::shared_ptr<DialogManager> dialogManager{ nullptr };
std::shared_ptr<AIManager> aiManager{ nullptr };
std::shared_ptr<LogicSystem> logicSystem{ nullptr };
std::shared_ptr<ShadowManager> shadowManager{ nullptr };
//----------------------------------------------------------------
// Register Managers
//----------------------------------------------------------------
void ECSManager::RegisterLifespanManager() {
	Signature signature;
	signature.set(ECS::GetComponentType<General>());
	signature.set(ECS::GetComponentType<Lifespan>());

	lifespanManager = ECS::RegisterSystem<LifespanManager>();
	ECS::SetSystemSignature<LifespanManager>(signature);
}

void ECSManager::RegisterTransformManager() {
	Signature signature;
	signature.set(ECS::GetComponentType<General>());
	signature.set(ECS::GetComponentType<Transform>());

	transformManager = ECS::RegisterSystem<TransformManager>();
	ECS::SetSystemSignature<TransformManager>(signature);
}

void ECSManager::RegisterSpriteManager() {
	Signature signature;
	signature.set(ECS::GetComponentType<General>());
	signature.set(ECS::GetComponentType<Sprite>());

	spriteManager = ECS::RegisterSystem<SpriteManager>();
	ECS::SetSystemSignature<SpriteManager>(signature);
}

void ECSManager::RegisterRenderManager() {
	Signature signature;
	signature.set(ECS::GetComponentType<General>());
	signature.set(ECS::GetComponentType<Transform>());
	signature.set(ECS::GetComponentType<Sprite>());

	renderManager = ECS::RegisterSystem<RenderManager>();
	ECS::SetSystemSignature<RenderManager>(signature);
}

void ECSManager::RegisterPhysics2DManager() {
	Signature signature{};
	signature.set(ECS::GetComponentType<Physics2D>());

	physics2DManager = ECS::RegisterSystem<Physics2DManager>();
	ECS::SetSystemSignature<Physics2DManager>(signature);
}

void ECSManager::RegisterCollision2DManager() {
	Signature signature{};
	signature.set(ECS::GetComponentType<General>());

	collision2DManager = ECS::RegisterSystem<Collision2DManager>();
	ECS::SetSystemSignature<Collision2DManager>(signature);
}

void ECSManager::RegisterPlayerController() {
	Signature signature{};
	signature.set(ECS::GetComponentType<General>());

	playerManager = ECS::RegisterSystem<PlayerController>();
	ECS::SetSystemSignature<PlayerController>(signature);
}

void ECSManager::RegisterEditorManager() {
	Signature signature;
	signature.set(ECS::GetComponentType<General>());

	editorManager = ECS::RegisterSystem<EditorManager>();
	ECS::SetSystemSignature<EditorManager>(signature);
}

void ECSManager::RegisterAudioManager() {
	Signature signature;
	signature.set(ECS::GetComponentType<General>());
	signature.set(ECS::GetComponentType<Audio>());

	audioManager = ECS::RegisterSystem<AudioManager>();
	ECS::SetSystemSignature<AudioManager>(signature);
}
void ECSManager::RegisterSerializationManager() {
	Signature signature;
	signature.set(ECS::GetComponentType<General>());
	
	serializationManager = ECS::RegisterSystem<SerializationManager>();
	ECS::SetSystemSignature<SerializationManager>(signature);
}
void ECSManager::RegisterDialogManager() {
	Signature signature;
	signature.set(ECS::GetComponentType<General>());
	signature.set(ECS::GetComponentType<Text>());

	dialogManager = ECS::RegisterSystem<DialogManager>();
	ECS::SetSystemSignature<DialogManager>(signature);
}
void ECSManager::RegisterAIManager() {
	Signature signature;
	signature.set(ECS::GetComponentType<General>());
	signature.set(ECS::GetComponentType<AI>());

	aiManager = ECS::RegisterSystem<AIManager>();
	ECS::SetSystemSignature<AIManager>(signature);
}
void ECSManager::RegisterAnimator() {
	Signature signature;
	signature.set(ECS::GetComponentType<General>());
	signature.set(ECS::GetComponentType<Sprite>());
	signature.set(ECS::GetComponentType<Animation>());

	animator = ECS::RegisterSystem<Animator>();
	ECS::SetSystemSignature<Animator>(signature);
}
void ECSManager::RegisterSheetAnimator() {
	Signature signature;
	signature.set(ECS::GetComponentType<General>());
	signature.set(ECS::GetComponentType<Sprite>());
	signature.set(ECS::GetComponentType<SheetAnimation>());

	sheetAnimator = ECS::RegisterSystem<SheetAnimator>();
	ECS::SetSystemSignature<SheetAnimator>(signature);
}

void ECSManager::RegisterLogicSystem() {
	Signature signature;
	signature.set(ECS::GetComponentType<Script>());

	logicSystem = ECS::RegisterSystem<LogicSystem>();
	ECS::SetSystemSignature<LogicSystem>(signature);
}
	
void ECSManager::RegisterShadowManager() {
	Signature signature;
	signature.set(ECS::GetComponentType<General>());
	signature.set(ECS::GetComponentType<Sprite>());

	shadowManager = ECS::RegisterSystem<ShadowManager>();
	ECS::SetSystemSignature<ShadowManager>(signature);
}
//----------------------------------------------------------------
// ECSManager Functions
//----------------------------------------------------------------
void ECSManager::RegisterAllSystems() {
	RegisterLifespanManager();
	RegisterTransformManager();
	RegisterSpriteManager();
	RegisterRenderManager();
	RegisterAnimator();
	RegisterSheetAnimator();
	RegisterPlayerController();
	RegisterPhysics2DManager();
	RegisterCollision2DManager();
	RegisterEditorManager();
	RegisterAudioManager();
	RegisterSerializationManager();
	RegisterDialogManager();
	RegisterAIManager();
	RegisterLogicSystem();
	RegisterShadowManager();
	// More to come
}

void ECSManager::RegisterAllComponents() {
	ECS::RegisterComponent<General>();
	ECS::RegisterComponent<Lifespan>();
	ECS::RegisterComponent<Transform>();
	ECS::RegisterComponent<Sprite>();
	ECS::RegisterComponent<Animation>();
	ECS::RegisterComponent<SheetAnimation>();
	ECS::RegisterComponent<Physics2D>();
	//ECS::RegisterComponent<Collider2D>();
	ECS::RegisterComponent<CircleCollider>();
	ECS::RegisterComponent<RectCollider>();
	ECS::RegisterComponent<Edge2DCollider>();
	ECS::RegisterComponent<Point2DCollider>();
	ECS::RegisterComponent<PlayerTmp>();
	ECS::RegisterComponent<AI>();
	ECS::RegisterComponent<Audio>();
	ECS::RegisterComponent<Text>();
	ECS::RegisterComponent<Script>();
	ECS::RegisterComponent<Dialogue>();
	ECS::RegisterComponent<LightSource>();
	ECS::RegisterComponent<ParentChild>();
	// More to come
}

void ECSManager::ECS_init() {
	RegisterAllComponents();
	RegisterAllSystems();
}









