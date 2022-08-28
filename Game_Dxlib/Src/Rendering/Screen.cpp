#include "Rendering/Screen.h"

int Screen::Width{ 960 };
int Screen::Height{ 540 };

void Screen::Start() {
	GetDefaultState(&Width, &Height, NULL);
}