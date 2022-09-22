//#include "Physics2DManager.h"

#include "ECSManager.h"

void Physics2DManager::Init() {
	Physics2DManager::Init(mEntities);
}

void Physics2DManager::Init(const std::set<Entity> &_entityList) {
	Physics2DManager::mPhysicsFirstUpdate = std::unordered_set<const Entity*>();

	for (const Entity &e : _entityList)
		if (e.HasComponent<Physics2D>())
			Physics2DManager::mPhysicsFirstUpdate.insert(&e);
}

void Physics2DManager::UpdateFirstList() {
	Physics2DManager::UpdateFirstList(mEntities);
}

void Physics2DManager::UpdateFirstList(const std::set<Entity> &_entityList){
	// Remove non-existing entities
	for (const Entity* e : Physics2DManager::mPhysicsFirstUpdate) {
		if (!(_entityList.contains(*e))) {
			Physics2DManager::mPhysicsFirstUpdate.erase(e);
		}
	}

	// Add new entities
	for (const Entity &e : _entityList) {
		if (e.HasComponent<Physics2D>() && !(Physics2DManager::mPhysicsFirstUpdate.contains(&e)))
			Physics2DManager::mPhysicsFirstUpdate.insert(&e);
	}
}

void Physics2DManager::FirstUpdate() {
	Physics2DManager::FirstUpdate(mEntities);
}

void Physics2DManager::FirstUpdate(const std::set<Entity> &_entityList) {
	// Update the list of entities to update physics
	// for events where entity may be removed during a game loop
	Physics2DManager::UpdateFirstList(_entityList);

	// Update all required entities physics based on object rotation/orientation
	for (const Entity *e : mPhysicsFirstUpdate) {
		//glm::vec2 addVel{}, objVel{ e.GetComponent<Collider2D>().velocity };
		//double speed{ static_cast<double>(e.GetComponent<Collider2D>().speed) };
		//addVel.x = static_cast<float>(static_cast<double>(objVel.x) * speed * Helper::dt);
		//addVel.y = static_cast<float>(static_cast<double>(objVel.y) * speed * Helper::dt);
		//e.GetComponent<Transform>().translation += addVel;

		//glm::vec2 addVel{ e.GetComponent<Collider2D>().velocity * static_cast<float>(e.GetComponent<Collider2D>().speed * Helper::dt)};
		//e.GetComponent<Transform>().translation += addVel;

		// Velocity movement
		//glm::vec2 addVel{ glm::cos(e.GetComponent<Transform>().rotation), glm::sin(e.GetComponent<Transform>().rotation) };
		//addVel *= e.GetComponent<Physics2D>().speed * Helper::dt;
		//e.GetComponent<Physics2D>().velocity += addVel;
		//// Graphics translation update
		//e.GetComponent<Transform>().translation += addVel;
		//transformManager->SetTranslate(e, e.GetComponent<Transform>().translation);
		//UpdateBoundingRect(e);

		//e.GetComponent<Physics2D>().direction = { glm::cos(e.GetComponent<Transform>().rotation), glm::sin(e.GetComponent<Transform>().rotation) };
		//e.GetComponent<Physics2D>().velocity += e.GetComponent<Physics2D>().direction * e.GetComponent<Physics2D>().speed;
		//e.GetComponent<Transform>().translation += e.GetComponent<Physics2D>().velocity * static_cast<float>(Helper::dt);
		//transformManager->SetTranslate(e, e.GetComponent<Transform>().translation);

		//Physics2DManager::SetVelocity(e, Physics2DManager::GetVelocity(e) + Physics2DManager::GetMoveDirection(e) * Physics2DManager::GetSpeed(e));
		//transformManager->SetTranslate(e, transformManager->GetTranslate(e) + Physics2DManager::GetVelocity(e) * static_cast<float>(Helper::dt));

		transformManager->SetTranslate(*e, transformManager->GetTranslate(*e) + 
										glm::vec2{ glm::cos(Physics2DManager::GetMoveDirection(*e)), glm::sin(Physics2DManager::GetMoveDirection(*e)) } *Physics2DManager::GetSpeed(*e) * static_cast<float>(Helper::dt));
	}

	// Collision check
	//for (const Entity &e1 : mEntities) {
	//	// Skip to next entity if entity does not have any collider at all
	//	if (!Physics2DManager::HasCollider(e1))
	//		continue;

	//	for (const Entity &e2 : mEntities) {
	//		if (e1.id == e2.id)
	//			continue;

	//		if (!Physics2DManager::HasCollider(e2))
	//			continue;
	//		
	//		int result{ Physics2DManager::CheckCollision(e1, e2) };
	//		if (result) {
	//			// Do collision response
	//			// Physics2DManager::CollisionResponse(e1, e2, result);
	//			float tmp = Physics2DManager::GetMoveDirection(e1);
	//			Physics2DManager::SetMoveDirection(e1, Physics2DManager::GetMoveDirection(e2));
	//			Physics2DManager::SetMoveDirection(e2, tmp);
	//			transformManager->SetTranslate(e1, transformManager->GetTranslate(e1) + glm::vec2{ glm::cos(Physics2DManager::GetMoveDirection(e1)), glm::sin(Physics2DManager::GetMoveDirection(e1)) } *Physics2DManager::GetSpeed(e1) * static_cast<float>(Helper::dt));
	//			transformManager->SetTranslate(e2, transformManager->GetTranslate(e2) + glm::vec2{ glm::cos(Physics2DManager::GetMoveDirection(e2)), glm::sin(Physics2DManager::GetMoveDirection(e2)) } *Physics2DManager::GetSpeed(e2) * static_cast<float>(Helper::dt));
	//			if (e1.HasComponent<Audio>()){
	//				////audioManager->playSound(e1, 3);
	//				e1.GetComponent<Audio>().toPlay = true;
	//			}
	//			if (e2.HasComponent<Audio>()){
	//				////audioManager->playSound(e2, 4);
	//				e2.GetComponent<Audio>().toPlay = true;
	// 
	//			}
	//		}
	//	}
	//}
}

