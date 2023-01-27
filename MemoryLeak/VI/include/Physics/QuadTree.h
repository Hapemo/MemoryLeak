#pragma once

#include "pch.h"
#include "ECS_items.h"
#include "..\ECS\ECS_components.h"

class QuadBox {
public:
	QuadBox(const Math::Vec2& _center = Math::Vec2{0.f, 0.f}, const Math::Vec2& _scale = Math::Vec2{0.f, 0.f}, const Math::Vec2& _centerOffset = Math::Vec2{0.f, 0.f}, const Math::Vec2& _scaleOffset = Math::Vec2{0.f, 0.f}) : 
		_mCenter(_center), _mScale(_scale), _mCenterOffset(_centerOffset), _mScaleOffset(_scaleOffset) {
	}

	QuadBox(const Entity& _entity) {
		if (_entity.HasComponent<RectCollider>()) {
			this->_mCenter = _entity.GetComponent<Transform>().translation;
			this->_mScale = _entity.GetComponent<Transform>().scale;
			this->_mCenterOffset = _entity.GetComponent<RectCollider>().centerOffset;
			this->_mScaleOffset = _entity.GetComponent<RectCollider>().scaleOffset;
		}
		else if (_entity.HasComponent<CircleCollider>()) {
			this->_mCenter = _entity.GetComponent<Transform>().translation;
			this->_mScale = _entity.GetComponent<Transform>().scale;
			this->_mCenterOffset = _entity.GetComponent<CircleCollider>().centerOffset;
			this->_mScaleOffset = Math::Vec2{ _entity.GetComponent<CircleCollider>().scaleOffset, _entity.GetComponent<CircleCollider>().scaleOffset };
		}
	}
	
	float GetLeft() const {
		return _mCenter.x + _mCenterOffset.x - fabs(_mScale.x * _mScaleOffset.x) / 2.f;
	}

	float GetRight() const {
		return _mCenter.x + _mCenterOffset.x + fabs(_mScale.x * _mScaleOffset.x) / 2.f;
	}

	float GetTop() const {
		return _mCenter.y + _mCenterOffset.y + fabs(_mScale.y * _mScaleOffset.y) / 2.f;
	}

	float GetBottom() const {
		return _mCenter.y + _mCenterOffset.y - fabs(_mScale.y * _mScaleOffset.y) / 2.f;
	}

	Math::Vec2 GetCenterOffsetted() const {
		return _mCenter + _mCenterOffset;
	}

	Math::Vec2 GetScaleOffsetted() const {
		Math::Vec2 _actualScale{ _mScale };
		_actualScale.x *= _mScaleOffset.x;
		_actualScale.y *= _mScaleOffset.y;
		return _actualScale;
	}

	Math::Vec2 GetCenter() const {
		return _mCenter;
	}

	void SetCenter(const Math::Vec2& _newCenter) {
		_mCenter = _newCenter;
	}

	Math::Vec2 GetScale() const {
		return _mScale;
	}

	void SetScale(const Math::Vec2& _newScale) {
		_mScale = _newScale;
	}

	Math::Vec2 GetCenterOffset() const {
		return _mCenterOffset;
	}

	void SetCenterOffset(const Math::Vec2& _newCenterOffset) {
		_mCenterOffset = _newCenterOffset;
	}

	Math::Vec2 GetScaleOffset() const {
		return _mScaleOffset;
	}

	void SetScaleOffset(const Math::Vec2& _newScaleOffset) {
		_mScaleOffset = _newScaleOffset;
	}

	Math::Vec2 GetTopLeft() const {
		return Math::Vec2{ GetLeft(), GetTop() };
	}

	Math::Vec2 GetTopRight() const {
		return Math::Vec2{ GetRight(), GetTop() };
	}

	Math::Vec2 GetBottomLeft() const {
		return Math::Vec2{ GetLeft(), GetBottom() };
	}

	Math::Vec2 GetBottomRight() const {
		return Math::Vec2{ GetRight(), GetBottom() };
	}

	bool Contains(const QuadBox& _box) const {
		return this->GetLeft() <= _box.GetLeft() &&
			_box.GetRight() <= this->GetRight() &&
			_box.GetTop() <= this->GetTop() &&
			_box.GetBottom() <= this->GetBottom();
	}

