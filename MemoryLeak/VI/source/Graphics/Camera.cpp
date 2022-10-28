#include <Camera.h>

Camera::Camera() : mPos(0.f, 0.f), mZoom(1.f), 
	mWindowWidth(0), mWindowHeight(0) {}

void Camera::Init(int _windowWidth, int _windowHeight)
{
	mWindowWidth = _windowWidth;
	mWindowHeight = _windowHeight;
}

Camera& Camera::operator+=(const Math::Vec2& translate)
{
	mPos += translate;
	return *this;
}

Camera& Camera::operator-=(const Math::Vec2& translate)
{
	mPos -= translate;
	return *this;
}

Camera& Camera::operator*=(float zoom)
{
	mZoom += zoom;
	if (mZoom < 0.1f)
		mZoom = 0.1f;
	return *this;
}

void Camera::SetPos(const Math::Vec2& _mPos)
{
	mPos = _mPos;
}

void Camera::SetZoom(float _mZoom)
{
	mZoom = _mZoom;
	if (mZoom < 0.1f)
		mZoom = 0.1f;
}