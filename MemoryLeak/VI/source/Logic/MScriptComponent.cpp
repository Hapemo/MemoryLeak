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

#include "MScriptComponent.h"

// Mono generic stuff
MonoDomain* MScriptComponent::m_ptrMonoDomain = nullptr;
MonoAssembly* MScriptComponent::m_ptrGameAssembly = nullptr;
MonoImage* MScriptComponent::m_ptrGameAssemblyImage = nullptr;

// Mono Methods
MonoMethod* MScriptComponent::m_ptrTickMethod = nullptr;
MonoMethod* MScriptComponent::m_ptrKeyEventMethod = nullptr;

// Mono Object
MonoObject* MScriptComponent::m_ptrGameObject = nullptr;
uint32_t MScriptComponent::m_gameObjectGCHandle = 0;

MScriptComponent::MScriptComponent() {
	// Current directon as mono directory
	mono_set_dirs("$(TargetDir)", "$(TargetDir)");

	// Create mono domain
	m_ptrMonoDomain = mono_jit_init("MScriptComponent");
	if (m_ptrMonoDomain) {
		// Load a mono assembly script.dll
		m_ptrGameAssembly = mono_domain_assembly_open(m_ptrMonoDomain, "Scripting.dll");
		if (m_ptrGameAssembly) {
			// Loading mono image
			m_ptrGameAssemblyImage = mono_assembly_get_image(m_ptrGameAssembly);
		}
	}
}

MScriptComponent::~MScriptComponent() {
	// Release mono handles
	if (m_gameObjectGCHandle)
		mono_gchandle_free(m_gameObjectGCHandle);

	// Release the domain
	if (m_ptrMonoDomain)
		mono_jit_cleanup(m_ptrMonoDomain);
}


/*!*****************************************************************************
\brief
Run the initialisation function for all active entities' scripts.
*******************************************************************************/
void MScriptComponent::Init() {
	if (m_ptrGameAssemblyImage) {
		// Add internal calls
		mono_add_internal_call("SCRIPTING.TestClass::Init()", &MScriptComponent::Update);

		// Find ptrClass
		MonoClass* ptrClass = mono_class_from_name(m_ptrGameAssemblyImage, "SCRIPTING", "TestClass");

		if (ptrClass) {
			// Describe method
			MonoMethodDesc* ptrMainMethodDesc = mono_method_desc_new(".TestClass:Init()", false);
			if (ptrMainMethodDesc) {
				// Find Update in TestClass
				MonoMethod* ptrMainMethod = mono_method_desc_search_in_class(ptrMainMethodDesc, ptrClass);
				if (ptrMainMethod) {
					// Call main method
					MonoObject* ptrExObject = nullptr;
					m_ptrGameObject = mono_runtime_invoke(ptrMainMethod, nullptr, nullptr, &ptrExObject);
					if (m_ptrGameObject) {
						// Ref count object on c++ side
						m_gameObjectGCHandle = mono_gchandle_new(m_ptrGameObject, false);
					}
				}
				// Free desc
				mono_method_desc_free(ptrMainMethodDesc);
			}
		}
	}
}

/*!*****************************************************************************
\brief
Run the update function for all active entities' scripts.
*******************************************************************************/
void MScriptComponent::Update() {
	if (m_ptrGameAssemblyImage) {
		// Add internal calls
		mono_add_internal_call("SCRIPTING.TestClass::Update()", &MScriptComponent::Update);

		// Find ptrClass
		MonoClass* ptrClass = mono_class_from_name(m_ptrGameAssemblyImage, "SCRIPTING", "TestClass");

		if (ptrClass) {
			// Describe method
			MonoMethodDesc* ptrMainMethodDesc = mono_method_desc_new(".TestClass:Update()", false);
			if (ptrMainMethodDesc) {
				// Find Update in TestClass
				MonoMethod* ptrMainMethod = mono_method_desc_search_in_class(ptrMainMethodDesc, ptrClass);
				if (ptrMainMethod) {
					// Call main method
					MonoObject* ptrExObject = nullptr;
					m_ptrGameObject = mono_runtime_invoke(ptrMainMethod, nullptr, nullptr, &ptrExObject);
					if (m_ptrGameObject) {
						// Ref count object on c++ side
						m_gameObjectGCHandle = mono_gchandle_new(m_ptrGameObject, false);
					}
				}
				// Free desc
				mono_method_desc_free(ptrMainMethodDesc);
			}
		}
	}
}

/*!*****************************************************************************
\brief
Run the exit function for all active entities' scripts.
*******************************************************************************/
void MScriptComponent::Exit() {
	if (m_ptrGameAssemblyImage) {
		// Add internal calls
		mono_add_internal_call("SCRIPTING.TestClass::Exit()", &MScriptComponent::Update);

		// Find ptrClass
		MonoClass* ptrClass = mono_class_from_name(m_ptrGameAssemblyImage, "SCRIPTING", "TestClass");

		if (ptrClass) {
			// Describe method
			MonoMethodDesc* ptrMainMethodDesc = mono_method_desc_new(".TestClass:Exit()", false);
			if (ptrMainMethodDesc) {
				// Find Update in TestClass
				MonoMethod* ptrMainMethod = mono_method_desc_search_in_class(ptrMainMethodDesc, ptrClass);
				if (ptrMainMethod) {
					// Call main method
					MonoObject* ptrExObject = nullptr;
					m_ptrGameObject = mono_runtime_invoke(ptrMainMethod, nullptr, nullptr, &ptrExObject);
					if (m_ptrGameObject) {
						// Ref count object on c++ side
						m_gameObjectGCHandle = mono_gchandle_new(m_ptrGameObject, false);
					}
				}
				// Free desc
				mono_method_desc_free(ptrMainMethodDesc);
			}
		}
	}
}
