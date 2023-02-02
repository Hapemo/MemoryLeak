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
uint32_t MonoManager::mMonoHandler = 0;

/*!*****************************************************************************
\brief
Initialise Mono.
*******************************************************************************/
void MonoManager::InitMono() {
	// Set and get mono directory
	std::string path = MonoDirectoryPath();

	// Create mono domain
	bool success = InitMonoDomain("MonoRoot", "MonoAppDomain", path, "Scripting");
	// Add internal functionsx
	if (success) MonoMethods::GetInstance()->RegisterCalls();
}

/*!*****************************************************************************
\brief
Set and return the mono directory path according to the projec configuration.
*******************************************************************************/
std::string MonoManager::MonoDirectoryPath() {
	char* tmp{};
	_get_pgmptr(&tmp);
	std::string path{ tmp };
	path.erase(path.find_last_of("\\"));

	//LOG_INFO(path);
	mono_set_dirs(path.c_str(), path.c_str());
	path += "\\SCRIPTING";
	return path;
}

/*!*****************************************************************************
\brief
Initialise the Mono root domain, create the app domain, and load the mono
assembly dll. Returns true if success, else returns false.
*******************************************************************************/
bool MonoManager::InitMonoDomain(const char* _root, const char* _appdomain, const std::string _directory, const std::string _dll) {
	std::cout << "Initialising Mono domain...\n";
	//LOG_INFO("Initialising Mono domain...");
	mRootDomain = mono_jit_init(_root);
	if (mRootDomain != nullptr) {
		std::cout << "Creating app domain...\n";
		// Create a mono app domain
		mAppDomain = mono_domain_create_appdomain((char*)_appdomain, nullptr);

		if (!mAppDomain) std::cout << "Failed to create Mono app domain: " << _appdomain << "!\n";
		else mono_domain_set(mAppDomain, true);

		std::cout << "Loading Mono assembly...\n";
		// Load a mono assembly script.dll
		mAssembly = mono_domain_assembly_open(mRootDomain, (_directory + '\\' + _dll + ".dll").c_str());
		if (!mAssembly) {
			std::cout << "Failed to load Mono assembly from: " << _directory + '\\' << _dll << ".dll!\n";
			return false;
		}
		else return true;
	}
	else {
		std::cout << "Failed to initialise Mono root domain: " << _root << "!\n";
		return false;
	}
	return false;
}

/*!*****************************************************************************
\brief
Retrieves the mono class from a mono image. Returns the mono class pointer if
success, else returns a nullptr.
*******************************************************************************/
MonoClass* MonoManager::GetClassInAssembly(MonoAssembly* _assembly, const char* _namespace, const char* _class) {
	std::cout << "Loading Mono image...\n";
	MonoImage* assemblyImage = mono_assembly_get_image(_assembly);

	if (!assemblyImage) {
		std::cout << "Failed to retrieve assembly image!\n";
		return nullptr;
	}

	std::cout << "Retrieving Mono class...\n";
	MonoClass* monoClass = mono_class_from_name(assemblyImage, _namespace, _class);
	if (monoClass == nullptr) return nullptr;
	return monoClass;
}

/*!*****************************************************************************
\brief
Loads the mono class and allocate a class instance for it in the app domain.
Returns the class instance if success, else returns a nullptr.
*******************************************************************************/
MonoObject* MonoManager::InstantiateClass(const char* _namespace, const char* _class) {
	// Get a reference to the class to instantiate
	MonoClass* monoClass = GetClassInAssembly(mAssembly, _namespace, _class);
	if (monoClass == nullptr) {
		std::cout << "Failed to retrieve Mono class " << _namespace << "::" << _class << "!\n";
		return nullptr;
	}
	else std::cout << "Retrieved Mono class " << _namespace << "::" << _class << ".\n";

	// Allocate an instance of the class
	MonoObject* classInstance = mono_object_new(mAppDomain, monoClass);

	if (classInstance == nullptr) {
		std::cout << "Failed to allocate an instance to Mono class " << _namespace << "::" << _class << "!\n";
		return nullptr;
	}
	else std::cout << "Allocated an instance to Mono class " << _namespace << "::" << _class << ".\n";

	// Call the parameterless (default) constructor
	mono_runtime_object_init(classInstance);
	return classInstance;
}

/*!*****************************************************************************
\brief
Calls a mono method by script name and function name.
*******************************************************************************/
void MonoManager::CallMethod(std::string _scriptName, const char* _function, int _paramCount) {
	MonoObject* monoInstance = GetMonoComponent(_scriptName);

	if (monoInstance == nullptr) std::cout << "Failed to get an instance to Mono object from member map mMonoComponents!\n";

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
		//std::cout << "Calling method...\n";
		mono_runtime_invoke(method, monoInstance, nullptr, &exception);

		// Handle the exception
		if (exception) {
			MonoString* exceptionString = mono_object_to_string(exception, nullptr);
			const char* exceptionCString = mono_string_to_utf8(exceptionString);
			std::cout << "Failed to call method " << _function << "()!\n";
			std::cout << "Error " << exceptionCString << " thrown!\n";
			mono_print_unhandled_exception(exception);
			BREAKPOINT(true);
		}
	}
}

/*!*****************************************************************************
\brief
Register the C# scripts to store internally for the logic system to use.
*******************************************************************************/
void MonoManager::RegisterMonoScript(std::string _namespace, std::string _class) {
	if (GetMonoComponent(_class) == nullptr) {
		std::cout << "Registering C# script method " << _namespace << "::" << _class << "()...\n";
		// Loading mono image
		MonoObject* newInstance = InstantiateClass(_namespace.c_str(), _class.c_str());
		// Storing mono object
		if (newInstance != nullptr) SetMonoComponent(_class, newInstance);
		else std::cout << "Failed to register C# script method " << _namespace << "::" << _class << "()!\n";

		mMonoHandler = mono_gchandle_new(newInstance, true);
	}
}

/*!*****************************************************************************
\brief
Set the mono script component in the member map mMonoComponents.
*******************************************************************************/
void MonoManager::SetMonoComponent(std::string _class, MonoObject* _monoObject) {
	mMonoComponents[_class] = _monoObject;
}

/*!*****************************************************************************
\brief
Get the mono script component from the member map mMonoComponents by class name.
*******************************************************************************/
MonoObject* MonoManager::GetMonoComponent(std::string _class) {
	return mMonoComponents[_class];
}

/*!*****************************************************************************
\brief
Close Mono and free & unload the domain.
*******************************************************************************/
void MonoManager::CloseMono() {
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

	mono_gchandle_free(mMonoHandler);
}