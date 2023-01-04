/*!*****************************************************************************
\file MonoManager.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 19-10-2022
\brief
This file contains the function definitions of the class MonoManager.
The MonoManager class handles the C# scripting for the engine.
*******************************************************************************/

#include <filesystem>
#include "pch.h"
#include "MonoManager.h"
//#include "Logger.h"

// Mono generic stuff
MonoDomain* MonoManager::mAppDomain = nullptr;
MonoDomain* MonoManager::mRootDomain = nullptr;
MonoAssembly* MonoManager::mAssembly = nullptr;

// Mono Object
MonoObject* MonoManager::m_ptrGameObject = nullptr;
uint32_t MonoManager::m_gameObjectGCHandle = 0;

std::string MonoManager::MonoDirectoryPath() {
	std::string path = std::filesystem::current_path().parent_path().string() + "\\bin\\";
#ifdef NDEBUG
#ifdef _EDITOR
	path += "EditorRelease";
#else
	path += "Release";
#endif
#else
#ifdef _EDITOR
	path += "EditorDebug";
#else
	path += "Debug";
#endif
#endif
	path += "\\x64";
	mono_set_assemblies_path(path.c_str());
	//mono_set_dirs("D:\\Heart\\Documents\\GitHub\\MemoryLeak\\MemoryLeak\\bin\\Debug\\x64", "D:\\Heart\\Documents\\GitHub\\MemoryLeak\\MemoryLeak\\bin\\Debug\\x64");
	path += "\\SCRIPTING";
	return path;
}

bool MonoManager::InitMonoDomain(const char* _root, const char* _appdomain, const std::string _directory, const std::string _dll) {
	std::cout << "Initialising Mono domain...\n";
	mRootDomain = mono_jit_init(_root);
	if (mRootDomain != nullptr) {
		// Create a mono app domain
		mAppDomain = mono_domain_create_appdomain((char*)_appdomain, nullptr);
		if (!mAppDomain)
			std::cout << "Failed to create Mono app domain: " << _appdomain << "!\n";
		else mono_domain_set(mAppDomain, true);

		std::cout << "Loading Mono assembly...\n";
		// Load a mono assembly script.dll
		mAssembly = mono_domain_assembly_open(mRootDomain, (_directory + '\\' + _dll + ".dll").c_str());
		if (!mAssembly) {
			std::cout << "Failed to load Mono assembly from: " << _directory + '\\' << _dll << ".dll!\n";
			return false;
		} else return true;
	} else {
		std::cout << "Failed to initialise Mono root domain: " << _root << "!\n";
		return false;
	}
	return false;
}

MonoClass* MonoManager::GetClassInAssembly(MonoAssembly* _assembly, const char* _namespace, const char* _class) {
	std::cout << "Loading Mono image...\n";
	MonoImage* assemblyImage = mono_assembly_get_image(_assembly);

	if (!assemblyImage) {
		std::cout << "Failed to retrieve assembly image!\n";
		return nullptr;
	}

	std::cout << "Retrieving Mono class...\n";
	MonoClass* monoClass = mono_class_from_name(assemblyImage, _namespace, _class);
	if (monoClass == nullptr) {
		std::cout << "Failed to retrieve Mono class " << _namespace << "::" << _class << "!\n";
		return nullptr;
	}
	//mono_image_close(assemblyImage);
	return monoClass;
}

MonoObject* MonoManager::InstantiateClass(const char* _namespace, const char* _class) {
	// Get a reference to the class to instantiate
	MonoClass* monoClass = GetClassInAssembly(mAssembly, _namespace, _class);
	if (monoClass == nullptr) {
		std::cout << "Failed to retrieve Mono class " << _namespace << "::" << _class << " from " << mAssembly << "!\n";
		return nullptr;
	}

	// Allocate an instance of the class
	MonoObject* classInstance = mono_object_new(mAppDomain, monoClass);

	if (classInstance == nullptr) {
		std::cout << "Failed to allocate an instance to Mono class " << _namespace << "::" << _class << "!\n";
		return nullptr;
	}

	// Call the parameterless (default) constructor
	mono_runtime_object_init(classInstance);
	return classInstance;
}

void MonoManager::CallMethod(std::string _scriptName, const char* _function, int _paramCount) {
	MonoObject* monoInstance = GetMonoComponent(_scriptName);
	if(monoInstance == nullptr) std::cout << "Failed to get an instance to Mono object from member map mMonoComponents!\n";

	// Get the MonoClass pointer from the instance
	MonoClass* classInstance = mono_object_get_class(monoInstance);
	if (classInstance == nullptr)
		std::cout << "Failed to get an instance to Mono class!\n";

	// Get a reference to the method in the class
	MonoMethod* method = mono_class_get_method_from_name(classInstance, _function, _paramCount);

	if (method == nullptr) {
		// No method called "Init" with 0 parameters in the class
		std::cout << "Method " << _function << "() does not exist!\n";
	}
	else {
		// Call the C# method on the objectInstance instance, and get any potential exceptions
		MonoObject* exception = nullptr;
		std::cout << "Calling method...\n";
		mono_runtime_invoke(method, monoInstance, nullptr, &exception);

		// Handle the exception
		if (exception) std::cout << "Failed to call method " << _function << "()!\n";
	}
}

MonoString* MonoManager::TestFunction() {
	std::cout << "Calling internal call success!\n";
	return mono_string_new(mono_domain_get(), "Hello!");
}

void MonoManager::SetMonoComponent(std::string _class, MonoObject* _monoObject) {
	mMonoComponents[_class] = _monoObject;
}

MonoObject* MonoManager::GetMonoComponent(std::string _class) {
	return mMonoComponents[_class];
}

void MonoManager::RegisterMonoScript(std::string _namespace, std::string _class) {
	if (MonoManager::GetInstance()->GetMonoComponent(_class) == nullptr) {
		std::cout << "Registering C# script method " << _namespace << "::" << _class << "()...\n";
		// Loading mono image
		MonoObject* testInstance = MonoManager::GetInstance()->InstantiateClass(_namespace.c_str(), _class.c_str());
		// Storing mono object
		if(testInstance != nullptr) MonoManager::GetInstance()->SetMonoComponent(_class, testInstance);
		else std::cout << "Failed to register C# script method " << _namespace << "::" << _class << "()!\n";
	}
}

void MonoManager::InitMono() {
	// Set and get mono directory
	std::string path = MonoDirectoryPath();

	// Create mono domain
	bool success = InitMonoDomain("MonoRoot", "MonoAppDomain", path, "Scripting");
	if (success) {
		// Add test internal functions
		//mono_add_internal_call("BonVoyage.TestClass::TestFunction", &MonoManager::TestFunction);
		//mono_add_internal_call("BonVoyage.TestClass::RegisterMonoScript", &MonoManager::RegisterMonoScript);
		//MonoMethods::GetInstance()->RegisterCalls();

		// Register mono script
		//MonoObject* testInstance = MonoManager::GetInstance()->InstantiateClass("BonVoyage", "TestClass");
		//CallMethod(testInstance, "Init", 0);
	}
}

void MonoManager::CloseMono() {
	// Release mono handles
	//if (m_gameObjectGCHandle)
		//mono_gchandle_free(m_gameObjectGCHandle);

	// Release the domain
	if (mAppDomain) {
		mono_domain_set(mono_get_root_domain(), false);
		mono_domain_unload(mAppDomain);
	}

	mAppDomain = nullptr;
	mAssembly = nullptr;

	if (mRootDomain) {
		//mono_domain_free(mDomain, false);
		mono_jit_cleanup(mRootDomain);
	}
	mRootDomain = nullptr;
}
