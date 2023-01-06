///*!*****************************************************************************
//\file MonoComponent.cpp
//\author Chen Jia Wen
//\par DP email: c.jiawen\@digipen.edu
//\par Course: GAM200
//\par Group: Memory Leak Studios
//\date 04-01-2023
//\brief
//This file contains the function definitions of the class MonoComponent.
//The MonoComponent class handles the C# scripting for the engine.
//*******************************************************************************/
//
//#include "MonoComponent.h"
////#include "Logger.h"
//
///*!*****************************************************************************
//\brief
//Run the exit function for all active entities' scripts.
//*******************************************************************************/
//void MonoComponent::EndScript() {
//	//if (m_ptrGameAssemblyImage) {
//	//	// Add internal calls
//	//	mono_add_internal_call("SCRIPTING.TestClass::Exit()", &MScriptComponent::EndScript);
//
//	//	// Find ptrClass
//	//	MonoClass* ptrClass = mono_class_from_name(m_ptrGameAssemblyImage, "SCRIPTING", "TestClass");
//
//	//	if (ptrClass) {
//	//		// Describe method
//	//		MonoMethodDesc* ptrMainMethodDesc = mono_method_desc_new(".TestClass:Exit()", false);
//	//		if (ptrMainMethodDesc) {
//	//			// Find Update in TestClass
//	//			MonoMethod* ptrMainMethod = mono_method_desc_search_in_class(ptrMainMethodDesc, ptrClass);
//	//			if (ptrMainMethod) {
//	//				// Call main method
//	//				MonoObject* ptrExObject = nullptr;
//	//				m_ptrGameObject = mono_runtime_invoke(ptrMainMethod, nullptr, nullptr, &ptrExObject);
//	//				if (m_ptrGameObject) {
//	//					// Ref count object on c++ side
//	//					m_gameObjectGCHandle = mono_gchandle_new(m_ptrGameObject, false);
//	//				}
//	//			}
//	//			// Free desc
//	//			mono_method_desc_free(ptrMainMethodDesc);
//	//		}
//	//	}
//	//}
//}
