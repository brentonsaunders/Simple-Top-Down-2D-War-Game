#pragma 

#include "Canvas.h"
#include "GameAssets.h"
#include "Units.h"
#include "ObstacleMap.h"

class Game {
public:
	Game();
	~Game();
	void init();
	void update(DWORD);
	void draw();
	void start();

private:
	Canvas* canvas;
	GameAssets assets;
	Units units;
	ObstacleMap map;
};
