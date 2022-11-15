/*!*****************************************************************************
\file Serialization.h
\author Huang Wei Jhin
\par DP email: h.weijhin@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function declarations for a Serialization system that modifies
Entities and its Components.
*******************************************************************************/
#pragma once
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"
#include <ECS_tools.h>
#include "ResourceManager.h"
#include <vec2.h>

#include "document.h"
#include "writer.h"
#include <istreamwrapper.h>
#include "stringbuffer.h"
#include <prettywriter.h>


// Data that a scene class should contain
struct SceneData {
	std::string Name;
	Transform camera;
	bool isActive;
	int layer;
	int order;
	std::set<Entity> mEntities;  //??
};

//Data that a gamestate class should contain
struct GameStateData {
	std::string Name;
	std::vector<SceneData> scenes;
	std::vector<ResourceManager::GUID> mGUIDs;
};

using namespace rapidjson;
/*!*****************************************************************************
\brief
	This class encapsulates the functions for Serialization manager
*******************************************************************************/
class SerializationManager : public System
{
public:
	std::set<Entity> LoadScene(std::string _filename);
	void SaveScene(std::string _filename, std::set<Entity> entities);
	std::vector<std::set<Entity>> LoadGameState(std::string& _filename, std::vector<std::string> & sceneName);
	void SaveGameState(std::pair<  std::string, std::vector<std::string> > _filename, std::vector<std::set<Entity>> entities);
	void LoadPrefab(std::string _filename = "NewPrefab");
	void SavePrefab(std::string _filename = "NewPrefab");
	void LoadDialogs(std::string _filename = "Dialog1");
	void SaveDialogs(std::string _filename = "Dialog1");

	//getters
	std::string GetSceneFilename();
	std::string GetGameStateFilename();
	std::string GetPrefabFilename();
	std::string GetDialogueFilename();
	std::vector<std::string> GetAllsceneFilename();
	std::vector<std::string> GetAllgameStateFilename();
	std::vector<std::string> GetAllprefabFilename();
	std::vector<std::string> GetAlldialogueFilename();



private:
	std::string sceneFilename;
	std::string gameStateFilename;
	std::string prefabFilename;
	std::string dialogueFilename;
	std::vector<std::string> allsceneFilename;
	std::vector<std::string> allgameStateFilename;
	std::vector<std::string> allprefabFilename;
	std::vector<std::string> alldialogueFilename;

	//helper functions
	static Math::Vec2 GetVec2(Value& vecIn);
	static void addVectorMember(Document& scene, Value& parent, const char* name, Math::Vec2 data);
	template<typename T>
	static void addVectorArrayStrMember(Document& scene, Value& parent, const char* name, std::vector <T> data);
	template<typename T>
	static void addVectorArrayForceMember(Document& scene, Value& parent, const char* name, std::vector <T> data);
	template<typename T>
	static void addVectorArrayMember(Document& scene, Value& parent, const char* name, std::vector <T> data);
	template<typename T>
	static void addVectorsMember(Document& scene, Value& parent, const char* name, std::vector <T> data);

	//load components
	General getGeneral(Value& entity);
	Lifespan getLifespan(Value& entity);
	Transform getTransform(Value& entity);
	Sprite getSprite(Value& entity);
	Animation getAnimation(Value& entity);
	SheetAnimation getSheetAnimation(Value& entity);
	Physics2D getPhysics2D(Value& entity);
	RectCollider getRectCollider(Value& entity);
	LayerCollider getLayerCollider(Value& entity);
	CircleCollider getCircleCollider(Value& entity);
	Edge2DCollider getEdge2DCollider(Value& entity);
	Point2DCollider getPoint2DCollider(Value& entity);
	Audio getAudio(Value& entity);
	AI getAI(Value& entity);
	Text getText(Value& entity);
	Dialogue getDialogue(Value& entity);
	LightSource getLightSource(Value& entity);
	Script getScript(Value& entity);

	//save components 
	void addGeneral(Document& scene, Value& entity, General general);
	void addLifespan(Document& scene, Value& entity, Lifespan lifespan);
	void addTransform(Document& scene, Value& entity, Transform transform);
	void addSprite(Document& scene, Value& entity, Sprite sprite);
	void addAnimation(Document& scene, Value& entity, Animation animation);
	void addSheetAnimation(Document& scene, Value& entity, SheetAnimation sheetAnimation);
	void addPhysics2D(Document& scene, Value& entity, Physics2D physics2D);
	void addRectCollider(Document& scene, Value& entity, RectCollider rectCollider);
	void addLayerCollider(Document& scene, Value& entity, LayerCollider layerCollider);
	void addCircleCollider(Document& scene, Value& entity, CircleCollider circleCollider);
	void addEdge2DCollider(Document& scene, Value& entity, Edge2DCollider edge2DCollider);
	void addPoint2DCollider(Document& scene, Value& entity, Point2DCollider point2DCollider);
	void addAudio(Document& scene, Value& entity, Audio audio);
	void addAI(Document& scene, Value& entity, AI ai);
	void addText(Document& scene, Value& entity, Text text);
	void addDialogue(Document& scene, Value& entity, Dialogue dialogue);
	void addLightSource(Document& scene, Value& entity, LightSource lightSource);
	void addScript(Document& scene, Value& entity, Script script);

public:
	static SceneData LoadSceneData(ResourceManager::GUID const& _guid);
	static SceneData LoadSceneData(std::string const& _filePath);
	static GameStateData LoadGameStateData(ResourceManager::GUID const& _guid); // (Deprecated)
	static GameStateData LoadGameStateData(std::string const& _filePath); // (Deprecated)
	static void SaveSceneData(ResourceManager::GUID const&);

};



