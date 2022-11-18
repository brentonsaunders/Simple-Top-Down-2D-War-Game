#include <Windows.h>
#include "GameLoop.h"
#include "Game.h"

GameLoop::GameLoop(Game *game) {
	this->game = game;
}

GameLoop::~GameLoop() {

}

void GameLoop::loop() {
	const int FPS = 60;
	DWORD timestep = 1000 / FPS;
	DWORD delta = 0;
	DWORD lastTime = timeGetTime();

	while (true) {
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			DWORD thisTime = timeGetTime();

			delta += thisTime - lastTime;

			lastTime = thisTime;

			while (delta >= timestep) {
				game->update(timestep);

				delta -= timestep;
			}

			game->draw();
		}
	}
}