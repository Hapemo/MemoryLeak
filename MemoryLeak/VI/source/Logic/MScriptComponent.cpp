/*!*****************************************************************************
\file MScriptComponent.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 19-10-2022
\brief
This file contains the function definitions of the class MScriptComponent.
The MScriptComponent class handles the C# scripting for the engine.
*******************************************************************************/

#include <filesystem>
#include "pch.h"
#include "MScriptComponent.h"
//#include "Logger.h"

// Mono generic stuff
MonoDomain* MScriptComponent::mDomain = nullptr;
MonoAssembly* MScriptComponent::mAssembly = nullptr;

// Mono Object
MonoObject* MScriptComponent::m_ptrGameObject = nullptr;
uint32_t MScriptComponent::m_gameObjectGCHandle = 0;

std::string MScriptComponent::MonoDirectoryPath() {
	std::string path = std::filesystem::current_path().parent_path().string() + "\\bin\\";
#ifdef NDEBUG
	path += "Release";
#else
	path += "Debug";
#endif
	path += "\\x64\\SCRIPTING";
	mono_set_dirs(path.c_str(), path.c_str());
	return path;
}

bool MScriptComponent::InitMonoDomain(const char* _domain, const std::string _directory, const std::string _dll) {
	std::cout << "Creating Mono domain...\n";
	mDomain = mono_jit_init(_domain);
	if (mDomain) {
		std::cout << "Loading Mono assembly...\n";
		// Load a mono assembly script.dll
		mAssembly = mono_domain_assembly_open(mDomain, (_directory + '\\' + _dll + ".dll").c_str());
		if (!mAssembly) {
			std::cout << "Failed to load Mono assembly from: " << _directory + '\\' << _dll << ".dll!\n";
			return false;
		} else return true;
	} else {
		std::cout << "Failed to initialise Mono domain: " << _domain << "!\n";
		return false;
	}
}

MonoClass* MScriptComponent::GetClassInAssembly(MonoAssembly* _assembly, const char* _namespace, const char* _class) {
	std::cout << "Loading Mono image...\n";
	MonoImage* assemblyImage = mono_assembly_get_image(_assembly);
	std::cout << "Retrieving Mono class...\n";
	MonoClass* monoClass = mono_class_from_name(assemblyImage, _namespace, _class);
	if (monoClass == nullptr) {
		std::cout << "Failed to retrieve Mono class: " << _namespace << "::" << _class << "!\n";
		return nullptr;
	}
	//mono_image_close(assemblyImage);
	return monoClass;
}

MonoObject* MScriptComponent::InstantiateClass(const char* _namespace, const char* _class) {
	// Get a reference to the class to instantiate
	MonoClass* monoClass = GetClassInAssembly(mAssembly, _namespace, _class);

	// Allocate an instance of the class
	MonoObject* classInstance = mono_object_new(mDomain, monoClass);

	if (classInstance == nullptr) {
		std::cout << "Failed to allocate an instance to Mono class: " << _namespace << "::" << _class << "!\n";
		return nullptr;
	}

	// Call the parameterless (default) constructor
	mono_runtime_object_init(classInstance);
	return classInstance;
}

void MScriptComponent::CallMethod(MonoObject* _objectInstance, const char* _function, int _paramCount) {
	// Get the MonoClass pointer from the instance
	MonoClass* instanceClass = mono_object_get_class(_objectInstance);

	// Get a reference to the method in the class
	MonoMethod* method = mono_class_get_method_from_name(instanceClass, _function, _paramCount);

	if (method == nullptr) {
		// No method called "Init" with 0 parameters in the class, log error or something
		return;
	}

	// Call the C# method on the objectInstance instance, and get any potential exceptions
	MonoObject* exception = nullptr;
	mono_runtime_invoke(method, _objectInstance, nullptr, &exception);

	// TODO: Handle the exception
}

MonoString* MScriptComponent::TestFunction() {
	std::cout << "Calling internal call success!\n";
	return mono_string_new(mono_domain_get(), "Hello!");
}

MScriptComponent::MScriptComponent() {
	// Set and get mono directory
	std::string path = MonoDirectoryPath();

	// Create mono domain
	bool success = InitMonoDomain("MScriptComponent", path, "Scripting");
	if (success) {
		// Loading mono image
		MonoObject* testInstance = InstantiateClass("SCRIPTING", "TestClass");
		CallMethod(testInstance, "Init", 0);
		std::cout << "Calling method...\n";

		// Test internal functions
		mono_add_internal_call("SCRIPTING.TestClass::TestFunction", &MScriptComponent::TestFunction);
	}
}

MScriptComponent::~MScriptComponent() {
	// Release mono handles
	if (m_gameObjectGCHandle)
		mono_gchandle_free(m_gameObjectGCHandle);

	mono_domain_set(mono_get_root_domain(), false);

	// Release the domain
	if (mDomain) {
		mono_domain_unload(mDomain);
		mono_domain_free(mDomain, false);
		//mDomain = nullptr;
		mono_jit_cleanup(mDomain);
	}
}


