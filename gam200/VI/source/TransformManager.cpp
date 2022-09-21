#include <TransformManager.h>

void TransformManager::SetScale(const Entity& e, const glm::vec2& _scale)
{
	e.GetComponent<Transform>().scale = _scale;
}

void TransformManager::SetRotation(const Entity& e, float _rotation)
{
	e.GetComponent<Transform>().rotation = _rotation;
}

void TransformManager::SetTranslate(const Entity& e, const glm::vec2& _translation)
{
	e.GetComponent<Transform>().translation = _translation;
}
