/*!*****************************************************************************
\file	LayerManager.h
\author Lee Hsien Wei, Joachim
\par	DP email: l.hsienweijoachim@digipen.edu
\par	Course: GAM200
\par	Group: Memory Leak Studios
\date	26-11-2022
\brief  This file contains the declaration of the Layer Manager Class and its
		member functions. It handles the updating of the layer values
		of each entity through the use of a layer collider
*******************************************************************************/
#pragma once

// -----------------------------
// Include files
// -----------------------------
#include "ECS_systems.h"
#include "./Physics/ColliderType.h"
#include "./Physics/Contact.h"

/*!*****************************************************************************
\brief Layer Manager system class that handles the updating of layer values of 
	   entities.
*******************************************************************************/
class LayerManager : public System {
public:
	/*!*****************************************************************************
	\brief
	CI_RectvsRect function that is modified to handle layer collider that does not
	require dynamic checks
	\param Contact &
	A reference to struct containing entity pair data to check
	\return bool
	Evaluated result of whether collision has occurred between the given entity pair
	*******************************************************************************/
	static bool CI_RectvsRect(Contact& _contact);

	/*!*****************************************************************************
	\brief
	Update function that checks which entities layer collider collides and stores that
	as a contact info for resolution of the layer values
	\return void
	NULL
	*******************************************************************************/
	void Update();
	
	void Step();
private:
	std::vector<Contact> mUpdateList;					// List of collided layer contacts
	std::unordered_map<Entity*, int> mOriginLayerMap;	// Container that stores the original layer value

	double mAccumulatedDT{ 0.0 };
	const double mFixedDT{ 1.0 / 60.0 };
	double mAccumulatedDTCap{ 1.0 };
};