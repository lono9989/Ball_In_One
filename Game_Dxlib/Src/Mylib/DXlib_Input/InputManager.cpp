#include "InputManager.h"
#include "Input.h"
#include "OnlyKeyInput.h"
#include "MouseInput.h"

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

bool InputManager::GetInput(InputType type, int buttonId)
{
	switch (type)
	{
	case InputType::KEY:
		return OnlyKeyInput::GetKey(buttonId);
		break;
	case InputType::PAD:
		return Input::GetButton(buttonId);
		break;
	case InputType::MOUSE:
		return MouseInput::GetMouse(buttonId);
		break;
	default:
		return false;
		break;
	}
}

bool  InputManager::GetInputDown(InputType type, int buttonId)
{
	switch (type)
	{
	case InputType::KEY:
		return OnlyKeyInput::GetKeyDown(buttonId);
		break;
	case InputType::PAD:
		return Input::GetButtonDown(buttonId);
		break;
	case InputType::MOUSE:
		return MouseInput::GetMouseDown(buttonId);
		break;
	default:
		return false;
		break;
	}
}

bool InputManager::GetInputUp(InputType type, int buttonId)
{
	switch (type)
	{
	case InputType::KEY:
		return OnlyKeyInput::GetKeyUp(buttonId);
		break;
	case InputType::PAD:
		return Input::GetButtonUp(buttonId);
		break;
	case InputType::MOUSE:
		return MouseInput::GetMouseUp(buttonId);
		break;
	default:
		return false;
		break;
	}
}