	bool Intersects(const QuadBox& _box) const {
		return !(this->GetLeft() > _box.GetRight() || this->GetRight() < _box.GetLeft() || this->GetTop() < _box.GetBottom() || this->GetBottom() > _box.GetTop());
	}

private:
	Math::Vec2 _mCenter, _mCenterOffset,
				_mScale, _mScaleOffset;
};

class QuadTree {
private:
	static constexpr size_t Threshold{ 16 },
							MaxDepth{ 8 };

	struct QuadNode {
		std::array<std::unique_ptr<QuadNode>, 4> child{};
		std::vector<Entity> values{ std::vector<Entity>() };
	};

	QuadBox _mQuadBox{};
	std::unique_ptr<QuadNode> _mRoot{};
public:
	QuadTree(){}

	QuadTree(const QuadBox& _nodeBox) : _mQuadBox(_nodeBox), _mRoot(std::make_unique<QuadNode>()) {

	}

	QuadBox GetBox() const {
		return this->_mQuadBox;
	}

	bool isLeaf(const QuadNode* _node) const {
		return !static_cast<bool>(_node->child[0]);
	}

	void ClearQuadTree(QuadNode* _node) {
		if (isLeaf(_node)) 
			_node->values.clear();
		else {
			for (size_t i{ 0 }; i < _node->child.size(); ++i) {
				ClearQuadTree(_node->child[i].get());
				_node->child[i].reset();
			}
		}
	}

	void ClearQuadTree() {
		ClearQuadTree(_mRoot.get());
		_mRoot.get()->values.clear();
	}

	void UpdateDimensions(const std::set<Entity>& _entitySet) {
		Math::Vec2 worldMin{}, worldMax{};
		for (const auto& _entity : _entitySet) {
			if (!_entity.ShouldRun())
				continue;
					
			Math::Vec2 _entityPos{ _entity.GetComponent<Transform>().translation }, _entityScale{ _entity.GetComponent<Transform>().scale };
			if (_entity.HasComponent<RectCollider>()) {
				_entityPos += _entity.GetComponent<RectCollider>().centerOffset;
				_entityScale.x *= _entity.GetComponent<RectCollider>().scaleOffset.x;
				_entityScale.y *= _entity.GetComponent<RectCollider>().scaleOffset.y;
			}
			else if (_entity.HasComponent<CircleCollider>()) {
				_entityPos += _entity.GetComponent<CircleCollider>().centerOffset;
				_entityScale *= _entity.GetComponent<CircleCollider>().scaleOffset;
			}
			_entityScale.x = fabs(_entityScale.x);
			_entityScale.y = fabs(_entityScale.y);
			Math::Vec2 _entityMax{ _entityPos + _entityScale / 2.f }, _entityMin{ _entityPos - _entityScale / 2.f };

			worldMax.x = std::max(_entityMax.x, worldMax.x);
			worldMax.y = std::max(_entityMax.y, worldMax.y);

			worldMin.x = std::min(_entityMin.x, worldMin.x);
			worldMin.y = std::min(_entityMin.y, worldMin.y);
		}

		QuadBox dimension{ (worldMax + worldMin) / 2.f,
							(worldMax - worldMin) * 2.f };

		if (!_mQuadBox.Contains(dimension)) {
			_mQuadBox.SetCenter(dimension.GetCenter());
			_mQuadBox.SetScale(dimension.GetScale());
			_mQuadBox.SetCenterOffset(dimension.GetCenterOffset());
			_mQuadBox.SetScaleOffset(dimension.GetScaleOffset());
		}
	}

	void UpdateQuadTree(const std::set<Entity>& _entitySet) {
		ClearQuadTree();

		for (auto const& _entity : _entitySet) {
			if (_entity.ShouldRun())
				AddNode(_entity);
		}
	}

	void AddNode(QuadNode* _node, size_t _depth, const QuadBox& _box, const Entity& _entity) {
		//ASSERT(_node != nullptr);
		//ASSERT(_box.Contains(mGetBox(_entity));
		
		if (isLeaf(_node)) {
			// Insert the value in this node if possbile
			if (_depth >= MaxDepth || _node->values.size() < Threshold)
				_node->values.emplace_back(_entity);
			// Otherwise spilt and try again
			else {
				Spilt(_node, _box);
				AddNode(_node, _depth, _box, _entity);
			}
		} 
		else {
			QuadBox entityBox{_entity};
			int i{ GetQuadrant(_box, entityBox) };
			if (i != -1)
				AddNode(_node->child[i].get(), _depth + 1, ComputeQuadrantDimensions(_box, i), _entity);
			else
				_node->values.emplace_back(_entity);
		}
	}

