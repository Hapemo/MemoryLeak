/*!*****************************************************************************
\file	Force.h
\author Lee Hsien Wei, Joachim
\par	DP email: l.hsienweijoachim@digipen.edu
\par	Course: GAM200
\par	Group: Memory Leak Studios
\date	27-09-2022
\brief  This file contains the declaration of the Force class, its member 
		functions and its data members which encapsulates information about
		a force that needs to be acted on an entity
*******************************************************************************/
#pragma once

// -----------------------------
// Include files
// -----------------------------
#include "pch.h"

/*!*****************************************************************************
\brief Force class that encapsulates information about the Force and its 
		different types
*******************************************************************************/
class Force {
public:
	/*!*****************************************************************************
	\brief
	Default constructor. Required to nullify errors
	\return void
	NULL
	*******************************************************************************/
	Force() {}

	/*!*****************************************************************************
	\brief
	Default copy constructor. Required to nullify errors. Calls assignment operator
	\param const Force &
	A reference to a read-only force to copy from
	*******************************************************************************/
	Force(const Force& _rhs) {
		*this = _rhs;
	}

	/*!*****************************************************************************
	\brief
	Default destructor. Required to nullify errors
	*******************************************************************************/
	~Force() {}

	/*!*****************************************************************************
	\brief
	Assignment operator that assigns values to be the same as the given Force
	\param const Force &
	A reference to a read-only force to reference from
	\return Force &
	Returns itself
	*******************************************************************************/
	Force& operator=(const Force& _rhs) {
		// Copy data members
		this->lifetimeLimit = _rhs.lifetimeLimit;
		this->age = _rhs.age;
		this->isActive = _rhs.isActive;
		this->forceID = _rhs.forceID;
		switch (this->forceID) {
		case 0:
			this->linearForce = _rhs.linearForce;
			break;
		case 1:
			this->rotationalForce = _rhs.rotationalForce;
			break;
		case 2:
			this->dragForce = _rhs.dragForce;
			break;
		}

		// Return itself
		return *this;
	}

	/*!*****************************************************************************
	Class variables
	*******************************************************************************/
	double lifetimeLimit{0.f};	// Maximum lifetime
	double age{0.f};			// Current lifespan
	bool isActive{true};		// Is it an active force
	int forceID;				// Force ID to identify how to access the union
	union {
		// Linear force
		struct LinearForce {
			Math::Vec2 unitDirection;
			float magnitude;
		} linearForce;
		// Rotation force
		struct RotationalForce {
			float torque;
		} rotationalForce;
		// Drag force
		struct DragForce {
			float	directionalDrag;
			float	rotationalDrag;
		} dragForce;
	};
};