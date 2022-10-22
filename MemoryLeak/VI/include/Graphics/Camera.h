#pragma once
#include <pch.h>

class Camera
{
public:
	Camera();
	~Camera() = default;

	Camera& operator+=(const Math::Vec2& translate);
	Camera& operator-=(const Math::Vec2& translate);
	Camera& operator*=(float zoom);
	Math::Vec2 GetPos() { return mPos; }
	float GetZoom() { return mZoom; }
	void SetPos(const Math::Vec2& _mPos);
	void SetZoom(float _mZoom);

private:
	Math::Vec2 mPos;
	float mZoom;
};