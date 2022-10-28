/*!*****************************************************************************
\file MonoScripting.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 19-10-2022
\brief
This file contains the function definitions of the class MonoScipting.
The MonoScipting class handles the C# scripting for the engine.
*******************************************************************************/

#include "MonoScripting.h"

MonoScripting::MonoScripting() {
	// Current directon as mono directory
	mono_set_dirs(".", ".");

	// Create mono domain
	m_ptrMonoDomain = mono_jit_init("MonoScripting");
	if (m_ptrMonoDomain) {
		// Load a mono assembly script.dll
		m_ptrGameAssembly = mono_domain_assembly_open(m_ptrMonoDomain, "TestScript.dll");
		if (m_ptrGameAssembly) {
			// Loading mono image
			m_ptrGameAssemblyImage = mono_assembly_get_image(m_ptrGameAssembly);
			if (m_ptrGameAssemblyImage) {
				int i = 0;
			}
		}
	}
}

MonoScripting::~MonoScripting() {
	// Release the domain
	if (m_ptrMonoDomain)
		mono_jit_cleanup(m_ptrMonoDomain);
}