bool Physics2DManager::HasPhysicsComponent(const Entity& _e) {
	return _e.HasComponent<Physics2D>();
}

Physics2D& Physics2DManager::GetPhysicsComponent(const Entity& _e) {
	return _e.GetComponent<Physics2D>();
}

void Physics2DManager::AddPhysicsComponent(const Entity& _e, const float& _mass, const float& _speed, const float& _moveDirection, const bool& _renderFlag) {
	if (!_e.HasComponent<Physics2D>()) {	//e.AddComponent(Physics2D{ _mass, _speed, _moveDir, glm::vec2{0, 0}, _renderFlag });
		_e.AddComponent(Physics2D{ _mass, _speed, _moveDirection, _renderFlag });
		mPhysicsFirstUpdate.insert(&_e);
	}
	else {
		Physics2DManager::SetMass(_e, _mass);
		Physics2DManager::SetSpeed(_e, _speed);
		Physics2DManager::SetMoveDirection(_e, _moveDirection);
		Physics2DManager::SetPhysicsRenderFlag(_e, _renderFlag);
		if (!(mPhysicsFirstUpdate.contains(&_e)))
			mPhysicsFirstUpdate.insert(&_e);
	}
}

//void Physics2DManager::RemovePhysicsComponent(const Entity &_e) {
//
//}

float Physics2DManager::GetMass(const Entity &_e) {
	return Physics2DManager::GetPhysicsComponent(_e).mass;
}

void Physics2DManager::SetMass(const Entity &_e, const float &_mass) {
	Physics2DManager::GetPhysicsComponent(_e).mass = _mass;
}

float Physics2DManager::GetSpeed(const Entity &_e) {
	return Physics2DManager::GetPhysicsComponent(_e).speed;
}

void Physics2DManager::SetSpeed(const Entity &_e, const float &_speed) {
	Physics2DManager::GetPhysicsComponent(_e).speed = _speed;
}

float Physics2DManager::GetMoveDirection(const Entity &_e) {
	return Physics2DManager::GetPhysicsComponent(_e).moveDirection;
}

void Physics2DManager::SetMoveDirection(const Entity &_e, const float &_moveDirection){
	Physics2DManager::GetPhysicsComponent(_e).moveDirection = _moveDirection;
}

bool Physics2DManager::GetPhysicsRenderFlag(const Entity &_e) {
	return Physics2DManager::GetPhysicsComponent(_e).renderFlag;
}

void Physics2DManager::SetPhysicsRenderFlag(const Entity &_e, const bool &_renderFlag) {
	Physics2DManager::GetPhysicsComponent(_e).renderFlag = _renderFlag;
}

