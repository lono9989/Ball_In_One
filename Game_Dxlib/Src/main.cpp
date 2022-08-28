#include "DxLib.h"
#include "Rendering/Screen.h"
#include "Game.h"

// �ݒ��ʂ́y�����J�[�z���y�V�X�e���z�́y�T�u�V�X�e���z��Windows(SUBSYSTEM:WINDOWS)�ɐݒ肷���WinMain����v���O�������J�n����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //--------------------------------------------
    LONGLONG nowtime;
    LONGLONG time;
    float delta_time;
    int fps;
    int fpsCounter;
    LONGLONG fpsCheckTime;
    //--------------------------------------------

    // Direct3D9Ex ���g�p����
    //SetUseDirect3DVersion(DX_DIRECT3D_9EX);

    SetOutApplicationLogValidFlag(FALSE);//���O���o�͂��邩�ǂ���

    // ��ʃ��[�h�̐ݒ�
#if _DEBUG
#else
    Screen::Start();
    SetWindowStyleMode(4);
#endif

    SetGraphMode(Screen::Width, Screen::Height, 32); // ��ʃT�C�Y960�~540�̃J���[�r�b�g��32�r�b�g�ŋN��
    SetWindowSize(Screen::Width, Screen::Height);// �E�B���h�E�T�C�Y960�~540(������SetGraphMode�̃T�C�Y���قȂ�Ɖ摜���䂪��)
    SetAlwaysRunFlag(FALSE);//�A�N�e�B�u��ԂłȂ��Ƃ����������s���邩�ǂ���
    ChangeWindowMode(TRUE);//�t���X�N���[���\�����E�B���h�E�\����
    SetMouseDispFlag(TRUE);// ������FALSE�ɂ���ƃ}�E�X�J�[�\����\��
    SetWindowSizeChangeEnableFlag(FALSE);//�E�C���h�E�T�C�Y�̕ύX�̉�
    SetMainWindowText("Ball In One");//���̍s�ŃG���[�ɂȂ�����y�ݒ�z�}���`�o�C�g�����Z�b�g���Ԉ���Ă邩��
    //�������܂ł̐ݒ�́�����DX���C�u��������������ɂ��Ȃ���DxLib_Init()���͉�ʂ��t���X�N���[���ɂȂ��ďI����Ă���E�B���h�E�T�C�Y���ύX�ɂȂ茩�ꂵ��

    // �c�w���C�u�����̏�����
    if (DxLib_Init() < 0)
    {
        // DX�̏������ɃG���[������������v���O�������̂��I��(return��)
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);

    //---------------------------------------------------
    time = GetNowHiPerformanceCount();
    delta_time = 0.0000001f;

    fpsCheckTime = GetNowHiPerformanceCount();
    fps = 0;
    fpsCounter = 0;
    //--------------------------------------------------

    Game game;
    game.Init();

    SetCameraNearFar(0.1f, 99999.9f);

    ScreenFlip();
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        ClearDrawScreen();
        game.Update(delta_time);
        game.Draw();
        DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS%d", fps);

        ScreenFlip();

        nowtime = GetNowHiPerformanceCount();

        delta_time = (nowtime - time) / 1000000.0f;
        time = nowtime;

        fpsCounter++;
        if (nowtime - fpsCheckTime > 1000000) {
            fps = fpsCounter;
            fpsCounter = 0;
            fpsCheckTime = nowtime;
        }
    }
    SetMouseDispFlag(TRUE);
    // �L�[���͑҂�������
    //WaitKey();
    // �c�w���C�u�����̌�n��
    DxLib_End();
    // �\�t�g�̏I��
    return 0;
}