///*!*****************************************************************************
//\file MScriptComponent.h
//\author Chen Jia Wen
//\par DP email: c.jiawen\@digipen.edu
//\par Course: GAM200
//\par Group: Memory Leak Studios
//\date 19-10-2022
//\brief
//This file contains the function declarations of the class MScriptComponent.
//The MScriptComponent class handles the C# scripting for the engine.
//*******************************************************************************/
//
//#pragma once
//#include <mono/jit/jit.h>
//#include <mono/metadata/assembly.h>
//#include <mono/metadata/debug-helpers.h>
//#include "ScriptComponent.h"
//
//class MScriptComponent : public ScriptComponent
//{
//public:
//	/*!*****************************************************************************
//	\brief
//	Default constructor and destructor.
//	*******************************************************************************/
//	MScriptComponent();
//	~MScriptComponent();
//
//	/*!*****************************************************************************
//	\brief
//	Delete copy constructor.
//	*******************************************************************************/
//	MScriptComponent(const MScriptComponent&) = delete;
//	const MScriptComponent& operator=(const MScriptComponent&) = delete;
//
//	/*!*****************************************************************************
//	\brief
//	Run the initialisation function for all active entities' scripts.
//	*******************************************************************************/
//	static void StartScript(Entity const& gob);
//
//	/*!*****************************************************************************
//	\brief
//	Run the update function for all active entities' scripts.
//	*******************************************************************************/
//	static void UpdateScript(Entity const& gob);
//
//	/*!*****************************************************************************
//	\brief
//	Run the exit function for all active entities' scripts.
//	*******************************************************************************/
//	static void EndScript(Entity const& gob);
//
//	std::string MonoDirectoryPath();
//	bool InitMonoDomain(const char* _domain, const std::string _directory, const std::string _dll);
//	MonoClass* GetClassInAssembly(MonoAssembly* _assembly, const char* _namespace, const char* _class);
//	MonoObject* InstantiateClass(const char* _namespace, const char* _class);
//	void CallMethod(MonoObject* _objectInstance, const char* _function, int _paramCount);
//
//	//void TestFunction(std::string _thingToPrint);
//	static MonoString* TestFunction();
//
//private:
//	// Mono generic stuff
//	static MonoDomain* mDomain;
//	static MonoAssembly* mAssembly;
//
//	// Mono Object
//	static MonoObject* m_ptrGameObject;
//	static uint32_t m_gameObjectGCHandle;
//};
