#include <windows.h>
#include <iostream>
#include "Game.h"
#include "Window.h"
#include "GameLoop.h"
#include "Math.h"

using namespace std;

Game::Game() : map(40, 30), units(&map) {

}

Game::~Game() {

}

void Game::init() {
	Window window(L"War", 800, 600);

	canvas = new Canvas(window.getHwnd(), 800, 600);

	assets.load();

	start();

	GameLoop gameLoop(this);

	gameLoop.loop();
}

void Game::start() {
	units.init();
}

void Game::update(DWORD time) {
	units.update(time);
}

void Game::draw() {
	canvas->save();

	canvas->fillColor = RGB(34, 177, 76);

	canvas->erase();

	map.draw(canvas, &assets);

	units.draw(canvas, &assets);

	canvas->draw();

	canvas->restore();
}
