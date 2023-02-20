/*!
file:	ParticleSystem.cpp
author:	Jazz Teoh Yu Jue

email:	j.teoh@digipen.edu

brief:	Particle System class. This is a singleton where it keeps track of all the particle
		operation in the game.

		All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*//*__________________________________________________________________________________*/
#include "ParticleManager.h"
#include "Camera.h"
#include "pch.h"
#include "Helper.h"
#include "Utilities.h"
#include "ECS_tools.h"
//#include "GameObject.h"
#include "SpriteVariable.h"


uint64_t ParticleManager::mParticleCount{};
bool		 ParticleManager::mParticleChange{};

//==============================
// Particle 
//==============================
Particle::Particle() : mTransform(), mVelocity(), mColor(), mLifespan(), mMaxLifespan(), mEntity() {}

void Particle::Init(Vec2 _velocity, Transform _transform, float _lifespan, EntityID _e) {
	mVelocity = _velocity;
	mTransform = _transform;
	mColor = ECS::GetComponent<ParticleSystem>(_e).mParticleInfo.mSprite.color;
	mMaxLifespan = mLifespan = _lifespan;
	mEntity = _e;
	ParticleManager::ParticleChanged();
}

void Particle::Update() {
	if (mLifespan == 0) {
		LOG_WARN("Should not be updating inactive particle");
		return;
	} else if ((mLifespan -= static_cast<float>(FPSManager::dt)) < 0) { // Update Lifespan
		Destroy();
		return;
	}

	ParticleSystem const& system{ ECS::GetComponent<ParticleSystem>(mEntity) };

	// Update position
	mTransform.translation += static_cast<float>(FPSManager::dt) * mVelocity;

	// Update rotation
	mTransform.rotation += system.mParticleInfo.mRotation * static_cast<float>(FPSManager::dt);
	//float radDT = system.mParticleInfo.mRotation * FPSManager::dt;
	//float cos = cosf(radDT);
	//float sin = sinf(radDT);
	//mFacing = Vec2{ cos * mFacing.x - sin * mFacing.y,
	//								sin * mFacing.x + cos * mFacing.y }.Normalize();

	// Update Color/Alpha
	if (system.mParticleInfo.mFading) {
		mColor.a = static_cast<GLubyte>(mLifespan / mMaxLifespan);
	}

}

void Particle::Destroy() {
	memset(this, 0, sizeof(Particle));
	ParticleManager::DecreaseParticleCount();
	ParticleManager::ParticleChanged();
}

//==============================
// Particle Manager
//==============================
ParticleManager::ParticleManager() : mParticles() { srand(static_cast<unsigned int>(time(0))); }

void ParticleManager::UpdateSystems() {
	for (auto& e : mEntities) {
		if (!e.ShouldRun()) continue;
		ParticleSystem& system{ e.GetComponent<ParticleSystem>() };
		if (!system.mIsActive) continue;

		GenerateParticle(system, e.id);
	}

	if (mParticleChange)
		std::sort(mParticles.begin(), mParticles.end(), [] (Particle p1, Particle p2) { return p1.GetIsActive() > p2.GetIsActive(); });
}

void ParticleManager::UpdateParticles() {
	for (int i{}; i < mParticleCount; ++i)
		mParticles[i].Update();

}

void ParticleManager::Update() {
	mParticleChange = false;
	UpdateSystems();
	UpdateParticles();
}

void ParticleManager::Reset() {
	LOG_INFO("Reset Particle Manager of size " + std::to_string(sizeof(ParticleManager)));
	memset(&mParticles, 0, mParticles.size() * sizeof(Particle));
	mParticleChange = false;
	mParticleCount = 0;
}

void ParticleManager::GenerateParticle(ParticleSystem const& _system, EntityID _e) {
	for (int i{}; i < _system.mDensity; ++i) {
		Particle& currP = mParticles[mParticleCount++];

		//Initialise the particle and give it a random position and direction to move from
		Transform trans{};
		trans.rotation = _system.mParticleInfo.mFacing;
		trans.scale *= _system.mParticleInfo.mScale;
		trans.translation = _system.mCenter + Vec2(static_cast<float>(Util::RandInt(-static_cast<int>(_system.mAreaWidth) / 2, static_cast<int>(_system.mAreaWidth) / 2)),
																							 static_cast<float>(Util::RandInt(-static_cast<int>(_system.mAreaWidth) / 2, static_cast<int>(_system.mAreaWidth) / 2)));


		float angle = Util::RandInt(static_cast<int>(-_system.mSpread) * 10, static_cast<int>(_system.mSpread) * 10) / 10.f;
		float cos = cosf(angle);
		float sin = sinf(angle);

		Vec2 vel = Vec2{ cos * _system.mDirection.x - sin * _system.mDirection.y,
										 sin * _system.mDirection.x + cos * _system.mDirection.y }.Normalize() * _system.mParticleInfo.mSpeed;

		currP.Init(std::move(vel), trans, _system.mParticleInfo.mLifespan, _e);
	}

}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