	void AddNode(const Entity& _entity) {
		AddNode(_mRoot.get(), 0, _mQuadBox, _entity);
	}

	bool RemoveNode(QuadNode* _node, const QuadBox& _box, const Entity& _entity) {
		//ASSERT(_node != nullptr);
		//ASSERT(_box.contains(mGetBox(value)));
		if (isLeaf(_node))
		{
			// Remove the value from node
			RemoveValue(_node, _entity);
			return true;
		}
		else
		{
			// Remove the value in a child if the value is entirely contained in it
			QuadBox entityBox{ _entity };
			int i{ GetQuadrant(_box, entityBox) };
			if (i != -1){
				if (RemoveNode(_node->child[i].get(), ComputeQuadrantDimensions(_box, i), _entity))
					return TryMerge(_node);
			}
			// Otherwise, we remove the value from the current node
			else
				RemoveValue(_node, _entity);
			return false;
		}
	}
	
	void RemoveNode(const Entity& _entity) {
		RemoveNode(_mRoot.get(), _mQuadBox, _entity);
	}

	void QueryNeighbours(QuadNode* _node, const QuadBox& _box, const QuadBox& _queryBox, std::vector<Entity>& _resultList) const {
		//ASSERt(node != nullptr);
		//ASSERT(_queryBox.Intersects(_box));
		for (const auto& entity : _node->values){
			QuadBox entityBox{ entity };
			if (_queryBox.Intersects(entityBox))
				_resultList.emplace_back(entity);
		}
		if (!isLeaf(_node)){
			for (size_t i{ 0 }; i < _node->child.size(); ++i){
				QuadBox childBox{ ComputeQuadrantDimensions(_box, static_cast<int>(i)) };
				if (_queryBox.Intersects(childBox))
					QueryNeighbours(_node->child[i].get(), childBox, _queryBox, _resultList);
			}
		}
	}
	
	std::vector<Entity> QueryNeighbours(const QuadBox& _box) const {
		std::vector<Entity> result{};
		QueryNeighbours(_mRoot.get(), _mQuadBox, _box, result);
		return result;
	}

	void FindAllIntersectionsInDescendants(QuadNode* _node, const Entity& _entity, std::vector<std::pair<Entity, Entity>>& _resultList) const {
		// Test against the values stored in this node
		QuadBox entityBox{ _entity };
		for (const auto& otherEntity : _node->values){
			QuadBox otherEntityBox{ otherEntity };
			if (entityBox.Intersects(otherEntityBox))
				_resultList.emplace_back(_entity, otherEntity);
		}

		// Test against values stored into descendants of this node
		if (!isLeaf(_node)){
			for (const auto& child : _node->child)
				FindAllIntersectionsInDescendants(child.get(), _entity, _resultList);
		}
	}

	void FindAllIntersections(QuadNode* _node, std::vector<std::pair<Entity, Entity>>& _resultList) const {
		// Find intersections between values stored in this node
		// Make sure to not report the same intersection twice
		for (size_t i{ 0 }; i < _node->values.size(); ++i){
			for (size_t j{ 0 }; j < i; ++j){
				QuadBox entityBox1{ _node->values[i] }, entityBox2{ _node->values[j] };
				if (entityBox1.Intersects(entityBox2))
					_resultList.emplace_back(_node->values[i], _node->values[j]);
			}
		}

		if (!isLeaf(_node)){
			// Values in this node can intersect values in descendants
			for (const auto& child : _node->child){
				for (const auto& entity : _node->values)
					FindAllIntersectionsInDescendants(child.get(), entity, _resultList);
			}

			// Find intersections in children
			for (const auto& child : _node->child)
				FindAllIntersections(child.get(), _resultList);
		}
	}
	
	std::vector<std::pair<Entity, Entity>> FindAllIntersections() const {
		std::vector<std::pair<Entity, Entity>> result{};
		FindAllIntersections(_mRoot.get(), result);
		return result;
	}

