#ifndef INPUT_H_
#define INPUT_H_

#include "DxLib.h"


// ���̓N���X
class Input
{
public:
    static int prevState; // 1�t���[���O�̏��
    static int currentState; // ���݂̏��

    // �������B�ŏ���1�񂾂��Ă�ł��������B
    static void Init()
    {
        prevState = 0;
        currentState = 0;
    }

    // �ŐV�̓��͏󋵂ɍX�V���鏈���B
    // ���t���[���̍ŏ��Ɂi�Q�[���̏�������Ɂj�Ă�ł��������B
    static void Update()
    {
        prevState = currentState;

        currentState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    }

    // �{�^����������Ă��邩�H
    static bool GetButton(int buttonId)
    {
        // ���{�^����������Ă��邩�ǂ�����ԋp
        return (currentState & buttonId) != 0;
    }

    // �{�^���������ꂽ�u�Ԃ��H
    static bool GetButtonDown(int buttonId)
    {
        // ���͉�����Ă��āA����1�t���[���O�͉�����Ă��Ȃ��ꍇ��true��ԋp
        return ((currentState & buttonId) & ~(prevState & buttonId)) != 0;
    }

    // �{�^���������ꂽ�u�Ԃ��H
    static bool GetButtonUp(int buttonId)
    {
        // 1�t���[���O�͉�����Ă��āA�����͉�����Ă��Ȃ��ꍇ��true��ԋp
        return ((prevState & buttonId) & ~(currentState & buttonId)) != 0;
    }
}; //���y���Ӂz�N���X��`�̏I���ɂ̓R�������K�v����I

#endif  //�����ŃG���[�o���l�́��y���Ӂz��;�R�����Y��