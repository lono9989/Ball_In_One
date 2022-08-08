#include "Input.h"

int Input::prevState{ 0 }; // 1フレーム前の状態
int Input::currentState{ 0 }; // 現在の状態
// ↑static intのときはこの行書かないとシンボリックエラーになる件(このためだけにcpp書かなきゃならん)
