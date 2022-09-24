/*!
file:	Singleton.h
author:	Jazz Teoh Yu Jue
date:	16/05/2022

email:	j.teoh@digipen.edu

brief:	Singleton base class, a design pattern that allows creation of only one instance
		of a class. 

		All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*//*__________________________________________________________________________________*/

#pragma once

#include "ISingleton.h"

template <typename T>
class Singleton : public ISingleton{
private:
	static T* instance;

	/***************************************************************************/
	/*!
		\brief
			Frees the singleton memory if it exists
	*/
	/**************************************************************************/
	void Destroy() {
		if (instance) {
			delete instance;
			instance = nullptr;
		}
	}

protected:
	Singleton() { std::cout << "Singleton Constructor called\n"; }

public:
	// Default ctor and dtor
	~Singleton() {}

	// To disable any copying mechanism for Singleton
	Singleton(const Singleton&) = delete;
	Singleton& operator= (const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator= (Singleton&&) = delete;

	/***************************************************************************/
	/*!
		\brief
			Returns the Singleton instance, make one if there is none
		\return
			Current singleton instance
	*/
	/**************************************************************************/
	static T* GetInstance() {
		if (!instance) instance = new T;
		return instance;
	}

};

template<typename T>
T* Singleton<T>::instance = nullptr;