/*!*****************************************************************************
\brief
Run the initialisation function for all active entities' scripts.
*******************************************************************************/
void MScriptComponent::StartScript(Entity const& gob) {
	(void)gob;
	std::cout << "Mono Start Script...\n";
	//if (mAssemblyImage) {
	//	// Add internal calls
	//	// mono_add_internal_call("SCRIPTING.TestClass::Init()", &MScriptComponent::StartScript);

	//	// Find ptrClass
	//	MonoClass* ptrClass = mono_class_from_name(mAssemblyImage, "SCRIPTING", "TestClass");

	//	if (ptrClass) {
	//		std::cout << "Mono ptrClass exist...\n";
	//		//LOG_INFO("Mono ptrClass exist.");
	//		// Describe method
	//		MonoMethodDesc* ptrMainMethodDesc = mono_method_desc_new(".TestClass:Init()", false);
	//		if (ptrMainMethodDesc) {
	//			// Find Update in TestClass
	//			MonoMethod* ptrMainMethod = mono_method_desc_search_in_class(ptrMainMethodDesc, ptrClass);
	//			if (ptrMainMethod) {
	//				// Call main method
	//				MonoObject* ptrExObject = nullptr;
	//				m_ptrGameObject = mono_runtime_invoke(ptrMainMethod, nullptr, nullptr, &ptrExObject);
	//				if (m_ptrGameObject) {
	//					// Ref count object on c++ side
	//					m_gameObjectGCHandle = mono_gchandle_new(m_ptrGameObject, false);
	//				}
	//			}
	//			// Free desc
	//			mono_method_desc_free(ptrMainMethodDesc);
	//		}
	//	}
	//}
}

/*!*****************************************************************************
\brief
Run the update function for all active entities' scripts.
*******************************************************************************/
void MScriptComponent::UpdateScript(Entity const& gob) {
	(void)gob;
	//if (m_ptrGameAssemblyImage) {
	//	// Add internal calls
	//	mono_add_internal_call("SCRIPTING.TestClass::Update()", &MScriptComponent::UpdateScript);

	//	// Find ptrClass
	//	MonoClass* ptrClass = mono_class_from_name(m_ptrGameAssemblyImage, "SCRIPTING", "TestClass");

	//	if (ptrClass) {
	//		// Describe method
	//		MonoMethodDesc* ptrMainMethodDesc = mono_method_desc_new(".TestClass:Update()", false);
	//		if (ptrMainMethodDesc) {
	//			// Find Update in TestClass
	//			MonoMethod* ptrMainMethod = mono_method_desc_search_in_class(ptrMainMethodDesc, ptrClass);
	//			if (ptrMainMethod) {
	//				// Call main method
	//				MonoObject* ptrExObject = nullptr;
	//				m_ptrGameObject = mono_runtime_invoke(ptrMainMethod, nullptr, nullptr, &ptrExObject);
	//				if (m_ptrGameObject) {
	//					// Ref count object on c++ side
	//					m_gameObjectGCHandle = mono_gchandle_new(m_ptrGameObject, false);
	//				}
	//			}
	//			// Free desc
	//			mono_method_desc_free(ptrMainMethodDesc);
	//		}
	//	}
	//}
}

/*!*****************************************************************************
\brief
Run the exit function for all active entities' scripts.
*******************************************************************************/
void MScriptComponent::EndScript(Entity const& gob) {
	(void)gob;
	//if (m_ptrGameAssemblyImage) {
	//	// Add internal calls
	//	mono_add_internal_call("SCRIPTING.TestClass::Exit()", &MScriptComponent::EndScript);

	//	// Find ptrClass
	//	MonoClass* ptrClass = mono_class_from_name(m_ptrGameAssemblyImage, "SCRIPTING", "TestClass");

	//	if (ptrClass) {
	//		// Describe method
	//		MonoMethodDesc* ptrMainMethodDesc = mono_method_desc_new(".TestClass:Exit()", false);
	//		if (ptrMainMethodDesc) {
	//			// Find Update in TestClass
	//			MonoMethod* ptrMainMethod = mono_method_desc_search_in_class(ptrMainMethodDesc, ptrClass);
	//			if (ptrMainMethod) {
	//				// Call main method
	//				MonoObject* ptrExObject = nullptr;
	//				m_ptrGameObject = mono_runtime_invoke(ptrMainMethod, nullptr, nullptr, &ptrExObject);
	//				if (m_ptrGameObject) {
	//					// Ref count object on c++ side
	//					m_gameObjectGCHandle = mono_gchandle_new(m_ptrGameObject, false);
	//				}
	//			}
	//			// Free desc
	//			mono_method_desc_free(ptrMainMethodDesc);
	//		}
	//	}
	//}
}
