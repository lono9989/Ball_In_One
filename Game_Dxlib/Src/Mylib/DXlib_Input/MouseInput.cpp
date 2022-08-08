#include "MouseInput.h"

int MouseInput::xBuf{ -1 };
int MouseInput::yBuf{ -1 };
int MouseInput::mouseState[256];
int MouseInput::resultState[256];

void MouseInput::Init() {
    for (int i = 0; i < 256; i++) {
        mouseState[i] = 0;
        resultState[i] = 0;
    }
    GetMousePoint(&xBuf, &yBuf);
}
void MouseInput::Update() {
    //ƒ}ƒEƒX‚Ì“ü—Í‚ð’²‚×‚é
    if ((GetMouseInput() &MOUSE_INPUT_LEFT) != 0)
    {
        mouseState[MOUSE_INPUT_LEFT] = 1;
    }
    else mouseState[MOUSE_INPUT_LEFT] = 0;

    if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
    {
        mouseState[MOUSE_INPUT_RIGHT] = 1;
    }
    else mouseState[MOUSE_INPUT_RIGHT] = 0;

    if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0)
    {
        mouseState[MOUSE_INPUT_MIDDLE] = 1;
    }
    else mouseState[MOUSE_INPUT_MIDDLE] = 0;

    if ((GetMouseInput() & MOUSE_INPUT_4) != 0)
    {
        mouseState[MOUSE_INPUT_4] = 1;
    }
    else mouseState[MOUSE_INPUT_4] = 0;

    if ((GetMouseInput() & MOUSE_INPUT_5) != 0)
    {
        mouseState[MOUSE_INPUT_5] = 1;
    }
    else mouseState[MOUSE_INPUT_5] = 0;
    GetMousePoint(&xBuf, &yBuf);

    //‘OƒtƒŒ[ƒ€‚Æ‚Ì”äŠr‚Å’l‚ðresurtState‚É‘}“ü
    //‰½‚à‚È‚¢F‚O
    //‰Ÿ‚³‚ê‚½uŠÔF‚P
    //‰Ÿ‚³‚ê‚Ä‚¢‚éF‚Q
    for (int i = 0; i < 256; i++)
    {
        if (mouseState[i] == 1)
        {
            if (resultState[i] == 0) resultState[i] = 1;
            else if (resultState[i] == 1 || resultState[i] == 2) resultState[i] = 2;
        }
        else if (mouseState[i] == 0)
        {
            if (resultState[i] == 0 || resultState[i] == 3) resultState[i] = 0;
            else if (resultState[i] == 1 || resultState[i] == 2) resultState[i] = 3;
        }
    }
    
}
bool MouseInput::GetMouse(int mouse)
{
    return resultState[mouse] == 2;
}
bool MouseInput::GetMouseDown(int mouse)
{
    return resultState[mouse] == 1;
}
bool MouseInput::GetMouseUp(int mouse)
{
    return resultState[mouse] == 3;
}
int MouseInput::GetMouseX()
{
    return xBuf;
}
int MouseInput::GetMouseY()
{
    return yBuf;
}

VECTOR MouseInput::GetMouseDif_and_SetPos(int x,int y)
{
    VECTOR v;
    v = VECTOR{ (float)(xBuf - x),(float)(yBuf - y),0.0f };
    SetMousePoint(x, y);
    return v;
}
