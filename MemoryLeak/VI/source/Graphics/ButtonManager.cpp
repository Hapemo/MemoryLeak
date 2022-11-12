#include "ButtonManager.h"
#include "Input.h"
#include "VertexFetcher.h"

void ButtonManager::Init(int* _windowWidth, int* _windowHeight)
{
	mWindowWidth = _windowWidth;
	mWindowHeight = _windowHeight;
}

void ButtonManager::Update()
{
	for (const Entity& e : mEntities)
	{
		e.GetComponent<Button>().isHover = CheckHover(e);
		e.GetComponent<Button>().isClick = CheckClick(e);
		if (!e.GetComponent<Button>().activated)
			e.GetComponent<Button>().activated = CheckActivate(e);
	}
}

bool ButtonManager::CheckHover(const Entity& _e)
{
	Math::Vec2 cursorPos = Math::Vec2(Input::CursorPos().x, -Input::CursorPos().y) +
		Math::Vec2(-*mWindowWidth / 2.f, *mWindowHeight / 2.f);
	Transform xform = _e.GetComponent<Transform>();
	if (!(cursorPos.x <= xform.translation.x + 0.5f * xform.scale.x)) return false;
	if (!(cursorPos.x >= xform.translation.x - 0.5f * xform.scale.x)) return false;
	if (!(cursorPos.y <= xform.translation.y + 0.5f * xform.scale.y)) return false;
	if (!(cursorPos.y >= xform.translation.y - 0.5f * xform.scale.y)) return false;
	return true;
}

bool ButtonManager::CheckClick(const Entity& _e)
{
	if (CheckHover(_e) && Input::CheckKey(E_STATE::HOLD, E_KEY::M_BUTTON_L))
		return true;
	return false;
}

bool ButtonManager::CheckActivate(const Entity& _e)
{
	if (CheckHover(_e) && Input::CheckKey(E_STATE::RELEASE, E_KEY::M_BUTTON_L))
		return true;
	return false;
}