#pragma once
#include <pch.h>

class Camera
{
public:
	Camera();
	~Camera() = default;

	void Init(int _windowWidth, int _windowHeight);

	Camera& operator+=(const Math::Vec2& translate);
	Camera& operator-=(const Math::Vec2& translate);
	Camera& operator*=(float zoom);
	Math::Vec2 GetWindowDim() { return Math::Vec2( static_cast<float>(mWindowWidth), static_cast<float>(mWindowHeight)); }
	Math::Vec2 GetPos() { return mPos; }
	float GetZoom() { return mZoom; }
	void SetPos(const Math::Vec2& _mPos);
	void SetZoom(float _mZoom);

private:
	int mWindowWidth, mWindowHeight;
	Math::Vec2 mPos;
	float mZoom;
};