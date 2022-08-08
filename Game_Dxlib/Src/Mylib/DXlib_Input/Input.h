#ifndef INPUT_H_
#define INPUT_H_

#include "DxLib.h"


// 入力クラス
class Input
{
public:
    static int prevState; // 1フレーム前の状態
    static int currentState; // 現在の状態

    // 初期化。最初に1回だけ呼んでください。
    static void Init()
    {
        prevState = 0;
        currentState = 0;
    }

    // 最新の入力状況に更新する処理。
    // 毎フレームの最初に（ゲームの処理より先に）呼んでください。
    static void Update()
    {
        prevState = currentState;

        currentState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    }

    // ボタンが押されているか？
    static bool GetButton(int buttonId)
    {
        // 今ボタンが押されているかどうかを返却
        return (currentState & buttonId) != 0;
    }

    // ボタンが押された瞬間か？
    static bool GetButtonDown(int buttonId)
    {
        // 今は押されていて、かつ1フレーム前は押されていない場合はtrueを返却
        return ((currentState & buttonId) & ~(prevState & buttonId)) != 0;
    }

    // ボタンが離された瞬間か？
    static bool GetButtonUp(int buttonId)
    {
        // 1フレーム前は押されていて、かつ今は押されていない場合はtrueを返却
        return ((prevState & buttonId) & ~(currentState & buttonId)) != 0;
    }
}; //←【注意】クラス定義の終わりにはコロンが必要だよ！

#endif  //ここでエラー出た人は↑【注意】の;コロン忘れ