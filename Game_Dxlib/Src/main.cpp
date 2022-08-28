#include "DxLib.h"
#include "Rendering/Screen.h"
#include "Game.h"

// 設定画面の【リンカー】→【システム】の【サブシステム】をWindows(SUBSYSTEM:WINDOWS)に設定するとWinMainからプログラムが開始する
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

    // Direct3D9Ex を使用する
    //SetUseDirect3DVersion(DX_DIRECT3D_9EX);

    SetOutApplicationLogValidFlag(FALSE);//ログを出力するかどうか

    // 画面モードの設定
#if _DEBUG
#else
    Screen::Start();
    SetWindowStyleMode(4);
#endif

    SetGraphMode(Screen::Width, Screen::Height, 32); // 画面サイズ960×540のカラービット数32ビットで起動
    SetWindowSize(Screen::Width, Screen::Height);// ウィンドウサイズ960×540(こことSetGraphModeのサイズが異なると画像がゆがむ)
    SetAlwaysRunFlag(FALSE);//アクティブ状態でなくとも処理を実行するかどうか
    ChangeWindowMode(TRUE);//フルスクリーン表示かウィンドウ表示か
    SetMouseDispFlag(TRUE);// ここをFALSEにするとマウスカーソル非表示
    SetWindowSizeChangeEnableFlag(FALSE);//ウインドウサイズの変更の可否
    SetMainWindowText("Ball In One");//この行でエラーになったら【設定】マルチバイト文字セットが間違ってるかも
    //↑ここまでの設定は↓下のDXライブラリ初期化より先にやらないとDxLib_Init()中は画面がフルスクリーンになって終わってからウィンドウサイズが変更になり見苦しい

    // ＤＸライブラリの初期化
    if (DxLib_Init() < 0)
    {
        // DXの初期化にエラーが発生したらプログラム自体を終了(returnで)
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
    // キー入力待ちをする
    //WaitKey();
    // ＤＸライブラリの後始末
    DxLib_End();
    // ソフトの終了
    return 0;
}