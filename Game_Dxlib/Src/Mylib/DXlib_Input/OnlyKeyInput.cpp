#include "OnlyKeyInput.h"

char OnlyKeyInput::KeyBuf[256];
int OnlyKeyInput::resultBuf[256];


// 初期化。最初に1回だけ呼んでください。
void OnlyKeyInput::Init()
{
    GetHitKeyStateAll(KeyBuf);
    for (int i = 0; i < 256; i++) {
        KeyBuf[i] = 0;
        resultBuf[i] = 0;
    }
}

// 最新の入力状況に更新する処理。
// 毎フレームの最初に（ゲームの処理より先に）呼んでください。
void OnlyKeyInput::Update()
{
    GetHitKeyStateAll(KeyBuf);

    //0:何もない
    //1:押された瞬間
    //2:押してる
    //3:離された瞬間
    for (int i = 0; i < 256; i++)
    {
        if (KeyBuf[i] == 1)
        {
            if (resultBuf[i] == 0) resultBuf[i] = 1;
            else if (resultBuf[i] == 1 || resultBuf[i] == 2) resultBuf[i] = 2;
        }
        else
        {
            if (resultBuf[i] == 0 || resultBuf[i] == 3) resultBuf[i] = 0;
            else if (resultBuf[i] == 1 || resultBuf[i] == 2) resultBuf[i] = 3;
        }
    }
}

// ボタンが押されているか？
bool OnlyKeyInput::GetKey(int buttonId)
{
    // 今ボタンが押されているかどうかを返却
    return resultBuf[buttonId] == 2;
}

// ボタンが押された瞬間か？
bool OnlyKeyInput::GetKeyDown(int buttonId)
{
    // 今は押されていて、かつ1フレーム前は押されていない場合はtrueを返却
    return resultBuf[buttonId] == 1;
}

// ボタンが離された瞬間か？
bool OnlyKeyInput::GetKeyUp(int buttonId)
{

    // 1フレーム前は押されていて、かつ今は押されていない場合はtrueを返却
    return resultBuf[buttonId] == 3;
}