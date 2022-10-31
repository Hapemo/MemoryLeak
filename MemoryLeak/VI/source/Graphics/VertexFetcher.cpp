#include "VertexFetcher.h"
#include "RenderProps.h"
#include "Logger.h"

std::vector<Math::Vec2> VertexFetcher::FetchVertices(const Entity& _e)
{
	if (!_e.HasComponent<Transform>())
	{
		PrintDebug("Transform");
		return std::vector<Math::Vec2>();
	}
	if (!_e.HasComponent<Sprite>())
	{
		PrintDebug("Sprite");
		return std::vector<Math::Vec2>();
	}

	Transform xform = _e.GetComponent<Transform>();
	Math::Vec2 pos = xform.translation;
	Sprite sprite = _e.GetComponent<Sprite>();

	switch (sprite.sprite)
	{
	case (SPRITE::SQUARE):
	case (SPRITE::TEXTURE):
	{
		float cosTheta = cosf(xform.rotation);
		float sinTheta = sinf(xform.rotation);
		Math::Vec2 i(cosTheta * xform.scale.x * 0.5f, sinTheta * xform.scale.x * 0.5f),
			j(-sinTheta * xform.scale.y *0.5f, cosTheta * xform.scale.y *0.5f);
		return { pos + i + j, pos - i + j, pos - i - j, pos + i - j };
	}
	case (SPRITE::CIRCLE):
	{
		return { pos };
	}
	default:
	{
		PrintDebug("Non-Debug");
		return std::vector<Math::Vec2>();
	}
	}
}

void VertexFetcher::PrintDebug(const std::string& _missingComponent)
{
	LOG_DEBUG("Entity does not contain " + _missingComponent + " component! Unable to fetch vertices.");
}