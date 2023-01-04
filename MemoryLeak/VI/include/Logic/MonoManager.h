/*!*****************************************************************************
\file MonoManager.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 19-10-2022
\brief
This file contains the function declarations of the class MonoManager.
The MonoManager class handles the C# scripting for the engine.
*******************************************************************************/

#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include "Singleton.h"
#include "ScriptComponent.h"
//#include "MonoComponent.h"
//#include "MonoMethods.h"

class MonoManager : public Singleton<MonoManager>
{
public:
	/*!*****************************************************************************
	\brief
	Default constructor and destructor.
	*******************************************************************************/
	MonoManager() = default;
	~MonoManager() = default;

	/*!*****************************************************************************
	\brief
	Delete copy constructor.
	*******************************************************************************/
	MonoManager(const MonoManager&) = delete;
	const MonoManager& operator=(const MonoManager&) = delete;

	void InitMono();
	void CloseMono();
	std::string MonoDirectoryPath();
	bool InitMonoDomain(const char* _root, const char* _appdomain, const std::string _directory, const std::string _dll);
	MonoClass* GetClassInAssembly(MonoAssembly* _assembly, const char* _namespace, const char* _class);
	MonoObject* InstantiateClass(const char* _namespace, const char* _class);
	void CallMethod(std::string _scriptName, const char* _function, int _paramCount);

	//void TestFunction(std::string _thingToPrint);
	static MonoString* TestFunction();
	static void RegisterMonoScript(std::string _namespace, std::string _class);

	void SetMonoComponent(std::string _class, MonoObject* _monoObject);
	MonoObject* GetMonoComponent(std::string _class);

private:
	// Mono generic stuff
	static MonoDomain* mAppDomain;
	static MonoDomain* mRootDomain;
	static MonoAssembly* mAssembly;

	// Mono Object
	static MonoObject* m_ptrGameObject;
	static uint32_t m_gameObjectGCHandle;

	// Storing all mono scripts
	std::map<std::string, MonoObject*> mMonoComponents;
};
