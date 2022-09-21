/*!
file:	SingletonManager.h
author:	Jazz Teoh Yu Jue
date:	16/05/2022

email:	j.teoh@digipen.edu

brief:	Singleton Manager keeps a list of all Singletons and free their memory together

		All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*//*__________________________________________________________________________________*/
#pragma once

#include "pch.h"

class ISingleton;

class SingletonManager {
private:
	static std::vector<ISingleton*> singletons;

	// Default ctor and dtor
	SingletonManager() {}
	~SingletonManager() {}


public:
	// To disable any copying mechanism for Singleton
	SingletonManager(const SingletonManager&) = delete;
	SingletonManager& operator= (const SingletonManager&) = delete;
	SingletonManager(SingletonManager&&) = delete;
	SingletonManager& operator= (SingletonManager&&) = delete;

	/***************************************************************************/
	/*!
		\brief
			Adds a singleton to the manager, mainly used by Singleton ctor
		\param singleton
			ISingleton pointer to the singleton added
	*/
	/**************************************************************************/
	static void addSingleton(ISingleton* singleton);

	/***************************************************************************/
	/*!
		\brief
			Deallocate all singleton's heap memory
	*/
	/**************************************************************************/
	static void destroyAllSingletons();
};