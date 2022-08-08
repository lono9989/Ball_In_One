#include "InputManager.h"

void InputManager::Init()
{
		Input::Init();
		OnlyKeyInput::Init();
		MouseInput::Init();
}

void InputManager::Update()
{
	Input::Update();
	OnlyKeyInput::Update();
	MouseInput::Update();
}
