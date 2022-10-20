#include <Camera.h>

Camera::Camera() : mPos(0.f, 0.f), mZoom(1.f) {}

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
	return *this;
}

void Camera::SetPos(const Math::Vec2& _mPos)
{
	mPos = _mPos;
}

void Camera::SetZoom(float _mZoom)
{
	mZoom = _mZoom;
}