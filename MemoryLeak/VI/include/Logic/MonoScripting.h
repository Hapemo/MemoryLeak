/*!*****************************************************************************
\file MonoScipting.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 19-10-2022
\brief
This file contains the function declarations of the class MonoScipting.
The MonoScipting class handles the C# scripting for the engine.
*******************************************************************************/

#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

#include "Singleton.h"
#include <string>
#include <vector>

class MonoScripting : public Singleton<MonoScripting>
{
public:
	/*!*****************************************************************************
	\brief
	Default constructor and destructor.
	*******************************************************************************/
	MonoScripting();
	~MonoScripting();

	/*!*****************************************************************************
	\brief
	Delete copy constructor.
	*******************************************************************************/
	MonoScripting(const MonoScripting&) = delete;
	const MonoScripting& operator=(const MonoScripting&) = delete;

private:
	// Mono generic stuff
	MonoDomain* m_ptrMonoDomain = nullptr;
	MonoAssembly* m_ptrGameAssembly = nullptr;
	MonoImage* m_ptrGameAssemblyImage = nullptr;
};