	QuadBox ComputeQuadrantDimensions(const QuadBox& _box, int _quadrant) const {
		Math::Vec2 newScale{ _box.GetScale() / 2.f };

		switch (_quadrant) {
		case 0: // NW
			return QuadBox(Math::Vec2{ _box.GetCenter().x - newScale.x / 2.f, _box.GetCenter().y + newScale.y / 2.f }, newScale);
			break;
		case 1:	// NE
			return QuadBox(Math::Vec2{ _box.GetCenter().x + newScale.x / 2.f, _box.GetCenter().y + newScale.y / 2.f }, newScale);
			break;
		case 2:	// SW
			return QuadBox(Math::Vec2{ _box.GetCenter().x - newScale.x / 2.f, _box.GetCenter().y - newScale.y / 2.f }, newScale);
			break;
		case 3:	// SE
			return QuadBox(Math::Vec2{ _box.GetCenter().x + newScale.x / 2.f, _box.GetCenter().y - newScale.y / 2.f }, newScale);
			break;
		default:
			//ASSERT(_quadrant > 3);
			return QuadBox(Math::Vec2{}, Math::Vec2{});
			break;
		}
	}

	int GetQuadrant(const QuadBox& _nodeBox, const QuadBox& _valueBox) const {
		Math::Vec2 center{ _nodeBox.GetCenter() };
		// West
		if (_valueBox.GetRight() < center.x)
		{
			// North West
			if (_valueBox.GetBottom() < center.y)
				return 0;
			// South West
			else if (_valueBox.GetTop() >= center.y)
				return 2;
			// Not contained in any quadrant
			else
				return -1;
		}
		// East
		else if (_valueBox.GetLeft() >= center.x)
		{
			// North East
			if (_valueBox.GetBottom() < center.y)
				return 1;
			// South East
			else if (_valueBox.GetTop() >= center.y)
				return 3;
			// Not contained in any quadrant
			else
				return -1;
		}
		// Not contained in any quadrant
		else
			return -1;
	}

	void Spilt(QuadNode* _node, const QuadBox& _box) {
		//ASSERT(_node != nullptr);
		//ASSERT(isLeaf(_node));

		// Create children
		for (auto& child : _node->child)
			child = std::make_unique<QuadNode>();

		// Assign value to child
		std::vector<Entity> initialValues{ std::vector<Entity>() };
		for (const auto& entity : _node->values) {
			QuadBox entityBox{entity};
			auto i{ GetQuadrant(_box, entityBox) };
			if (i != -1)
				_node->child[i]->values.emplace_back(entity);
			else
				initialValues.emplace_back(entity);
		}
		_node->values = std::move(initialValues);
	}

	void RemoveValue(QuadNode* _node, const Entity& _entity) {
		// Find value in node values container
		auto it{ std::find_if(std::begin(_node->values), 
							  std::end(_node->values), 
							  [this, &_entity](const Entity& _rhs) {
								return _entity.id == _rhs.id; 
	    					  }) };
		////ASSERT(it != std::end(_node->values));
		//BREAKPOINT(it == std::end(_node->values));


		//// Swap with the last element and pop back
		//std::swap(*it, _node->values.back());
		//_node->values.pop_back();
		if (it != std::end(_node->values))
			_node->values.erase(it);
	}

	bool TryMerge(QuadNode* _node) {
		//ASSERT(_node != nullptr);
		//ASSERT(!isLeaf(_node));
		size_t newSize{ _node->values.size()};
		for (const auto& child : _node->child){
			if (!isLeaf(child.get()))
				return false;
			newSize += child->values.size();
		}
		if (newSize <= Threshold){
			_node->values.reserve(newSize);
			
			// Merge the values of all the child
			for (const auto& child : _node->child){
				for (const auto& entity : child->values)
					_node->values.emplace_back(entity);
			}
			// Remove the child
			for (auto& child : _node->child)
				child.reset();
			return true;
		}
		else
			return false;
	}

	void InOrderPrint(QuadNode* _node) {
		if (_node != nullptr) {
			InOrderPrint(_node->child[0].get());
			InOrderPrint(_node->child[1].get());
			for (size_t i{ 0 }; i < _node->values.size(); ++i)
				std::cout << _node->values[i].id << " ";
			InOrderPrint(_node->child[2].get());
			InOrderPrint(_node->child[3].get());
		}
		std::cout << std::endl;
	}
};