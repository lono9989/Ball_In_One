#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

enum class InputType {
	KEY,
	PAD,
	MOUSE
};

/// <summary>
/// �Ǘ��p�N���X
/// </summary>
static class InputManager {
public: 
	
public:
	static void Init();
	static void Update();

	static bool GetInput(InputType type,int buttonId);
	static bool GetInputDown(InputType type, int buttonId);
	static bool GetInputUp(InputType type, int buttonId);
};

#endif // !INPUT_MANAGER_H_
