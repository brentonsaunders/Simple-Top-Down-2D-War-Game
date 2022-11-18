#pragma once

class Game;

class GameLoop {
public:
	GameLoop(Game *);
	~GameLoop();
	void loop();

private:
	Game* game;
};
