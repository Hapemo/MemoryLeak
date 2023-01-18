#include "../Physics/QuadTree.h"
#include "ECS_components.h"


QuadTree::QuadTree(const int &_level, const Math::Vec2 &_center, const Math::Vec2 &_scale) : mLevel(_level), mCenter(_center), mScale(_scale) {
	mLeaf[0] = nullptr;
	mLeaf[1] = nullptr;
	mLeaf[2] = nullptr;
	mLeaf[3] = nullptr;
}

void QuadTree::UpdateQuadTreeSize(const Math::Vec2& _center, const Math::Vec2& _scale) {

}

void QuadTree::Clear() {
	this->mEntityList.clear();

	for (int i{ 0 }; i < 4; ++i) {
		if (mLeaf[i] !- nullptr)
			mLeaf[i]->Clear();
	}
}

void QuadTree::DestroyTree() {
	this->mEntityList.clear();

	for (int i{ 0 }; i < 4; ++i){
		if (mLeaf[i] != nullptr) {
			mLeaf[i]->DestroyTree();
			delete mLeaf[i];
			mLeaf[i] = nullptr;
		}
	}
}

void QuadTree::Spilt() {
	Math::Vec2 newScale{ this->mScale / 2.f };
	mLeaf[1] = new QuadTree(this->mLevel + 1, Math::Vec2{this->mCenter.x - newScale.x / 2.f, this->mCenter.y + newScale.y / 2.f}, newScale);
	mLeaf[0] = new QuadTree(this->mLevel + 1, Math::Vec2{this->mCenter.x + newScale.x / 2.f, this->mCenter.y + newScale.y / 2.f}, newScale);
	mLeaf[2] = new QuadTree(this->mLevel + 1, Math::Vec2{this->mCenter.x - newScale.x / 2.f, this->mCenter.y - newScale.y / 2.f}, newScale);
	mLeaf[3] = new QuadTree(this->mLevel + 1, Math::Vec2{this->mCenter.x + newScale.x / 2.f, this->mCenter.y - newScale.y / 2.f}, newScale);
}

int QuadTree::GetQuadrant(const Entity& _e, const bool &_UseCollider) {
	int result{ -1 };

	Math::Vec2 _center{ _e.GetComponent<Transform>().translation },
				_scale{ _e.GetComponent<Transform>().scale };
	
	if (_UseCollider) {
		if (_e.HasComponent<RectCollider>()) {
			_center += _e.GetComponent<RectCollider>().centerOffset;
			_scale.x *= _e.GetComponent<RectCollider>().scaleOffset.x;
			_scale.y *= _e.GetComponent<RectCollider>().scaleOffset.y;
		}
		else if (_e.HasComponent<CircleCollider>()) {
			_center += _e.GetComponent<CircleCollider>().centerOffset;
			_scale *= _e.GetComponent<CircleCollider>().scaleOffset;
			if (_scale.x < _scale.y)
				_scale.x = _scale.y;
			else if (_scale.x > _scale.y)
				_scale.y = _scale.x;
		}
	}

	// Object bounding box
	Math::Vec2 objMax{ _center + _scale }, 
				objMin{ _center - _scale };

	// Above or Below center
	bool upperQuad{ objMax.y > this->mCenter.y && objMin.y > this->mCenter.y },
		lowerQuad{ objMax.y < this->mCenter.y&& objMin.y < this->mCenter.y };

	// Right of center
	if (objMax.x > this->mCenter.x && objMin.x > this->mCenter.x) {
		if (upperQuad)
			result = 0;	
		else if (lowerQuad)
			result = 3;	
	}	// Left of center
	else if (objMax.x < this->mCenter.x && objMin.x < this->mCenter.x) {
		if (upperQuad)
			result = 1;	
		else  if (lowerQuad)
			result = 2;	
	}

	return result;
}

void QuadTree::Insert(const Entity& _e) {
	// Check if parent node has alr been spilt
	if (mLeaf[0] != nullptr) {
		int result{ GetQuadrant(_e) };

		if (result != -1) {
			mLeaf[result]->Insert(_e);
			return;
		}
	}

	mEntityList.emplace_back(_e);

	if (this->mEntityList.size() + 1 > MAX_OBJ_PER_NODE && this->mLevel < MAX_SUBLEVELS) {
		if (mLeaf[0] == nullptr)
			Spilt();

		int i{ 0 };
		for (auto it{ mEntityList.begin() }; it < mEntityList.end();) {
			int result{ GetQuadrant(*it) };
			if (result != -1) {
				mLeaf[result]->Insert(*it);
				it = mEntityList.erase(it);
			}
			else
				++it;
		}
	}
}

void QuadTree::Retrieve(std::vector<Entity> &_returnList, const Entity& _e) {
	int result{ GetQuadrant(_e) };
	if (result != -1 && mLeaf[result] != nullptr) {
		mLeaf[result]->Retrieve(_returnList, _e);
	}

	for (int i{ 0 }; i < mEntityList.size(); ++i)
		_returnList.emplace_back(mEntityList[i]);
}

