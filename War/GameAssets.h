#pragma once

#include "Bitmap.h"

class GameAssets {
public:
	Bitmap* soldier;
	Bitmap* tank;
	Bitmap* fighter;
	Bitmap* usaFlag;
	Bitmap* germanFlag;
	Bitmap* tree;

	GameAssets();
	~GameAssets();
	bool load();
};
