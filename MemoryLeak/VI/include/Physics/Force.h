#pragma once

#include "pch.h"

class Force {
public:
	Force() {}
	Force(const Force& _rhs) {
		*this = _rhs;
	}
	~Force() {}
	Force& operator=(const Force& _rhs) {
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

		return *this;
	}

	double lifetimeLimit{0.f};
	double age{0.f};
	bool isActive{true};
	int forceID;
	union {
		struct LinearForce {
			Math::Vec2 unitDirection;
			float magnitude;
		} linearForce;
		struct RotationalForce {
			float torque;
		} rotationalForce;
		struct DragForce {
			float	directionalDrag;
			float	rotationalDrag;
		} dragForce;
	};
};