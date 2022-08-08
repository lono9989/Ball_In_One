#include "OnlyKeyInput.h"

char OnlyKeyInput::KeyBuf[256];
int OnlyKeyInput::resultBuf[256];


// �������B�ŏ���1�񂾂��Ă�ł��������B
void OnlyKeyInput::Init()
{
    GetHitKeyStateAll(KeyBuf);
    for (int i = 0; i < 256; i++) {
        KeyBuf[i] = 0;
        resultBuf[i] = 0;
    }
}

// �ŐV�̓��͏󋵂ɍX�V���鏈���B
// ���t���[���̍ŏ��Ɂi�Q�[���̏�������Ɂj�Ă�ł��������B
void OnlyKeyInput::Update()
{
    GetHitKeyStateAll(KeyBuf);

    //0:�����Ȃ�
    //1:�����ꂽ�u��
    //2:�����Ă�
    //3:�����ꂽ�u��
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

// �{�^����������Ă��邩�H
bool OnlyKeyInput::GetKey(int buttonId)
{
    // ���{�^����������Ă��邩�ǂ�����ԋp
    return resultBuf[buttonId] == 2;
}

// �{�^���������ꂽ�u�Ԃ��H
bool OnlyKeyInput::GetKeyDown(int buttonId)
{
    // ���͉�����Ă��āA����1�t���[���O�͉�����Ă��Ȃ��ꍇ��true��ԋp
    return resultBuf[buttonId] == 1;
}

// �{�^���������ꂽ�u�Ԃ��H
bool OnlyKeyInput::GetKeyUp(int buttonId)
{

    // 1�t���[���O�͉�����Ă��āA�����͉�����Ă��Ȃ��ꍇ��true��ԋp
    return resultBuf[buttonId] == 3;
}