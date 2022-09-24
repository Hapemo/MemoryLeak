/*!
file:	ISingleton.h
author:	Jazz Teoh Yu Jue
date:	16/05/2022

email:	j.teoh@digipen.edu

brief:	ISingleton is only used to provide polymorphism control for SingletonManager. This
		is necessary since Singleton class is templatized

		All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*//*__________________________________________________________________________________*/

#pragma once

#include "SingletonManager.h"

class ISingleton {
public:
	/***************************************************************************/
	/*!
		\brief
			Adds a singleton to the SingletonManager
	*/
	/**************************************************************************/
	ISingleton() { SingletonManager::addSingleton(this); }
	
	// Default dtor
	~ISingleton() {}

	// To disable any copying mechanism for Singleton
	ISingleton(const ISingleton&) = delete;
	ISingleton& operator= (const ISingleton&) = delete;
	ISingleton(ISingleton&&) = delete;
	ISingleton& operator= (ISingleton&&) = delete;

	// Deallocate heap memory
	virtual void Destroy() = 0;
};