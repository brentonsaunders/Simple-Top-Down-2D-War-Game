#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include "Game.h"
#include "Console.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow) {
	Game game;

	Console::init();

	game.init();

	return 0;
}
