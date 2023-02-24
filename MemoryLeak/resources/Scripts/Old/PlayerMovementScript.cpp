#include "PlayerMovementScript.h"

REGISTER_SCRIPT(ScriptComponent, PlayerMovementScript);

void PlayerMovementScript::StartScript(const Entity& _e) {
	(void)_e;
}

void PlayerMovementScript::UpdateScript(const Entity& _e) {
	if (FUNC->CheckKey(E_STATE::HOLD, M_BUTTON_L)) {
		Math::Vec2 dirVector{ FUNC->GetWorldMousePos() - _e.GetComponent<Transform>().translation };
		if (dirVector.SqMagnitude() > Math::epsilonValue * Math::epsilonValue)
			FUNC->ApplyImpulse(_e, dirVector.Normalized() * playerSpeed, Math::Vec2{ 0.f, 0.f });
	}
}

void PlayerMovementScript::EndScript(const Entity& _e) {
	(void)_e;
}